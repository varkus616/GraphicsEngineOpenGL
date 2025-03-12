#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "RenderContext.hpp"
#include "Color.hpp"
#include "RenderTarget.hpp"
#include "Renderable.hpp"
#include "RenderData.hpp"
#include "Camera.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class Window : public RenderTarget {
public:
    Window(RenderContext& context, int width, int height, const std::string& title);
    Window(RenderContext& context, int width, int height);
    Window(RenderContext& context);
    ~Window();

    const bool shouldClose() const;

    void clear(const Color& color = Color::Black) override;
    void display() override;

    void draw(Renderable& renderable, RenderData& data) override;
    void draw(const VertexBuffer& VBO, const IndexBuffer& EBO, RenderData& data) override;

    int getWidth() const;
    int getHeight() const;

    const std::string& getTitle() const;
    void setTitle(const std::string& title);

    void InitializeImGui(GLFWwindow* window);

    GLFWwindow* const getWindowHandle() const { return m_window; }

    // Camera methods
    void setCamera(const Camera& camera);
    Camera& getCamera();
    const Camera& getCamera() const;

    void processInput(float deltaTime); // For handling camera movement
    void processMouseMovement(float xoffset, float yoffset);
    void processMouseScroll(float yoffset);

    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewMatrix() const;

private:
    GLFWwindow* m_window;
    int m_width;
    int m_height;
    std::string m_title;

    Camera m_camera; // Camera object
    glm::mat4 m_projection_matrix;

    void initialize(GLFWwindow* window);

};

#endif // WINDOW_HPP