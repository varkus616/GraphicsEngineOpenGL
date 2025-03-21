#ifndef APP_HPP
#define APP_HPP
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <random>

#include <Shader.hpp>     
#include <Utilities.hpp>
#include <Window.hpp>
#include <Shapes.hpp>
#include <Light.hpp>

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
	void renderImGui();

	Window& m_window;
	
	Texture testTexture;
	Sphere sphere;

	Mesh	plane;
	Triangle epicT;

	RenderableObject sphereObj;

	RenderableObject obj;
	std::vector<Cube> cubes;
	RenderData currentRenderData;


	SpotLight light;
	DirLight dirLight;

	std::vector<PointLight> pointLights;
	std::vector<SpotLight> spotLights;

	Material material;
	bool m_app_running = true;

private:
	void installLights();
	void imguiRender();
};

#endif // !APP_HPP
