#include "App.hpp"


App::App(Window& window)
    : m_window(window),
    cubes(200),
    plane(Utils::generatePlane(100, 100)),
    obj(&plane, DrawMode::ELEMENTS),
    sphereObj(&sphere)
{
    light.position = {0, 40, 40};
    currentRenderData.shaderProgram.addShader("shaders\\vert\\vertShader.glsl", GL_VERTEX_SHADER);
    currentRenderData.shaderProgram.addShader("shaders\\frag\\fragShader.glsl", GL_FRAGMENT_SHADER);
    currentRenderData.shaderProgram.linkProgram();

    Texture wallText = Texture(Utils::loadTexture("resources\\container2.png"));
    Texture wallTextSpec = Texture(Utils::loadTexture("resources\\container2_specular.png"));

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

            d.shaderConfig.uniforms["light.position"] = UniformValue(UniformType::VEC3, viewPos);
            d.shaderConfig.uniforms["light.direction"] = UniformValue(UniformType::VEC3, camDir);

            d.shaderConfig.uniforms["light.ambient"] = UniformValue(UniformType::VEC3, light.ambient);
            d.shaderConfig.uniforms["light.diffuse"] = UniformValue(UniformType::VEC3, light.diffuse);
            d.shaderConfig.uniforms["light.specular"] = UniformValue(UniformType::VEC3, light.specular);

            light.constant = 1.f;
            light.linear = 0.09f;
            light.quadratic = 0.032f;
            light.cutOff = glm::cos(glm::radians(12.5f));

            d.shaderConfig.uniforms["light.constant"] = UniformValue(UniformType::FLOAT,    light.constant);
            d.shaderConfig.uniforms["light.linear"] = UniformValue(UniformType::FLOAT, light.linear);
            d.shaderConfig.uniforms["light.quadratic"] = UniformValue(UniformType::FLOAT, light.quadratic);

            d.shaderConfig.uniforms["material.ambient"] = UniformValue(UniformType::VEC3, material.ambient);
            d.shaderConfig.uniforms["material.diffuse"] = UniformValue(UniformType::INT,  0);
            d.shaderConfig.uniforms["material.specular"] = UniformValue(UniformType::INT,  1);
            d.shaderConfig.uniforms["material.specular"] = UniformValue(UniformType::VEC3, material.specular);
            d.shaderConfig.uniforms["material.shininess"] = UniformValue(UniformType::FLOAT, material.shininess);
        };


    srand(time(0));

    int BOUND_X = 30;
    int BOUND_Y = 30;
    int BOUND_Z = 30;


    for (int i = 0; i < cubes.size(); i++) {
        auto& cube = cubes[i];
        float x = rand() % (BOUND_X + 1 - (-BOUND_X)) + (-BOUND_X);
        float y = rand() % (BOUND_Y + 1 - (-BOUND_Y)) + (-BOUND_Y);
        float z = rand() % (BOUND_Z + 1 - (-BOUND_Z)) + (-BOUND_Z);
        cube.addTexture(wallText, 0);
        cube.setPosition(x, y, z);
    }

    obj.setPosition(0, -2, 0);
    epicT.setPosition(0, 0, 8);
    m_window.getCamera().SetPosition(glm::vec3(0, 0, 3));
    obj.setColor(glm::vec4(0, 1, 0, 0));
}

void App::run()
{
    while (isRunning())
    {
        processInput();
        update();
        render();
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

    light.position.y = sin(t) * 40;
    light.position.z = cos(t) * 40;

    m_window.getCamera().Update();

}

void App::render()
{
    m_window.clear(Color(0.1f, 0.1f, 0.1f, 1.f));

    for (int i = 0; i < cubes.size(); i++) {
        auto& cube = cubes[i];
        
        m_window.draw(cube, currentRenderData);
    }
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
    ImGui::SliderFloat3("Light Position", &light.position[0], -40.0f, 40.0f);
    ImGui::ColorEdit3("Light Ambient", &light.ambient[0]);
    ImGui::ColorEdit3("Light Diffuse", &light.diffuse[0]);
    ImGui::ColorEdit3("Light Specular", &light.specular[0]);

    // Material Controls
    ImGui::Text("Material Properties");
    ImGui::ColorEdit3("Material Ambient", &material.ambient[0]);
    ImGui::ColorEdit3("Material Diffuse", &material.diffuse[0]);
    ImGui::ColorEdit3("Material Specular", &material.specular[0]);
    ImGui::SliderFloat("Shininess", &material.shininess, 1.0f, 128.0f);

    ImGui::End();



    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}