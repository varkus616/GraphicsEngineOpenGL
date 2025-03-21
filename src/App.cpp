#include "App.hpp"


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
    cubes(200),
    plane(Utils::generatePlane(100, 100)),
    obj(&plane, DrawMode::ELEMENTS),
    sphereObj(&sphere)
{
    currentRenderData.shaderProgram.addShader("shaders\\vert\\vertShader.glsl", GL_VERTEX_SHADER);
    currentRenderData.shaderProgram.addShader("shaders\\frag\\fragShader.glsl", GL_FRAGMENT_SHADER);
    currentRenderData.shaderProgram.linkProgram();

    Texture wallText = Texture(Utils::loadTexture("resources\\container2.png"));
    Texture wallTextSpec = Texture(Utils::loadTexture("resources\\container2_specular.png"));
   
    installLights();

    currentRenderData.uniformUpdater = [&](Renderable& r, RenderData& d, Window& w) -> void
        {
            const GLfloat t = (GLfloat)glfwGetTime();
            glm::mat4 mvmatrix = w.getViewMatrix() * r.getModelMatrix();
            glm::mat4 proj = w.getProjectionMatrix();
            glm::mat4 model = r.getModelMatrix();
            glm::vec3 viewPos = w.getCamera().GetPosition();
            glm::mat4 invTrMat = glm::transpose(glm::inverse(model));

            glm::vec3 camDir = w.getCamera().GetDirection();


            // Use the Light and Material structs for uniform values
            d.shaderConfig.uniforms["view"] = UniformValue(UniformType::MAT4, w.getViewMatrix());
            d.shaderConfig.uniforms["viewPos"] = UniformValue(UniformType::VEC3, viewPos);
            d.shaderConfig.uniforms["model"] = UniformValue(UniformType::MAT4, r.getModelMatrix());
            d.shaderConfig.uniforms["proj_matrix"] = UniformValue(UniformType::MAT4, proj);
            d.shaderConfig.uniforms["norm_matrix"] = UniformValue(UniformType::MAT4, invTrMat);
            d.shaderConfig.uniforms["objectColor"] = UniformValue(UniformType::VEC4, r.getColor());

            d.shaderConfig.uniforms["numPointLights"] = UniformValue(UniformType::INT, (int)pointLights.size());
            d.shaderConfig.uniforms["numSpotLights"] = UniformValue(UniformType::INT, (int)spotLights.size());

            for (size_t i = 0; i < pointLights.size(); i++) {
                std::string index = std::to_string(i);

                d.shaderConfig.uniforms["pointLights[" + index + "].position"] = UniformValue(UniformType::VEC3, pointLights[i].position);
                d.shaderConfig.uniforms["pointLights[" + index + "].constant"] = UniformValue(UniformType::FLOAT, pointLights[i].constant);
                d.shaderConfig.uniforms["pointLights[" + index + "].linear"] = UniformValue(UniformType::FLOAT, pointLights[i].linear);
                d.shaderConfig.uniforms["pointLights[" + index + "].quadratic"] = UniformValue(UniformType::FLOAT, pointLights[i].quadratic);
                d.shaderConfig.uniforms["pointLights[" + index + "].ambient"] = UniformValue(UniformType::VEC3, pointLights[i].ambient);
                d.shaderConfig.uniforms["pointLights[" + index + "].diffuse"] = UniformValue(UniformType::VEC3, pointLights[i].diffuse);
                d.shaderConfig.uniforms["pointLights[" + index + "].specular"] = UniformValue(UniformType::VEC3, pointLights[i].specular);

            }

            for (size_t i = 0; i < spotLights.size(); i++) {
                std::string index = std::to_string(i);
                d.shaderConfig.uniforms["spotLights[" + index + "].position"] = UniformValue(UniformType::VEC3,   viewPos);
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
            
            d.shaderConfig.uniforms["material.ambient"] = UniformValue(UniformType::VEC3, material.ambient);
            d.shaderConfig.uniforms["material.diffuse"] = UniformValue(UniformType::INT,  0);
            d.shaderConfig.uniforms["material.specular"] = UniformValue(UniformType::INT,  1);
        };


    srand(time(0));

    int BOUND_X = 30;
    int BOUND_Y = 30;
    int BOUND_Z = 30;


    for (int i = 0; i < cubes.size(); i++) {
        auto& cube = cubes[i];
        float x = rand() % (BOUND_X + 1 - (-BOUND_X)) + (-BOUND_X);
        float y = rand() % (BOUND_Y + 1 - (-BOUND_Y)) + (-BOUND_Y);
        float z =   rand() % (BOUND_Z + 1 - (-BOUND_Z)) + (-BOUND_Z);
        cube.addTexture(wallText, 0);
        cube.setPosition(x, y, z);
        x = rand() % 255;
        y = rand() % 255;
        z = rand() % 255;
        cube.setColor(glm::vec4(x/255, y/255, z/255, 0));
    }

    obj.setPosition(0, -2, 0);
    epicT.setPosition(0, 0, 8);
    m_window.getCamera().SetPosition(glm::vec3(0, 0, 3));
    obj.setColor(glm::vec4(0, 1, 0, 0));
}

void App::installLights()
{
    PointLight pointLight;
    pointLight.position = { 0, -40, -40 };
    light.position = { 0, 40, 40 };
    dirLight.direction = { 0, 40, 40 };

    dirLight.ambient = { 0.1, 0.1, 0.1 };
    dirLight.diffuse = { 0.8, 0.8, 0.8 };
    dirLight.specular = { 0.2f, 0.2f, 0.2f };

    light.constant = 1.f;
    light.linear = 0.09f;
    light.quadratic = 0.032f;
    light.cutOff = glm::cos(glm::radians(12.5f));
    light.outerCutOff = glm::cos(glm::radians(17.5));

    light.ambient = { 0.1, 0.1, 0.1 };
    light.diffuse = { 0.8, 0.8, 0.8 };
    light.specular = { 1.f, 1.f, 1.f };


    pointLight.ambient = { 0.2f, 0.1f, 0.05f };
    pointLight.diffuse = { 1.0f, 0.5f, 0.2f };
    pointLight.specular = { 0.5f, 0.3f, 0.2f };

    pointLight.constant = 1.0f;
    pointLight.linear = 0.92f;
    pointLight.quadratic = 0.70f;

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
    m_window.processInput(0.5f);
    if (m_window.shouldClose())
        m_app_running = false;
    if (glfwGetKey(m_window.getWindowHandle(), GLFW_KEY_F1) == GLFW_PRESS)
        obj.setColor(glm::vec4(1, 1, 1, 0));
    if (glfwGetKey(m_window.getWindowHandle(), GLFW_KEY_F2) == GLFW_PRESS)
        obj.setColor(glm::vec4(0, 0, 1, 0));

}

void App::update()
{
    
    float t = glfwGetTime();

    m_window.getCamera().Update();
    pointLights[0].position = glm::vec3(360 * glm::sin(glfwGetTime()), 40,0);//m_window.getCamera().GetPosition();

}

void App::render()
{
    m_window.clear(Color(0.1f, 0.1f, 0.1f, 1.f));

    for (int i = 0; i < cubes.size(); i++) {
        auto& cube = cubes[i];
        
        m_window.draw(cube, currentRenderData);
    }
    m_window.draw(obj, currentRenderData);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    renderImGui();

    m_window.display();
}

void App::renderImGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Light and Material Controls");

    // Light Controls
    ImGui::Text("Light Properties");
    ImGui::SliderFloat3("Light Position", &spotLights[0].position[0], -40.0f, 40.0f);
    float cutOffAngle = glm::degrees(glm::acos(spotLights[0].cutOff));  // Przekszta³æ cosinus na stopnie
    float outerCutOffAngle = glm::degrees(glm::acos(spotLights[0].outerCutOff));

    if (ImGui::SliderFloat("Light Cutoff", &cutOffAngle, 0.0f, 90.0f)) {
        spotLights[0].cutOff = glm::cos(glm::radians(cutOffAngle)); // Konwersja stopni -> cosinus
    }

    if (ImGui::SliderFloat("Light OuterCutOff", &outerCutOffAngle, 0.0f, 90.0f)) {
        spotLights[0].outerCutOff = glm::cos(glm::radians(outerCutOffAngle));
    }

    ImGui::ColorEdit3("Light Ambient", &spotLights[0].ambient[0]);
    ImGui::ColorEdit3("Light Diffuse", &spotLights[0].diffuse[0]);
    ImGui::ColorEdit3("Light Specular", &spotLights[0].specular[0]);

    // Material Controls
    ImGui::Text("Material Properties");
    ImGui::ColorEdit3("Material Ambient", &material.ambient[0]);
    ImGui::SliderFloat("Shininess", &material.shininess, 1.0f, 128.0f);

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
