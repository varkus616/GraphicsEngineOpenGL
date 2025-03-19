#include "App.hpp"


glm::vec4 globalAmbient = { 0.7f, 0.7f, 0.7f, 1.0f };
glm::vec4 lightAmbient  = { 1.f, 1.f, 1.f, 1.0f };
glm::vec4 lightDiffuse  = { 1.0f, 1.0f, 1.0f, 1.0f };
glm::vec4 lightSpecular = { 1.0f, 1.0f, 1.0f, 1.0f };

glm::vec3 objectColor = {1.f, 0.5f, 0.31f};

glm::vec4* matAmbient = Utils::goldAmbient();
glm::vec4* matDiffuse = Utils::goldDiffuse();
glm::vec4* matSpecular = Utils::goldSpecular();
float matShininess = Utils::goldShininess();
glm::vec3 lightPosition = glm::vec3(1.2f, 1.f, 2.f);//glm::vec3(m_window.getViewMatrix() * glm::vec4(currentLightPos, 1.0));

App::App(Window& window)
    :m_window(window),
    cubes(1),
    plane(Utils::generatePlane(100, 100)),
    obj(&plane, DrawMode::ELEMENTS),
   
    sphereObj(&sphere)
{
    currentRenderData.shaderProgram.addShader("shaders\\vert\\vertShader.glsl", GL_VERTEX_SHADER);
    currentRenderData.shaderProgram.addShader("shaders\\frag\\fragShader.glsl", GL_FRAGMENT_SHADER);
    currentRenderData.shaderProgram.linkProgram();




    currentRenderData.uniformUpdater = [&](Renderable& r, RenderData& d, Window& w) -> void 
        {
            const GLfloat t = (GLfloat)glfwGetTime();
            glm::mat4 mvmatrix = w.getViewMatrix() * r.getModelMatrix();
            glm::mat4 proj = w.getProjectionMatrix();
            
            glm::mat4 invTrMat = glm::transpose(glm::inverse(mvmatrix));

            d.shaderConfig.uniforms["mv_matrix"] = UniformValue(UniformType::MAT4, mvmatrix);
            d.shaderConfig.uniforms["view"] = UniformValue(UniformType::MAT4, w.getViewMatrix());
            d.shaderConfig.uniforms["model"] = UniformValue(UniformType::MAT4, r.getModelMatrix());
            d.shaderConfig.uniforms["proj_matrix"] = UniformValue(UniformType::MAT4, proj);
            d.shaderConfig.uniforms["norm_matrix"] = UniformValue(UniformType::MAT4, invTrMat);
            
            d.shaderConfig.uniforms["objectColor"] = UniformValue(UniformType::VEC3, objectColor);

            //d.shaderConfig.uniforms["globalAmbient"     ]  = UniformValue(UniformType::VEC4, globalAmbient);
            d.shaderConfig.uniforms["lightAmbient"      ]  = UniformValue(UniformType::VEC4, lightAmbient);    //lightAmbient);
            d.shaderConfig.uniforms["lightDiffuse"     ]  = UniformValue(UniformType::VEC4, lightDiffuse);    //lightDiffuse);
            //d.shaderConfig.uniforms["light.specular"    ]  = UniformValue(UniformType::VEC4, lightSpecular);   //lightSpecular);
            d.shaderConfig.uniforms["lightPosition"    ]  = UniformValue(UniformType::VEC3, lightPosition);   //lightPosition);

            //d.shaderConfig.uniforms["material.ambient"  ]  = UniformValue(UniformType::VEC4, *matAmbient);
            //d.shaderConfig.uniforms["material.diffuse"  ]  = UniformValue(UniformType::VEC4, *matDiffuse);
            //d.shaderConfig.uniforms["material.specular" ]  = UniformValue(UniformType::VEC4, *matSpecular);
            //d.shaderConfig.uniforms["material.shininess"]  = UniformValue(UniformType::FLOAT, matShininess);
        
        };
    
    Texture wallText = Texture(Utils::loadTexture("resources\\wall.jpg"));

    srand(time(0));
    
    int BOUND_X = 35;
    int BOUND_Y = 35;
    int BOUND_Z = 35;

    int min = -35;

    for (int i = 0; i < cubes.size(); i++) {
        auto& cube = cubes[i];
        //float x = rand() % (BOUND_X  + 1 - min) + min;
        //float y = rand() % (BOUND_Y  + 1 - min) + min;
        //float z = rand() % (BOUND_Z  + 1 - min) + min;
        cube.setPosition(1, 0, 3);
    }
    obj.setPosition(0, -2, 0);

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

}

void App::render()
{
    m_window.clear(Color(0.1f, 0.1f, 0.1f, 1.f));

    for (int i = 0; i < cubes.size(); i++) {
        auto& cube = cubes[i];
        
        m_window.draw(cube, currentRenderData);
    }
    //m_window.draw(obj, currentRenderData);

    //m_window.draw(epicT, currentRenderData);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Testing Ground");
    
    ImGui::BeginChild("Light", ImVec2(0, 100), true);
    ImGui::Text("Ambient");
    ImGui::InputFloat("R", &lightAmbient.r);
    ImGui::InputFloat("G", &lightAmbient.g);
    ImGui::InputFloat("B", &lightAmbient.b);
    ImGui::InputFloat("A", &lightAmbient.a);
    ImGui::InputFloat("ObjectColor R", &objectColor.r);
    ImGui::InputFloat("ObjectColor G", &objectColor.g);
    ImGui::InputFloat("ObjectColor B", &objectColor.b);

    ImGui::SliderFloat("POS Z", &lightPosition.x, -10.0f, 10.0f);
    ImGui::SliderFloat("POS X", &lightPosition.y, -10.0f, 10.0f);
    ImGui::SliderFloat("POS Y", &lightPosition.z, -10.0f, 10.0f);

    //ImGui::Text("Diffuse");
    //ImGui::InputFloat("R", &lightDiffuse.r);
    //ImGui::InputFloat("G", &lightDiffuse.g);
    //ImGui::InputFloat("B", &lightDiffuse.b);
    //ImGui::InputFloat("A", &lightDiffuse.a);
    //
    //ImGui::Text("Specular");
    //ImGui::InputFloat("R", &lightSpecular.r);
    //ImGui::InputFloat("G", &lightSpecular.g);
    //ImGui::InputFloat("B", &lightSpecular.b);
    //ImGui::InputFloat("A", &lightSpecular.a);

    ImGui::EndChild();

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    

    m_window.display();
}

void App::imguiRender()
{
    
    
    
    
    
    
    
    
    
}
