#include "App.hpp"
#include <glm/ext/matrix_clip_space.hpp>


bool calculateLightFlag = true;
glm::mat4 lightSpaceMatrix;

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
std::vector<std::string> faces = {
    "resources\\right.jpg",
    "resources\\left.jpg",
    "resources\\top.jpg",
    "resources\\bottom.jpg",
    "resources\\front.jpg",
    "resources\\back.jpg" };

App::App(Window& window)
    : m_window(window),
    cubes(10),
    plane(Utils::generatePlane(100, 100)),
    obj(&plane, DrawMode::ELEMENTS),
    shadowMap(1024, 1024),
    m_skybox(faces)
{

    //float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
    //    // positions   // texCoords
    //    -1.0f,  1.0f,  0.0f, 1.0f,
    //    -1.0f, -1.0f,  0.0f, 0.0f,
    //     1.0f, -1.0f,  1.0f, 0.0f,
    //
    //    -1.0f,  1.0f,  0.0f, 1.0f,
    //     1.0f, -1.0f,  1.0f, 0.0f,
    //     1.0f,  1.0f,  1.0f, 1.0f
    //};
    //
    //
    //glGenVertexArrays(1, &quadVAO);
    //glGenBuffers(1, &quadVBO);
    //glBindVertexArray(quadVAO);
    //
    //glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    //
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    currentRenderData.shaderProgram.addShader("shaders\\vert\\vertShader2.glsl", GL_VERTEX_SHADER);
    currentRenderData.shaderProgram.addShader("shaders\\frag\\fragShader2.glsl", GL_FRAGMENT_SHADER);
    currentRenderData.shaderProgram.linkProgram();

    basicShader = currentRenderData.shaderProgram;

    shadowView.addShader("shaders\\vert\\viewShadowVert.glsl", GL_VERTEX_SHADER);
    shadowView.addShader("shaders\\frag\\viewShadowFrag.glsl", GL_FRAGMENT_SHADER);
    shadowView.linkProgram();

    //currentRenderData.shaderProgram = shadowView;

    shadowShader.addShader("shaders\\vert\\shadowsVert.glsl", GL_VERTEX_SHADER);
    shadowShader.addShader("shaders\\frag\\shadowsFrag.glsl", GL_FRAGMENT_SHADER);
    shadowShader.linkProgram();

    skyboxShader.addShader("shaders\\vert\\cubemapVert.glsl", GL_VERTEX_SHADER);
    skyboxShader.addShader("shaders\\frag\\cubemapFrag.glsl", GL_FRAGMENT_SHADER);
    skyboxShader.linkProgram();

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
    int BOUND_Y = 0;
    int BOUND_Z = 15;


    for (int i = 0; i < cubes.size(); i++) {
        auto& cube = cubes[i];

        // Losowanie pozycji
        float x = rand() % (BOUND_X + 1 - (-BOUND_X)) + (-BOUND_X);
        float y = rand() % (BOUND_Y + 1 - (-BOUND_Y)) + (-BOUND_Y);
        float z = rand() % (BOUND_Z + 1 - (-BOUND_Z)) + (-BOUND_Z);

        cube.addTexture(wallText, 0);
        cube.setPosition(x, y + 0.55, z);

        float angleX = rand() % 360;
        float angleY = rand() % 360;
        float angleZ = rand() % 360;

        cube.rotate(angleX, Axis::X);
        cube.rotate(angleY, Axis::Y);
        cube.rotate(angleZ, Axis::Z);
        x = rand() % 255;
        y = rand() % 255;
        z = rand() % 255;

        //cube.setColor(glm::vec4(x/255 * 0.5, y/255 * 0.5, z/255 * 0.5, 0));
        cube.setColor(glm::vec4(1, 0, 0, 0));
    }

    obj.setPosition(0, 0, 0);
    epicT.setPosition(0, 0, 8);
    m_window.getCamera().SetPosition(glm::vec3(0, 1, 3));
    //obj.setColor(glm::vec4(0, 1, 0, 0));
    miku.loadModel("resources\\miku.obj");
    miku.m_drawMode = DrawMode::ELEMENTS;
   
}

void App::renderShadows()
{
    glm::mat4 lightProjection = glm::ortho(
        -orthoSize, orthoSize,
        -orthoSize, orthoSize,
        lightNear, lightFar);

    //lightProjection = glm::perspective(glm::radians(90.f), (float)(w/h), lightNear, lightFar);

    glm::mat4 lightView = glm::lookAt(
        glm::vec3(0.0f, 1.0f, 0.0f),
        -dirLight.direction, 
        glm::vec3(0.0f, 1.0f, 0.0f));  

    lightSpaceMatrix = lightProjection * lightView;
    shadowMap.BindForWrite();  
    
    glClear(GL_DEPTH_BUFFER_BIT);

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
    glViewport(0, 0, m_window.getWidth(), m_window.getHeight());
 }

void App::installLights()
{
    light.position = { 0, 4, 5 };
    dirLight.direction = { 0, 0, 0 };

    dirLight.ambient = { 0.2, 0.2, 0.25 };
    dirLight.diffuse = { 0.2, 0.2, 0.2 };
    dirLight.specular = { 0.2, 0.2, 0.2 };

    light.constant = 1.f;
    light.linear = 0.09f;
    light.quadratic = 0.032f;
    light.cutOff = glm::cos(glm::radians(12.5f));
    light.outerCutOff = glm::cos(glm::radians(17.5));

    light.ambient = { 0.2, 0.2, 0.2 };
    light.diffuse = { 0.8, 0.8, 0.8 };
    light.specular = { 1.f, 1.f, 1.f };


    PointLight pointLight;
    pointLight.position = { 0, 2, 3 };
    pointLight.ambient = { 0.9, 0.9, 0.9 };
    pointLight.diffuse = { 0.5, 0.5, 0.5 };
    pointLight.specular = { 0.3f, 0.3f, 0.3f };

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

}
void App::render()
{
   //renderShadows();
   m_window.clear();

   //currentRenderData.shaderProgram.use();
   //shadowMap.BindForRead(GL_TEXTURE0);
   //
   //currentRenderData.shaderProgram.setInt("shadowMap", 0);
   //currentRenderData.shaderProgram.setMat4("lightSpaceMatrix", lightSpaceMatrix);
   
   m_skybox.render(skyboxShader, m_window.getViewMatrix(), m_window.getCamera().GetProjectionMatrix());
   
   //for (int i = 0; i < cubes.size(); i++) {
   //    auto& cube = cubes[i];
   //    
   //    m_window.draw(cube, currentRenderData);
   //}
   m_window.draw(obj, currentRenderData);
   m_window.draw(miku, currentRenderData);
   //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   openGlFLags();
   
   renderImGui();

    m_window.display();
}

void App::renderImGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Shadow Map Controls");

    // Kontrola pozycji œwiat³a z przyciskami +/-
    ImGui::Text("Light Settings");
    ImGui::PushID("LightPos");
    {
        ImGui::Text("Light Position:");
        ImGui::SliderFloat("X", &dirLight.position.x, -50.0f, 50.0f);
        ImGui::SameLine(); if (ImGui::SmallButton("-1")) pointLights[0].position.x -= 1.0f;
        ImGui::SameLine(); if (ImGui::SmallButton("+1")) pointLights[0].position.x += 1.0f;

        ImGui::SliderFloat("Y", &dirLight.position.y, -50.0f, 50.0f);
        ImGui::SameLine(); if (ImGui::SmallButton("-1")) pointLights[0].position.y -= 1.0f;
        ImGui::SameLine(); if (ImGui::SmallButton("+1")) pointLights[0].position.y += 1.0f;

        ImGui::SliderFloat("Z", &dirLight.position.z, -50.0f, 50.0f);
        ImGui::SameLine(); if (ImGui::SmallButton("-1")) pointLights[0].position.z -= 1.0f;
        ImGui::SameLine(); if (ImGui::SmallButton("+1")) pointLights[0].position.z += 1.0f;
    }
    ImGui::PopID();

    // Kontrola celu œwiat³a z przyciskami +/-
    ImGui::PushID("LightTarget");
    {
        ImGui::Text("Light Target:");
        ImGui::SliderFloat("X##Target", &dirLight.direction.x, -50.0f, 50.0f);
        ImGui::SameLine(); if (ImGui::SmallButton("-1##TX")) lightTarget.x -= 1.0f;
        ImGui::SameLine(); if (ImGui::SmallButton("+1##TX")) lightTarget.x += 1.0f;

        ImGui::SliderFloat("Y##Target", &dirLight.direction.y, -50.0f, 50.0f);
        ImGui::SameLine(); if (ImGui::SmallButton("-1##TY")) lightTarget.y -= 1.0f;
        ImGui::SameLine(); if (ImGui::SmallButton("+1##TY")) lightTarget.y += 1.0f;

        ImGui::SliderFloat("Z##Target", &dirLight.direction.z, -50.0f, 50.0f);
        ImGui::SameLine(); if (ImGui::SmallButton("-1##TZ")) lightTarget.z -= 1.0f;
        ImGui::SameLine(); if (ImGui::SmallButton("+1##TZ")) lightTarget.z += 1.0f;
    }
    ImGui::PopID();

    // Kontrola parametrów rzutowania z przyciskami +/-
    ImGui::Text("Projection Settings");
    ImGui::SliderFloat("Near Plane", &lightNear, 0.1f, 50.0f);
    ImGui::SameLine(); if (ImGui::SmallButton("-1##Near")) lightNear = glm::max(0.1f, lightNear - 1.0f);
    ImGui::SameLine(); if (ImGui::SmallButton("+1##Near")) lightNear += 1.0f;

    ImGui::SliderFloat("Far Plane", &lightFar, 50.0f, 500.0f);
    ImGui::SameLine(); if (ImGui::SmallButton("-1##Far")) lightFar = glm::max(lightNear + 1.0f, lightFar - 1.0f);
    ImGui::SameLine(); if (ImGui::SmallButton("+1##Far")) lightFar += 1.0f;

    ImGui::SliderFloat("Ortho Size", &orthoSize, 10.0f, 200.0f);
    ImGui::SameLine(); if (ImGui::SmallButton("-1##Ortho")) orthoSize = glm::max(1.0f, orthoSize - 1.0f);
    ImGui::SameLine(); if (ImGui::SmallButton("+1##Ortho")) orthoSize += 1.0f;

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void App::openGlFLags()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

}