#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include <RenderContext.hpp>
#include <Color.hpp>
#include <RenderTarget.hpp>
#include <Renderable.hpp>
#include <RenderData.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <FreeCamera.hpp>
#include <TargetCamera.hpp>

#include <VertexArray.hpp>

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
    void draw(const VertexArray& VAO, RenderData& data) override;
    void drawGeneric(const VertexArray& VAO, RenderData& data);
    int getWidth() const;
    int getHeight() const;

    const std::string& getTitle() const;
    void setTitle(const std::string& title);

    void InitializeImGui(GLFWwindow* window);
    void mouseCallback(double xpos, double ypos);
    GLFWwindow* const getWindowHandle() const { return m_window; }

    // Camera methods
    void setCamera(const CFreeCamera& camera);
    CFreeCamera& getCamera() { return m_camera; }

    void processInput(float deltaTime); // For handling camera movement
    void processMouseMovement(float xoffset, float yoffset);
    void processMouseScroll(float yoffset);

    const glm::mat4& getProjectionMatrix() const;
    const glm::mat4& getOrthographicMatrix() const;
    const glm::mat4& getViewMatrix() const;

private:
    GLFWwindow* m_window;
    int m_width;
    int m_height;
    std::string m_title;
    bool m_enableMouseControl = true; // Domy�lnie mysz kontroluje kamer�

    CFreeCamera m_camera;
    glm::mat4 m_projection_matrix;
    glm::mat4 m_orthographic_matrix;
    void initialize(GLFWwindow* window);

};

#endif // WINDOW_HPP