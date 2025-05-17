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
    shadowMap(1024, 1024),
    m_skybox(faces)
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
            d.shaderProgram->setBool("calculateShadows", calculateShadows);
            d.shaderProgram->setBool("hasTexture", hasTextureFlag);
        };

    auto pointfunc = [&](Renderable& r, RenderData& d, Window& w)
        {
            d.shaderProgram->setMat4("projectionMatrix", w.getOrthographicMatrix());
            d.shaderProgram->setMat4("viewMatrix", glm::mat4(1)); //w.getViewMatrix());
        };  
    m_window.getCamera().SetPosition(glm::vec3(0, 0, -8));
    c.setPosition(0, 0, 0);
    c.setColor(glm::vec4(255, 255, 0, 0));
    
    //`int pointCount = 50;
    //`float screenWidth = static_cast<float>(m_window.getWidth());
    //`float step = screenWidth / (pointCount - 1);
    //`for (int i = 0; i < pointCount; ++i) {
    //`    float x = i * step;
    //`    float y = m_window.getHeight(); 
    //`    Point p(x, y * 0.02, 0.0f);
    //`    p.mass = 1.f;
    //`    p.invMass = 1.f / p.mass;
    //`    points.push_back(p); 
    //`}

    currentRenderData.uniformUpdater = func;
    //currentRenderData.drawMode = DrawMode::ARRAYS;
    //currentRenderData.primitiveType = PrimitiveType::POINTS;

    //VertexBufferLayout layout;
    //layout.Push<GLfloat>(3);
    //pMesh.setBufferType(GL_ARRAY_BUFFER);
    //pMesh.setData(points, GL_DYNAMIC_DRAW);
    //pMesh.setupBuffers(layout);
    //pointsRenderable.setMesh(&pMesh);

    //gravitation.y = 1;
    //
    //sfera.pos.x = m_window.getWidth() / 2;
    //sfera.pos.y = m_window.getHeight() / 2;
    //sfera.tlum = 0;
    //sfera.R = 200;
    
    //s.setPosition(0, 0, -8);
}

void App::calculateForces()
{
    //for (auto& point : points)
    //{
    //    if ( !(point.flag & P_ZAW))
    //    {
    //        point.force = gravitation * point.mass;
    //    }
    //}
}

void App::calculateEuler(float dt)
{
    //for (auto& point : points)
    //{
    //    if (!(point.flag & P_ZAW))
    //    {
    //        point.dv = W_Euler(point.force * point.invMass, dt);
    //        point.speed += point.dv;
    //        point.dr = point.speed * dt;
    //        point.position += point.dr;
    //    }
    //}
}

void App::run()
{
    while (isRunning())
    {
        processInput();
        //update(0.005);
        renderShadows();
        render();
    }
}

void App::processInput() 
{
    m_window.processInput(0.05f);
    m_window.getCamera().Update();
    if (m_window.shouldClose())
        m_app_running = false;
}

void App::update(float dt)
{   
    
    calculateForces();
    calculateEuler(dt);
    
    //for (auto& p : points) {
    //    if (p.position.x < 0) {
    //        p.position.x = 0;
    //        p.speed.x *= -1;
    //    }
    //    if (p.position.x > m_window.getWidth()) {
    //        p.position.x = m_window.getWidth();
    //        p.speed.x *= -1;
    //    }
    //    if (p.position.y < 0) {
    //        p.position.y = 0;
    //        p.speed.y *= -1;
    //    }
    //    if (p.position.y > m_window.getHeight()) {
    //        p.position.y = m_window.getHeight();
    //        p.speed.y *= -1;
    //    }
    //
    //    glm::vec3 d = sfera.pos - p.position;
    //   
    //    if (glm::length(d) - sfera.R < 0)
    //    {
    //        glm::vec3 n = (sfera.pos - p.position);
    //        n = glm::normalize(n);
    //        glm::vec3 z = d - sfera.R;
    //        p.position = p.position + n * z;
    //
    //        glm::vec3 Vn = n * (n * p.speed);
    //        glm::vec3 Vs = p.speed - Vn;
    //
    //        p.speed = (Vs - Vn*sfera.tlum);
    //    }
    //}
    //
    //std::vector<glm::vec3> positionsOnly;
    //positionsOnly.reserve(points.size());
    //for (const auto& p : points) {
    //    positionsOnly.push_back(p.position);
    //}
    //
    //pMesh.updateData(positionsOnly);

    //currentRenderData.vertexCount = points.size();
}

void App::render()
{
   m_window.clear();
   std::cout << c.getPosition().x << c.getPosition().x << c.getPosition().x << std::endl;
   m_window.draw(c, currentRenderData);
   
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
