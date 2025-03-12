#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <stdexcept>

class RenderContext {
public:
    RenderContext();

    ~RenderContext();

    void createContext(GLFWwindow* window);

    bool InitializeGLFW();

    bool InitializeGLEW();

};
