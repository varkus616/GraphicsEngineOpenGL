#ifndef APP_HPP
#define APP_HPP
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <random>

#include <Shader.hpp>     
#include <Texture.hpp>
#include <Utilities.hpp>
#include <Window.hpp>
#include <Shapes.hpp>
#include <RenderableObject.hpp>


class App
{
public:
	App(Window& window);
	~App() = default;

	void run();
	const bool isRunning()const { return m_app_running; }
	const Window& getWindow()const { return m_window; }
	
	void processInput();
	void update();
	void render();

	Window& m_window;
	
	Texture testTexture;
	Sphere sphere;
	RenderableObject shotgun;
	std::vector<Cube> cubes;
	RenderData currentRenderData;

	bool m_app_running = true;

private:
	void imguiRender();
};

#endif // !APP_HPP
