#include "App.hpp"


void BasicUnifromUpdate(Renderable& r, RenderData& d, Window& w)
{
    glm::mat4 mvmatrix = w.getViewMatrix() * r.getModelMatrix();
    glm::mat4 proj = w.getProjectionMatrix();

    d.shaderConfig.uniforms["model_view_matrix"] = UniformValue(UniformType::MAT4, mvmatrix);
    d.shaderConfig.uniforms["projection_matrix"] = UniformValue(UniformType::MAT4, proj);
}


App::App(Window& window)
    :m_window(window),
    cubes(20)
{
    currentRenderData.shaderProgram.addShader("shaders\\vert\\vertShader.glsl", GL_VERTEX_SHADER);
    currentRenderData.shaderProgram.addShader("shaders\\frag\\fragShader.glsl", GL_FRAGMENT_SHADER);
    currentRenderData.shaderProgram.linkProgram();

    currentRenderData.layout.Push<float>(3);

    currentRenderData.setUniformUpdater(BasicUnifromUpdate);
    
    Texture wallText = Texture(Utils::loadTexture("resources\\wall.jpg"));

    sphere.textures.push_back(wallText);

    shotgun.setPosition(0, 0, -10);

    shotgun.loadModel("resources\\Shotgun_Pump_West.fbx");

    srand(time(0));
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
    m_window.processInput(0.45f);
    if (glfwWindowShouldClose(m_window.getWindowHandle()))
        m_app_running = false;
}

void App::update()
{
    float t = glfwGetTime();
    shotgun.rotate(sin(t) * 360, Axis::Y);

}

void App::render()
{
    m_window.clear();

    //for (int i = 0; i < cubes.size(); i++) {
    //    auto& cube = cubes[i];
    //
    //    glm::vec3 pos = cube.getPosition();
    //    glm::vec3 direction = glm::vec3(1);
    //    glm::vec3 movePos = pos + glm::vec3(1, 1, 1);
    //
    //    cube.setPosition(movePos.x, movePos.y, movePos.z);
    //
    //    m_window.draw(cube, currentRenderData);
    //}
                       
    m_window.draw(shotgun, currentRenderData);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    m_window.display();
}

