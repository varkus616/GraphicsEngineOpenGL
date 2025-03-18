#include "App.hpp"


glm::vec4 globalAmbient = { 0.7f, 0.7f, 0.7f, 1.0f };
glm::vec4 lightAmbient  = { 0.0f, 0.0f, 0.0f, 1.0f };
glm::vec4 lightDiffuse  = { 1.0f, 1.0f, 1.0f, 1.0f };
glm::vec4 lightSpecular = { 1.0f, 1.0f, 1.0f, 1.0f };


glm::vec4* matAmbient = Utils::goldAmbient();
glm::vec4* matDiffuse = Utils::goldDiffuse();
glm::vec4* matSpecular = Utils::goldSpecular();
float matShininess = Utils::goldShininess();
glm::vec3 currentLightPos = glm::vec3(0, 0, 0);

App::App(Window& window)
    :m_window(window),
    cubes(80),
    plane(Utils::generatePlane(100, 100)),
    obj(&plane, DrawMode::ELEMENTS),
    light(
        glm::vec3(0.0f, 0.0f, 0.0f), // Pozycja
        glm::vec3(0.0f, -1.0f, 0.0f), // Kierunek (œwieci w dó³)
        12.5f, 15.0f,                 // Cutoff wewnêtrzny i zewnêtrzny (miêkkie krawêdzie)
        glm::vec3(0.3f),              // Ambient
        glm::vec3(0.8f),              // Diffuse
        glm::vec3(1.0f),              // Specular
        1.0f, 0.09f, 0.032f           // T³umienie (attenuation)
    ),
    sphereObj(&sphere)
{
    currentRenderData.shaderProgram.addShader("shaders\\vert\\vertShader.glsl", GL_VERTEX_SHADER);
    currentRenderData.shaderProgram.addShader("shaders\\frag\\fragShader.glsl", GL_FRAGMENT_SHADER);
    currentRenderData.shaderProgram.linkProgram();


    glm::vec3 lightPosition = glm::vec3(m_window.getViewMatrix() * glm::vec4(currentLightPos, 1.0));


    currentRenderData.uniformUpdater = [&](Renderable& r, RenderData& d, Window& w) -> void 
        {
            const GLfloat t = (GLfloat)glfwGetTime();
            glm::mat4 mvmatrix = w.getViewMatrix() * r.getModelMatrix();
            glm::mat4 proj = w.getProjectionMatrix();
            
            glm::mat4 invTrMat = glm::transpose(glm::inverse(mvmatrix));

            d.shaderConfig.uniforms["mv_matrix"] = UniformValue(UniformType::MAT4, mvmatrix);
            d.shaderConfig.uniforms["proj_matrix"] = UniformValue(UniformType::MAT4, proj);
            d.shaderConfig.uniforms["norm_matrix"] = UniformValue(UniformType::MAT4, invTrMat);

            d.shaderConfig.uniforms["globalAmbient"     ]  = UniformValue(UniformType::VEC4, globalAmbient);
            d.shaderConfig.uniforms["light.ambient"     ]  = UniformValue(UniformType::VEC4, light.ambient);    //lightAmbient);
            d.shaderConfig.uniforms["light.diffuse"     ]  = UniformValue(UniformType::VEC4, light.diffuse);    //lightDiffuse);
            d.shaderConfig.uniforms["light.specular"    ]  = UniformValue(UniformType::VEC4, light.specular);   //lightSpecular);
            d.shaderConfig.uniforms["light.position"    ]  = UniformValue(UniformType::VEC3, light.position);   //lightPosition);

            d.shaderConfig.uniforms["material.ambient"  ]  = UniformValue(UniformType::VEC4, *matAmbient);
            d.shaderConfig.uniforms["material.diffuse"  ]  = UniformValue(UniformType::VEC4, *matDiffuse);
            d.shaderConfig.uniforms["material.specular" ]  = UniformValue(UniformType::VEC4, *matSpecular);
            d.shaderConfig.uniforms["material.shininess"]  = UniformValue(UniformType::FLOAT, matShininess);
        
        };
    
    Texture wallText = Texture(Utils::loadTexture("resources\\wall.jpg"));

    srand(time(0));
    
    int BOUND_X = 35;
    int BOUND_Y = 35;
    int BOUND_Z = 35;

    int min = -35;


    for (int i = 0; i < cubes.size(); i++) {
        auto& cube = cubes[i];
        float x = rand() % (BOUND_X  + 1 - min) + min;
        float y = rand() % (BOUND_Y  + 1 - min) + min;
        float z = rand() % (BOUND_Z  + 1 - min) + min;
        cube.setPosition(x, y, z);
    }
    obj.setPosition(0, 0, 0);

    epicT.setPosition(0, 0, 8);
    m_window.getCamera().SetPosition(glm::vec3(0, 0, 0));
    obj.setColor(glm::vec4(0,1,0,0));

    
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
    
    m_window.getCamera().Update();
    m_window.getCamera().CalcFrustumPlanes();
    light.position = m_window.getCamera().GetPosition();
    light.direction = m_window.getCamera().GetDirection();

}

void App::render()
{
    m_window.clear();

    for (int i = 0; i < cubes.size(); i++) {
        auto& cube = cubes[i];
        
        m_window.draw(cube, currentRenderData);
    }
    //m_window.draw(obj, currentRenderData);
    m_window.draw(sphereObj, currentRenderData);

    //m_window.draw(epicT, currentRenderData);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    imguiRender();

    m_window.display();
}

void App::imguiRender()
{
    //ImGui_ImplOpenGL3_NewFrame();
    //ImGui_ImplGlfw_NewFrame();
    //ImGui::NewFrame();
    //
    //ImGui::Begin("");
    //ImGui::End();
    //
    //ImGui::Render();
    //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
