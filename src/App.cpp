#include "App.hpp"
#include <glm/ext/matrix_clip_space.hpp>

bool calculateLightFlag = true;
bool calculateShadows = false;
bool calculateTorchLight = true;
bool hasTextureFlag = false;
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
    shadowMap(1024, 1024),
    m_skybox(faces),
    planeMesh(Utils::generatePlane(100, 100)),
    plane(&planeMesh, DrawMode::ELEMENTS),
    t("resources/earth2048.bmp")
{
    srand(777);
    initializeShaders();
    installLights();
    auto func = [&](Renderable& r, RenderData& d, Window& w) -> void 
        {
            const glm::mat4& proj = w.getProjectionMatrix();
            const glm::mat4& view = w.getViewMatrix();
            const glm::mat4& model = r.getModelMatrix();

            glm::mat4 mvp = proj * view * model;

            glm::vec3 cameraPos = w.getCamera().GetPosition();
            glm::vec3 camDir = w.getCamera().GetDirection();

            d.shaderProgram->setVec3("viewPos", cameraPos);
            d.shaderProgram->setMat4("model", model);
            //d.shaderProgram->setVec3("norm_matrix", cameraPos);
            d.shaderProgram->setMat4("mvpmatrix", mvp);

            d.shaderProgram->setVec3("viewPos", cameraPos);

            d.shaderProgram->setInt("numPointLights", (int)pointLights.size());
            d.shaderProgram->setInt("numSpotLights", (int)spotLights.size());

            for (size_t i = 0; i < pointLights.size(); i++) {
                std::string index = std::to_string(i);
                d.shaderProgram->setVec3("pointLights[" + index + "].position"   ,pointLights[i].position);

                d.shaderProgram->setFloat("pointLights[" + index + "].constant"  ,pointLights[i].constant);
                d.shaderProgram->setFloat("pointLights[" + index + "].linear"    ,pointLights[i].linear);
                d.shaderProgram->setFloat("pointLights[" + index + "].quadratic" ,pointLights[i].quadratic);

                d.shaderProgram->setVec3("pointLights[" + index + "].ambient", pointLights[i].ambient);
                d.shaderProgram->setVec3("pointLights[" + index + "].diffuse", pointLights[i].diffuse);
                d.shaderProgram->setVec3("pointLights[" + index + "].specular"   ,pointLights[i].specular);

            }

            for (size_t i = 0; i < spotLights.size(); i++) {
                std::string index = std::to_string(i);
                d.shaderProgram->setVec3("spotLights[" + index + "].position"     ,cameraPos            );
                d.shaderProgram->setVec3("spotLights[" + index + "].direction"    ,camDir               );

                d.shaderProgram->setFloat("spotLights[" + index + "].constant"    ,spotLights[i].constant);      
                d.shaderProgram->setFloat("spotLights[" + index + "].linear"      ,spotLights[i].linear);
                d.shaderProgram->setFloat("spotLights[" + index + "].quadratic"   ,spotLights[i].quadratic);
                d.shaderProgram->setFloat("spotLights[" + index + "].cutOff"      ,spotLights[i].cutOff);
                d.shaderProgram->setFloat("spotLights[" + index + "].outerCutOff" ,spotLights[i].outerCutOff);

                d.shaderProgram->setVec3("spotLights[" + index + "].ambient"      , spotLights[i].ambient);
                d.shaderProgram->setVec3("spotLights[" + index + "].diffuse"      , spotLights[i].diffuse);
                d.shaderProgram->setVec3("spotLights[" + index + "].specular"     , spotLights[i].specular);

            }

            d.shaderProgram->setVec3("dirLight.direction",   dirLight.direction);
            d.shaderProgram->setVec3("dirLight.ambient",     dirLight.ambient);
            d.shaderProgram->setVec3("dirLight.diffuse",     dirLight.diffuse);
            d.shaderProgram->setVec3("dirLight.specular",    dirLight.specular);

            d.shaderProgram->setVec4("objectColor", r.getColor());

            d.shaderProgram->setBool("calculateLight", calculateLightFlag);
            d.shaderProgram->setBool("calculateTorchLight", calculateTorchLight);
            d.shaderProgram->setBool("calculateShadows", calculateShadows);
            d.shaderProgram->setBool("hasTexture", hasTextureFlag);
        };

   
    m_window.getCamera().SetPosition(glm::vec3(0, 0, -8));
    c.setPosition(0, 0, 0);
    c.setColor(glm::vec4(255, 255, 0, 0));

    plane.setPosition(0, -1.5, 0);
    for (int i = 0; i < 9; ++i) {
        Cube cube;
        cube.setColor(glm::vec4(0.2f * i, 0.5f, 1.0f - 0.2f * i, 1.0f));
        orbitingCubes.push_back(cube);

        cubeRotAngles.push_back(0.0f);

        Axis axis = static_cast<Axis>(i % 3);
        cubeRotAxes.push_back(axis);

        float speed = (i % 2 == 0 ? 1.0f : -1.0f) * (1.6f + 0.6f * i);
        cubeRotSpeeds.push_back(speed);
    }

    
    currentRenderData.uniformUpdater = func;
  
    earth.addTexture(&t, 0);
}

void App::run()
{
    while (isRunning())
    {
        processInput();
        update(0.0005);
        renderShadows();
        render();
    }
}

void App::processInput() 
{
    m_window.processInput(0.005f);
    m_window.getCamera().Update();
    if (m_window.shouldClose())
        m_app_running = false;
    if (glfwGetKey(m_window.getWindowHandle(), GLFW_KEY_V) == GLFW_PRESS)
        calculateTorchLight = !calculateTorchLight;
}
void App::update(float dt)
{
    static float time = 0;
    time += dt;
    auto t = glfwGetTime();
    for (int i = 0; i < orbitingCubes.size(); ++i) {
        float angle = time + i * glm::radians(72.0f);
        float radius = 8.0f + i;

        float x = cos(angle) * radius;
        float z = sin(angle) * radius;

        orbitingCubes[i].setPosition(x, 0.0f, z);

        cubeRotAngles[i] += cubeRotSpeeds[i]  * 0.1;

        orbitingCubes[i].rotate(cubeRotAngles[i], cubeRotAxes[i]);
        earth.rotate(360 * sin(t), Axis::Y);
    }
}

void App::render()
{
    m_window.clear();


    m_window.draw(plane, currentRenderData);
    
    m_window.draw(c, currentRenderData);
    hasTextureFlag = true;
    m_window.draw(earth, currentRenderData);
    hasTextureFlag = false;
    for (auto& cube : orbitingCubes)
        m_window.draw(cube, currentRenderData);

    openGlFLags();
    m_window.display();
}


void App::renderImGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Shadow Map Controls");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void App::openGlFLags()
{
    //glPointSize(10.f);
    //glEnable(GL_POINT_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void App::initializeShaders()
{
    mainShader.addShader("shaders\\vert\\vertShader2.glsl", GL_VERTEX_SHADER);
    mainShader.addShader("shaders\\frag\\fragShader2.glsl", GL_FRAGMENT_SHADER);
    mainShader.linkProgram();

    pointsShader.addShader("shaders\\vert\\pointsShaderVert.glsl", GL_VERTEX_SHADER);
    pointsShader.addShader("shaders\\frag\\pointsShaderFrag.glsl", GL_FRAGMENT_SHADER);
    pointsShader.linkProgram();

    skyboxShader.addShader("shaders\\vert\\cubemapVert.glsl", GL_VERTEX_SHADER);
    skyboxShader.addShader("shaders\\frag\\cubemapFrag.glsl", GL_FRAGMENT_SHADER);
    skyboxShader.linkProgram();

    currentRenderData.shaderProgram = &mainShader;
}

void App::installLights()
{
    SpotLight light;
    light.position = { 0, 4, 5 };
    dirLight.direction = { 30, -10, 0 };

    dirLight.ambient =  {   0.2, 0.2, 0.2 };
    dirLight.diffuse =  {   0.2, 0.2, 0.2 };
    dirLight.specular = {   0.2, 0.2, 0.2 };

    light.constant = 2.f;
    light.linear = 0.09f;
    light.quadratic = 0.032f;
    light.cutOff = glm::cos(glm::radians(12.5f));
    light.outerCutOff = glm::cos(glm::radians(17.5));

    light.ambient = { 0.3f, 0.15f, 0.0f };
    light.diffuse = { 0.9f, 0.4f, 0.0f };
    light.specular = { 1.0f, 0.5f, 0.1f };



    PointLight pointLight;
    pointLight.position = { 0, 2, 3 };
    pointLight.ambient = { 0.9, 0.9, 0.9 };
    pointLight.diffuse = { 0.5, 0.5, 0.5 };
    pointLight.specular = { 0.3f, 0.3f, 0.3f };

    pointLight.constant = 1.0f;
    pointLight.linear = 0.092f;
    pointLight.quadratic = 0.032f;

    //pointLights.emplace_back(pointLight);
    spotLights.emplace_back(light);

}

void App::renderShadows()
{
    //glm::mat4 lightProjection = glm::ortho(
    //    -orthoSize, orthoSize,
    //    -orthoSize, orthoSize,
    //    lightNear, lightFar);
    //
    //glm::mat4 lightView = glm::lookAt(
    //    glm::vec3(0.0f, 1.0f, 0.0f),
    //    -dirLight.direction, 
    //    glm::vec3(0.0f, 1.0f, 0.0f));  
    //
    //lightSpaceMatrix = lightProjection * lightView;
    //shadowMap.BindForWrite();  
    //
    //glClear(GL_DEPTH_BUFFER_BIT);
    //
    //shadowShader.use();
    //shadowShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
    //
    //for (int i = 0; i < cubes.size(); i++) {
    //    auto& cube = cubes[i];
    //    shadowShader.setMat4("model",cube.getModelMatrix());
    //
    //    m_window.draw(cube, shadowShader);
    //}
    //shadowShader.setMat4("model", obj.getModelMatrix());
    //
    //m_window.draw(obj, shadowShader);
    //
    //shadowMap.Unbind();
    //glViewport(0, 0, m_window.getWidth(), m_window.getHeight());
}
