#pragma once
#include <vector>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader;

class Cubemap {
private:
    unsigned int m_textureID;
    static unsigned int skyboxVAO, skyboxVBO;
    static bool initialized;
    static const float skyboxVertices[108];

    static void initializeSkybox();

public:
    Cubemap(const std::vector<std::string>& faces);
    ~Cubemap();

    void render(Shader& skyboxShader, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
    unsigned int getID() const { return m_textureID; }
};