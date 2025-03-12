#include "Window.hpp"
#include <stdexcept>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"
#include "Utilities.hpp"
#include <functional>
#include "IndexBuffer.hpp"

Window::Window(RenderContext& context, int width, int height, const std::string& title)
    : m_width(width), m_height(height), m_title(title), m_camera(glm::vec3(0.f, 0.f, -8.f))
{
    m_projection_matrix = glm::ortho(0.0f, (float)m_width, (float)m_height, 0.0f, -1.0f, 1.0f);

    float aspect_ratio = getWidth() / getHeight();
    m_projection_matrix = glm::perspective(1.0472f, aspect_ratio, 0.1f, 1000.f);
    
    
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if (!m_window) {
        GLCall(glfwTerminate());
        throw std::runtime_error("Failed to create GLFW window");
    }
    
    context.createContext(m_window);
    initialize(m_window);
}

Window::Window(RenderContext& context, int width, int height)
    : Window(context, width, height, "Window") {}

Window::Window(RenderContext& context)
    : Window(context, 800, 600, "Window") {}

Window::~Window() {
    glfwDestroyWindow(m_window);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

void Window::initialize(GLFWwindow* window) {
    
    InitializeImGui(m_window);
    
    GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4));
    GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1));
    GLCall(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));
}

const bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_window);
}

void Window::clear(const Color& color) {
    GLCall(glClearColor(color.r, color.g, color.b, color.a));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Window::draw(Renderable& renderable, RenderData& data)
{
    if (data.uniformUpdater) {
        data.uniformUpdater(renderable, data, *this);
    } 

    data.shaderProgram.use();

    data.shaderConfig.apply(data.shaderProgram);

    renderable.draw(*this, data);
   
}

void Window::draw(const VertexBuffer& VBO, const IndexBuffer& EBO, RenderData& data) 
{
    switch (data.drawMode) {
    case DrawMode::ELEMENTS:
        switch (data.primitiveType) {
        case PrimitiveType::TRIANGLES:
            GLCall(glDrawElements(GL_TRIANGLES, EBO.GetSize() / sizeof(GLuint), GL_UNSIGNED_INT, nullptr));
            break;
        case PrimitiveType::QUADS:
            GLCall(glDrawElements(GL_QUADS, EBO.GetSize() , GL_UNSIGNED_INT, nullptr));
            break;
        default:
            break;
        }
        break;

    case DrawMode::ARRAYS:
        switch (data.primitiveType) {
        case PrimitiveType::TRIANGLES:
            GLCall(glDrawArrays(GL_TRIANGLES, 0, VBO.GetSize() / sizeof(GLfloat)));
            break;
        case PrimitiveType::QUADS:
            GLCall(glDrawArrays(GL_QUADS, 0, VBO.GetSize() / sizeof(GLfloat)));
            break;
        default:
            break;
        }
        break;

    case DrawMode::INSTANCED:
        switch (data.primitiveType)
        {
        case PrimitiveType::TRIANGLES:
            GLCall(glDrawArraysInstanced(GL_TRIANGLES, 0, VBO.GetSize() / sizeof(GLfloat), data.instancedDrawModeSize));            
            break;

        case PrimitiveType::QUADS:
            GLCall(glDrawArraysInstanced(GL_QUADS, 0, VBO.GetSize() / sizeof(GLfloat), data.instancedDrawModeSize));
            break;
        }
        break;
    default:
        std::cerr << "Error: No such drawMode" << std::endl;
        exit(1);
        break;
    }
}

void Window::display() {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

int Window::getWidth() const {
    return m_width;
}

int Window::getHeight() const {
    return m_height;
}

const std::string& Window::getTitle() const {
    return m_title;
}

void Window::setTitle(const std::string& title) {
    m_title = title;
    glfwSetWindowTitle(m_window, title.c_str());
}

void Window::InitializeImGui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 430");
}

void Window::setCamera(const Camera& camera) {
    m_camera = camera;
}

Camera& Window::getCamera() {
    return m_camera;
}

const Camera& Window::getCamera() const {
    return m_camera;
}

void Window::processInput(float deltaTime) {

    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);
    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
        m_camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
        m_camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
        m_camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
        m_camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_F) == GLFW_PRESS)
        m_camera.ProcessKeyboard(TOP, deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_G) == GLFW_PRESS)
        m_camera.ProcessKeyboard(DOWN, deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS)
        m_camera.ProcessKeyboard(ROT_RIGHT, deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS)
        m_camera.ProcessKeyboard(ROT_LEFT, deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_Z) == GLFW_PRESS)
        m_camera.ProcessKeyboard(ROT_BOT, deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_X) == GLFW_PRESS)
        m_camera.ProcessKeyboard(ROT_TOP, deltaTime);
}

void Window::processMouseMovement(float xoffset, float yoffset) {
    m_camera.ProcessMouseMovement(xoffset, yoffset);
}

void Window::processMouseScroll(float yoffset) {
    m_camera.ProcessMouseScroll(yoffset);
}

glm::mat4 Window::getProjectionMatrix() const {
    return m_projection_matrix;
}

glm::mat4 Window::getViewMatrix() const {
    return m_camera.GetViewMatrix();
}