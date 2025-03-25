#include "Window.hpp"
#include <stdexcept>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"
#include "Utilities.hpp"
#include "IndexBuffer.hpp"
#include <functional>

Window::Window(RenderContext& context, int width, int height, const std::string& title)
    : m_width(width), m_height(height), m_title(title)
{

    float aspect_ratio = getWidth() / getHeight();
    m_camera.SetupProjection(90, aspect_ratio, 0.1f, 1000.f);
    
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if (!m_window) {
        GLCall(glfwTerminate());
        throw std::runtime_error("Failed to create GLFW window");
    }
    
    context.createContext(m_window);
    initialize(m_window);

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
        static_cast<Window*>(glfwGetWindowUserPointer(window))->mouseCallback(xpos, ypos);
        });
    glfwSetWindowUserPointer(m_window, this);
}

Window::Window(RenderContext& context, int width, int height)
    : Window(context, width, height, "Window") {}

Window::Window(RenderContext& context)
    : Window(context, 800, 600, "Window") {}

Window::~Window() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::initialize(GLFWwindow* window) {

    GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4));
    GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
    GLCall(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Ustawienie backendów (dla OpenGL + GLFW)
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 430");
    ImGui::StyleColorsDark();
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
    if (data.uniformUpdater) 
        data.uniformUpdater(renderable, data, *this);

    data.shaderProgram.use();

    data.shaderConfig.apply(data.shaderProgram);

    renderable.draw(*this, data);
}

void Window::draw(Renderable& renderable, Shader& shader)
{

    shader.use();
    RenderData data;
    data.drawMode = DrawMode::ARRAYS;
    data.primitiveType = PrimitiveType::TRIANGLES;
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
            GLCall(glDrawElements(GL_QUADS, EBO.GetSize() / sizeof(GLuint), GL_UNSIGNED_INT, nullptr));
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

void Window::processInput(float deltaTime) {
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);

    if (glfwGetKey(m_window, GLFW_KEY_T) == GLFW_PRESS) {
        m_enableMouseControl = !m_enableMouseControl; // Prze³¹czanie kontroli myszy
        glfwSetInputMode(m_window, GLFW_CURSOR, m_enableMouseControl ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }

    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
        m_camera.Walk(deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
        m_camera.Walk(-deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
        m_camera.Strafe(-deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
        m_camera.Strafe(deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_F) == GLFW_PRESS)
        m_camera.Lift(deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_G) == GLFW_PRESS)
        m_camera.Lift(-deltaTime);

    if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS)
        m_camera.Rotate(deltaTime, 0, 0);
    if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS)
        m_camera.Rotate(-deltaTime, 0, 0);

    if (glfwGetKey(m_window, GLFW_KEY_Z) == GLFW_PRESS)
        m_camera.Rotate(0, deltaTime, 0);
    if (glfwGetKey(m_window, GLFW_KEY_X) == GLFW_PRESS)
        m_camera.Rotate(0, -deltaTime, 0);

    if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS) {
        m_camera.ResetRotation();
        m_camera.SetPosition(glm::vec3(0.f, 0.f, 0.f));
    }


}
void Window::mouseCallback(double xpos, double ypos) {
    processMouseMovement(static_cast<float>(xpos), static_cast<float>(ypos));
}

void Window::processMouseMovement(float xpos, float ypos) {
    if (!m_enableMouseControl) return;

    static float lastX = m_width / 2.0f;
    static float lastY = m_height / 2.0f;
    static bool firstMouse = true;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    m_camera.Rotate(-xoffset, -yoffset, 0.0f);
}

void Window::processMouseScroll(float yoffset) {
}

glm::mat4 Window::getProjectionMatrix() const {
    return m_camera.GetProjectionMatrix();
}

glm::mat4 Window::getViewMatrix() const {
    return m_camera.GetViewMatrix();
}