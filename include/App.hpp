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
#include <ShadowMapFBO.hpp>
#include <Cubemap.hpp>
#include <GenericRenderable.hpp>
#include <Physics.hpp>

class App
{
public:
	App(Window& window);
	~App() = default;

	void run();
	const bool isRunning()const { return m_app_running; }
	const Window& getWindow()const { return m_window; }
	
	void processInput();
	void update(float dt);
	void render();
	void renderShadows();
	void renderImGui();

	RenderData currentRenderData;
	Window& m_window;
	Cubemap m_skybox;

	DirLight dirLight;

	std::vector<PointLight> pointLights;
	std::vector<SpotLight> spotLights;

	Shader mainShader;
	Shader pointsShader;
	Shader shadowShader;
	Shader shadowView;
	Shader skyboxShader;

	ShadowMapFBO shadowMap;
	bool m_app_running = true;

	std::vector<Point> points;
	glm::vec3 gravitation;
	VertexBuffer pointsVBO;
	VertexArray pointsVAO;
	GenericRenderable pointsRenderable;

private:
	void calculateForces();
	void calculateEuler(float dt);
	void initializeShaders();
	void installLights();
	void openGlFLags();
	void initShadows();
	void imguiRender();
};

#endif // !APP_HPP
