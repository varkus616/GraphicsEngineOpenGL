#include "App.hpp"
#include <glm/ext/matrix_clip_space.hpp>

bool calculateLightFlag = true;

void printFPS()
{
    static double lastTime = glfwGetTime();
    static int frameCount = 0;

    double currentTime = glfwGetTime();
    frameCount++;

    if (currentTime - lastTime >= 1.0) 
    {
        std::cout << "FPS: " << frameCount << std::endl;
        frameCount = 0;
        lastTime = currentTime;
    }
}

App::App(Window& window)
    : m_window(window),
    cubes(100),
    plane(Utils::generatePlane(100, 100)),
    obj(&plane, DrawMode::ELEMENTS),
    shadowMap(1024, 1024)
{

    currentRenderData.shaderProgram.addShader("shaders\\vert\\vertShader2.glsl", GL_VERTEX_SHADER);
    currentRenderData.shaderProgram.addShader("shaders\\frag\\fragShader2.glsl", GL_FRAGMENT_SHADER);
    currentRenderData.shaderProgram.linkProgram();

    basicShader = currentRenderData.shaderProgram;

    shadowShader.addShader("shaders\\vert\\shadowsVert.glsl", GL_VERTEX_SHADER);
    shadowShader.addShader("shaders\\frag\\shadowsFrag.glsl", GL_FRAGMENT_SHADER);
    shadowShader.linkProgram();


    Texture wallText = Texture(Utils::loadTexture("resources\\container2.png"));
    Texture wallTextSpec = Texture(Utils::loadTexture("resources\\container2_specular.png"));
   
    installLights();

    currentRenderData.uniformUpdater = [&](Renderable& r, RenderData& d, Window& w) -> void
        {
            const GLfloat t = (GLfloat)glfwGetTime();
            glm::mat4 mvmatrix = w.getViewMatrix() * r.getModelMatrix();
            glm::mat4 proj = w.getProjectionMatrix();
            glm::mat4 view = w.getViewMatrix();
            glm::mat4 model = r.getModelMatrix();
            glm::vec3 cameraPos = w.getCamera().GetPosition();
            glm::mat3 invTrMat = glm::transpose(glm::inverse(model));

            glm::vec3 camDir = w.getCamera().GetDirection();



            // Use the Light and Material structs for uniform values
            d.shaderConfig.uniforms["viewPos"] = UniformValue(UniformType::VEC3, cameraPos);
            d.shaderConfig.uniforms["model"] = UniformValue(UniformType::MAT4, model);
            d.shaderConfig.uniforms["norm_matrix"] = UniformValue(UniformType::MAT3, invTrMat);
            d.shaderConfig.uniforms["mvpmatrix"] = UniformValue(UniformType::MAT4, proj*mvmatrix);
            
            d.shaderConfig.uniforms["objectColor"] = UniformValue(UniformType::VEC4, r.getColor());

            d.shaderConfig.uniforms["numPointLights"] = UniformValue(UniformType::INT, (int)pointLights.size());
            d.shaderConfig.uniforms["numSpotLights"] = UniformValue(UniformType::INT, (int)spotLights.size());

            d.shaderConfig.uniforms["calculateLight"] = UniformValue(UniformType::BOOL, calculateLightFlag);
            for (size_t i = 0; i < pointLights.size(); i++) {
                std::string index = std::to_string(i);
                d.shaderConfig.uniforms["pointLights[" + index + "].position"] = UniformValue(UniformType::VEC3,   pointLights[i].position);
                d.shaderConfig.uniforms["pointLights[" + index + "].constant"] = UniformValue(UniformType::FLOAT,  pointLights[i].constant);
                d.shaderConfig.uniforms["pointLights[" + index + "].linear"] = UniformValue(UniformType::FLOAT,    pointLights[i].linear);
                d.shaderConfig.uniforms["pointLights[" + index + "].quadratic"] = UniformValue(UniformType::FLOAT, pointLights[i].quadratic);
                d.shaderConfig.uniforms["pointLights[" + index + "].ambient"] = UniformValue(UniformType::VEC3,  pointLights[i].ambient);
                d.shaderConfig.uniforms["pointLights[" + index + "].diffuse"] = UniformValue(UniformType::VEC3,  pointLights[i].diffuse);
                d.shaderConfig.uniforms["pointLights[" + index + "].specular"] = UniformValue(UniformType::VEC3, pointLights[i].specular);

            }

            for (size_t i = 0; i < spotLights.size(); i++) {
                std::string index = std::to_string(i);
                d.shaderConfig.uniforms["spotLights[" + index + "].position"] = UniformValue(UniformType::VEC3, cameraPos);
                d.shaderConfig.uniforms["spotLights[" + index + "].direction"] = UniformValue(UniformType::VEC3,  camDir);
                d.shaderConfig.uniforms["spotLights[" + index + "].constant"] = UniformValue(UniformType::FLOAT,  spotLights[i].constant);
                d.shaderConfig.uniforms["spotLights[" + index + "].linear"] = UniformValue(UniformType::FLOAT,    spotLights[i].linear);
                d.shaderConfig.uniforms["spotLights[" + index + "].quadratic"] = UniformValue(UniformType::FLOAT, spotLights[i].quadratic);
                d.shaderConfig.uniforms["spotLights[" + index + "].cutOff"] = UniformValue(UniformType::FLOAT,    spotLights[i].cutOff);
                d.shaderConfig.uniforms["spotLights[" + index + "].outerCutOff"] = UniformValue(UniformType::FLOAT,spotLights[i].outerCutOff);
                d.shaderConfig.uniforms["spotLights[" + index + "].ambient"] = UniformValue(UniformType::VEC3,    spotLights[i].ambient);
                d.shaderConfig.uniforms["spotLights[" + index + "].diffuse"] = UniformValue(UniformType::VEC3,    spotLights[i].diffuse);
                d.shaderConfig.uniforms["spotLights[" + index + "].specular"] = UniformValue(UniformType::VEC3,   spotLights[i].specular);
            
            }

            d.shaderConfig.uniforms["dirLight.ambient"] = UniformValue(UniformType::VEC3, dirLight.ambient);
            d.shaderConfig.uniforms["dirLight.diffuse"] = UniformValue(UniformType::VEC3, dirLight.diffuse);
            d.shaderConfig.uniforms["dirLight.specular"] = UniformValue(UniformType::VEC3, dirLight.specular);
            d.shaderConfig.uniforms["dirLight.direction"] = UniformValue(UniformType::VEC3, dirLight.direction);
            
            //d.shaderConfig.uniforms["material.ambient"] = UniformValue(UniformType::VEC3, material.ambient);
            //d.shaderConfig.uniforms["material.diffuse"] = UniformValue(UniformType::INT,  0);
            //d.shaderConfig.uniforms["material.specular"] = UniformValue(UniformType::INT,  1);
        };

    srand(777);

    int BOUND_X = 15;
    int BOUND_Y = 15;
    int BOUND_Z = 15;


    for (int i = 0; i < cubes.size(); i++) {
        auto& cube = cubes[i];

        // Losowanie pozycji
        float x = rand() % (BOUND_X + 1 - (-BOUND_X)) + (-BOUND_X);
        float y = rand() % (BOUND_Y + 1 - (-BOUND_Y)) + (-BOUND_Y);
        float z = rand() % (BOUND_Z + 1 - (-BOUND_Z)) + (-BOUND_Z);

        cube.addTexture(wallText, 0);
        cube.setPosition(x, y, z);

        float angleX = rand() % 360;
        float angleY = rand() % 360;
        float angleZ = rand() % 360;

        cube.rotate(angleX, Axis::X);
        cube.rotate(angleY, Axis::Y);
        cube.rotate(angleZ, Axis::Z);
        x = rand() % 255;
        y = rand() % 255;
        z = rand() % 255;

        //cube.setColor(glm::vec4(x/255, y/255, z/255, 0));
    }

    obj.setPosition(0, -16, 0);
    epicT.setPosition(0, 0, 8);
    m_window.getCamera().SetPosition(glm::vec3(0, 0, 3));
    obj.setColor(glm::vec4(0, 1, 0, 0));
}

void App::renderShadows()
{
    shadowMap.BindForWrite();  // Zwi¹zanie tekstury mapy cieni
    float near = m_window.getCamera().GetNearPlane();
    float far = m_window.getCamera().GetFarPlane();
    float w = m_window.getWidth();
    float h = m_window.getHeight();
    
    glm::mat4 lightProjection = glm::ortho(0.f, w, 0.f, h, near, far);
    glm::mat4 lightView = glm::lookAt(light.position,
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)); 
    glm::mat4 lightSpaceMatrix = lightProjection * lightView; 
    
    auto uni = [&](Renderable& r, RenderData& d, Window& w) {
        d.shaderConfig.uniforms["lightSpaceMatrix"] = UniformValue(UniformType::MAT4, lightSpaceMatrix);
        d.shaderConfig.uniforms["model"] = UniformValue(UniformType::MAT4, r.getModelMatrix());
        };
    shadowShader.use();
    shadowShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

    for (int i = 0; i < cubes.size(); i++) {
        auto& cube = cubes[i];
        shadowShader.setMat4("model",cube.getModelMatrix());

        m_window.draw(cube, shadowShader);
    }
    shadowShader.setMat4("model", obj.getModelMatrix());

    m_window.draw(obj, shadowShader);

    shadowMap.Unbind();
    glViewport(0, 0, w, h);
    shadowMap.BindForRead();  
}

void App::installLights()
{
    light.position = { 0, 7, 13 };
    dirLight.direction = { 0, 0, 0 };

    dirLight.ambient = { 0.2, 0.2, 0.25 };
    dirLight.diffuse = { 0.3, 0.3, 0.3 };
    dirLight.specular = { 0.5f, 0.5f, 0.5f };

    light.constant = 1.f;
    light.linear = 0.09f;
    light.quadratic = 0.032f;
    light.cutOff = glm::cos(glm::radians(12.5f));
    light.outerCutOff = glm::cos(glm::radians(17.5));

    light.ambient = { 0.2, 0.2, 0.2 };
    light.diffuse = { 0.8, 0.8, 0.8 };
    light.specular = { 1.f, 1.f, 1.f };


    PointLight pointLight;
    pointLight.position = { 0, 3, -19 };
    pointLight.ambient = { 0.0f, 0.0f, 0.2f };
    pointLight.diffuse = { 0.0f, 0.0f, 0.5f };
    pointLight.specular = { 0.0f , 0.0f , 1.f };

    pointLight.constant = 1.0f;
    pointLight.linear = 0.092f;
    pointLight.quadratic = 0.032f;

    pointLights.emplace_back(pointLight);
    spotLights.emplace_back(light);

}
void App::run()
{
    while (isRunning())
    {
        processInput();
        update();
        render();
        printFPS();
    }
}

void App::processInput() 
{
    m_window.processInput(0.15f);
    if (m_window.shouldClose())
        m_app_running = false;
    if (glfwGetKey(m_window.getWindowHandle(), GLFW_KEY_F1) == GLFW_PRESS)
        calculateLightFlag = !calculateLightFlag;
    if (glfwGetKey(m_window.getWindowHandle(), GLFW_KEY_F2) == GLFW_PRESS)
        obj.setColor(glm::vec4(0, 0, 1, 0));

}

void App::update()
{
    
    float t = glfwGetTime();

    m_window.getCamera().Update();
    //pointLights[0].position = glm::vec3(360 * glm::sin(glfwGetTime()), 40,0);//m_window.getCamera().GetPosition();

}

void App::render()
{
   renderShadows();
   float w = m_window.getWidth();
   float h = m_window.getHeight();
   glViewport(0, 0, w, h);
   m_window.clear(Color(0.1f, 0.1f, 0.1f, 1.f));

   currentRenderData.shaderProgram.setInt("shadowMap", 1);

   for (int i = 0; i < cubes.size(); i++) {
       auto& cube = cubes[i];
       
       m_window.draw(cube, currentRenderData);
   }
   m_window.draw(obj, currentRenderData);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   //glEnable(GL_CULL_FACE);
   //glCullFace(GL_BACK);
   //renderImGui();

    m_window.display();
}

void App::renderImGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
        
    if(ImGui::CollapsingHeader("Directional Light Settings")) {
        // Kontrola kierunku œwiat³a (wektor 3D)
        ImGui::Text("Light Direction");
        ImGui::SliderFloat("X", &dirLight.direction.x, -10.0f, 10.0f);
        ImGui::SliderFloat("Y", &dirLight.direction.y, -10.0f, 10.0f);
        ImGui::SliderFloat("Z", &dirLight.direction.z, -10.0f, 10.0f);

        // Kontrola ambientu
        ImGui::Text("Ambient Light");
        ImGui::ColorEdit3("Ambient Color", &dirLight.ambient[0]);

        // Kontrola diffuse
        ImGui::Text("Diffuse Light");
        ImGui::ColorEdit3("Diffuse Color", &dirLight.diffuse[0]);

        // Kontrola specular
        ImGui::Text("Specular Light");
        ImGui::ColorEdit3("Specular Color", &dirLight.specular[0]);
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
