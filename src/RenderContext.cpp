#include "RenderContext.hpp"

RenderContext::RenderContext()
{
    if (!InitializeGLFW()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
}

RenderContext::~RenderContext()
{
    glfwTerminate();
}

void RenderContext::createContext(GLFWwindow* window)
{
    glfwMakeContextCurrent(window);
    if (!InitializeGLEW()) {
        throw std::runtime_error("Failed to initialize GLEW");
    }
}

bool RenderContext::InitializeGLFW()
{
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return false;
    }
    return true;
}

bool RenderContext::InitializeGLEW()
{
    if (glewInit() != GLEW_OK) {
        printf("Failed to initialize GLEW\n");
        return false;
    }
    return true;
}
