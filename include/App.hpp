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
	void renderShadows();
	void renderImGui();

	Window& m_window;
	
	Texture testTexture;
	Sphere sphere;

	Mesh	plane;

	RenderableObject miku;


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
	Shader shadowShader;
	Shader basicShader;
	Shader shadowView;
	Shader skyboxShader;

	ShaderConfig shadowShaderConfig;

	ShadowMapFBO shadowMap;
	unsigned int quadVAO, quadVBO;
	unsigned int textureColorbuffer;
	float w = m_window.getWidth();
	float h = m_window.getHeight();
	// W sekcji private klasy App
	//m_window.getCamera().GetNearPlane();
	//m_window.getCamera().GetFarPlane();
	float orthoSize = 120.0f;
	float lightNear = 1;
	float lightFar = 1500;

	glm::vec3 lightTarget;
	bool m_app_running = true;

	
	Cubemap m_skybox;


private:
	void installLights();
	void openGlFLags();
	void initShadows();
	void imguiRender();
};

#endif // !APP_HPP
