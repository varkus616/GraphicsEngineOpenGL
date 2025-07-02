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
#include <SimpleMesh.hpp>
#include <ResourceManager.hpp>	


class App
{
public:
	void run();
	App(Window& window);
	~App() = default;
private:

	const bool isRunning()const { return m_app_running; }
	const Window& getWindow()const { return m_window; }
	
	RenderData currentRenderData;
	Window& m_window;
	Cubemap m_skybox;
	
	std::vector<PointLight> pointLights;
	std::vector<SpotLight> spotLights;
	DirLight dirLight;

	Shader mainShader;
	Shader pointsShader;
	Shader shadowShader;
	Shader shadowView;
	Shader skyboxShader;

	ShadowMapFBO shadowMap;
	Cube c;
	Texture t;
	Sphere earth;
	Mesh planeMesh;
	RenderableObject plane;


	std::vector<Cube> orbitingCubes;
	std::vector<float> cubeRotAngles;
	std::vector<Axis> cubeRotAxes;
	std::vector<float> cubeRotSpeeds;

	bool m_app_running = true;
	
	void processInput();
	void update(float dt);
	void render();
	void renderShadows();
	void renderImGui();

	void initializeShaders();
	void installLights();
	void openGlFLags();
	void initShadows();
	void imguiRender();
};

#endif // !APP_HPP
