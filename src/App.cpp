#include "App.hpp"
#include <glm/ext/matrix_clip_space.hpp>

bool calculateLightFlag = true;
bool calculateShadows = false;
bool hasTextureFlag = true;
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
    cubes(100),
    plane(Utils::generatePlane(100, 100)),
    obj(&plane, DrawMode::ELEMENTS),
    shadowMap(1024, 1024),
    m_skybox(faces)
{
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

            d.shaderProgram.setVec3("viewPos", cameraPos);
            d.shaderProgram.setMat4("model", model);
            //d.shaderProgram.setVec3("norm_matrix", cameraPos);
            d.shaderProgram.setMat4("mvpmatrix", mvp);

            d.shaderProgram.setVec3("viewPos", cameraPos);

            d.shaderProgram.setInt("numPointLights", (int)pointLights.size());
            d.shaderProgram.setInt("numSpotLights", (int)spotLights.size());

            for (size_t i = 0; i < pointLights.size(); i++) {
                std::string index = std::to_string(i);
                d.shaderProgram.setVec3("pointLights[" + index + "].position"   ,pointLights[i].position);

                d.shaderProgram.setFloat("pointLights[" + index + "].constant"  ,pointLights[i].constant);
                d.shaderProgram.setFloat("pointLights[" + index + "].linear"    ,pointLights[i].linear);
                d.shaderProgram.setFloat("pointLights[" + index + "].quadratic" ,pointLights[i].quadratic);

                d.shaderProgram.setVec3("pointLights[" + index + "].ambient"    ,pointLights[i].ambient);
                d.shaderProgram.setVec3("pointLights[" + index + "].diffuse"    ,pointLights[i].diffuse);
                d.shaderProgram.setVec3("pointLights[" + index + "].specular"   ,pointLights[i].specular);

            }

            for (size_t i = 0; i < spotLights.size(); i++) {
                std::string index = std::to_string(i);
                d.shaderProgram.setVec3("spotLights[" + index + "].position"     ,cameraPos            );
                d.shaderProgram.setVec3("spotLights[" + index + "].direction"    ,camDir               );

                d.shaderProgram.setFloat("spotLights[" + index + "].constant"    ,spotLights[i].constant);      
                d.shaderProgram.setFloat("spotLights[" + index + "].linear"      ,spotLights[i].linear);
                d.shaderProgram.setFloat("spotLights[" + index + "].quadratic"   ,spotLights[i].quadratic);
                d.shaderProgram.setFloat("spotLights[" + index + "].cutOff"      ,spotLights[i].cutOff);
                d.shaderProgram.setFloat("spotLights[" + index + "].outerCutOff" ,spotLights[i].outerCutOff);

                d.shaderProgram.setVec3("spotLights[" + index + "].ambient"      , spotLights[i].ambient);
                d.shaderProgram.setVec3("spotLights[" + index + "].diffuse"      , spotLights[i].diffuse);
                d.shaderProgram.setVec3("spotLights[" + index + "].specular"     , spotLights[i].specular);

            }

            d.shaderProgram.setVec3("dirLight.direction",   dirLight.direction);
            d.shaderProgram.setVec3("dirLight.ambient",     dirLight.ambient);
            d.shaderProgram.setVec3("dirLight.diffuse",     dirLight.diffuse);
            d.shaderProgram.setVec3("dirLight.specular",    dirLight.specular);

            d.shaderProgram.setVec4("objectColor", r.getColor());

            d.shaderProgram.setBool("calculateLight", calculateLightFlag);
            d.shaderProgram.setBool("calculateShadows", calculateShadows);
            d.shaderProgram.setBool("hasTexture", hasTextureFlag);
        };

    currentRenderData.uniformUpdater = func;

    srand(777);

    randomCubes();

    m_window.getCamera().SetPosition(glm::vec3(0, 1, 3));
    s.addTexture(&earthText, 0);
    Miku.loadModel("resources\\crusader.max");
    Miku2.loadModel("resources\\miku.obj");
    Miku.m_drawMode = DrawMode::ELEMENTS;
    Miku.m_primType = PrimitiveType::TRIANGLES;
    Miku2.m_drawMode = DrawMode::ELEMENTS;
    Miku2.m_primType = PrimitiveType::TRIANGLES;
    Miku.setColor(glm::vec4(1, 0, 1, 1));
    
    Miku.setPosition(2,0,0);
    Miku.rotate(-90, Axis::X);
    Miku.addTexture(&wallText, 0);
    Miku.addTexture(&mikuText2, 1);
    Miku.addTexture(&mikuText, 2);

    Miku2.addTexture(&wallText, 0);
    Miku2.addTexture(&wallText, 1);
    Miku2.addTexture(&wallText, 2);
    Miku2.setScale(0.1, 0.1, 0.1);

   // Miku.setScale(0.1f, 0.1f, 0.1f);  // Dostosuj skalê

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

void App::run()
{
    while (isRunning())
    {
        processInput();
        update();
        renderShadows();
        render();
        printFPS();
    }
}

void App::processInput() 
{
    m_window.processInput(0.05f);
    if (m_window.shouldClose())
        m_app_running = false;
}

void App::update()
{
    float t = glfwGetTime();

    m_window.getCamera().Update();
   // s.setAngle(sin(t) * 180);
}

void App::render()
{
   m_window.clear();

   //currentRenderData.shaderProgram.use();
   //shadowMap.BindForRead(GL_TEXTURE0);
   //
   //currentRenderData.shaderProgram.setInt("shadowMap", 0);
   //currentRenderData.shaderProgram.setMat4("lightSpaceMatrix", lightSpaceMatrix);
   
   m_skybox.render(skyboxShader, m_window.getViewMatrix(), m_window.getCamera().GetProjectionMatrix());
   //currentRenderData.shaderProgram.setBool("hasTexture", hasTextureFlag);

   for (int i = 0; i < cubes.size(); i++) {
       auto& cube = cubes[i];
       
       m_window.draw(cube, currentRenderData);
   }
   m_window.draw(s, currentRenderData);
   m_window.draw(Miku, currentRenderData);
   hasTextureFlag = false;
   m_window.draw(Miku2, currentRenderData);
   hasTextureFlag = true;

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
    //glEnable(GL_CULL_FACE);glCullFace(GL_BACK);glFrontFace(GL_CW);
    glDepthFunc(GL_LEQUAL);
}

void App::randomCubes()
{
    int BOUND_X = 15;
    int BOUND_Y = 0;
    int BOUND_Z = 15;

    for (int i = 0; i < cubes.size(); i++) {
        auto& cube = cubes[i];
    
        // Losowanie pozycji
        float x = rand() % (BOUND_X + 1 - (-BOUND_X)) + (-BOUND_X);
        float y = rand() % (BOUND_Y + 1 - (-BOUND_Y)) + (-BOUND_Y);
        float z = rand() % (BOUND_Z + 1 - (-BOUND_Z)) + (-BOUND_Z);
    
        cube.addTexture(&wallText, 0);
        cube.setPosition(x, y + 2.55, z);
    
        float angleX = rand() % 360;
        float angleY = rand() % 360;
        float angleZ = rand() % 360;
    
        cube.rotate(angleX, Axis::X);
        cube.rotate(angleY, Axis::Y);
        cube.rotate(angleZ, Axis::Z);
        x = rand() % 255;
        y = rand() % 255;
        z = rand() % 255;
    
        cube.setColor(glm::vec4(1, 0, 0, 0));
    }
}

void App::initializeShaders()
{

    currentRenderData.shaderProgram.addShader("shaders\\vert\\vertShader2.glsl", GL_VERTEX_SHADER);
    currentRenderData.shaderProgram.addShader("shaders\\frag\\fragShader2.glsl", GL_FRAGMENT_SHADER);
    currentRenderData.shaderProgram.linkProgram();

    //shadowView.addShader("shaders\\vert\\viewShadowVert.glsl", GL_VERTEX_SHADER);
    //shadowView.addShader("shaders\\frag\\viewShadowFrag.glsl", GL_FRAGMENT_SHADER);
    //shadowView.linkProgram();

    //shadowShader.addShader("shaders\\vert\\shadowsVert.glsl", GL_VERTEX_SHADER);
    //shadowShader.addShader("shaders\\frag\\shadowsFrag.glsl", GL_FRAGMENT_SHADER);
    //shadowShader.linkProgram();

    skyboxShader.addShader("shaders\\vert\\cubemapVert.glsl", GL_VERTEX_SHADER);
    skyboxShader.addShader("shaders\\frag\\cubemapFrag.glsl", GL_FRAGMENT_SHADER);
    skyboxShader.linkProgram();
}

void App::installLights()
{
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

    //pointLights.emplace_back(pointLight);
    spotLights.emplace_back(light);

}
