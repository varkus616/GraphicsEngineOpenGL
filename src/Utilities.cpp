#include "Utilities.hpp"
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <SOIL2/soil2.h>
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#define M_PI 3.14159265358979323846   


void Utils::GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool Utils::GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cerr << "[OpenGL Error] (" << error << "):" << function <<
			" " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

GLuint Utils::loadTexture(const char* texImagePath) {
    GLuint textureID;
    textureID = SOIL_load_OGL_texture(texImagePath,
        SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (textureID == 0) std::cout << "Warning: could not find texture file" << texImagePath << std::endl;
    GLCall(glBindTexture(GL_TEXTURE_2D, textureID));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));

    if (glewIsSupported("GL_EXT_texture_filter_anisotropic")) {
        GLfloat anisoSetting = 0.0f;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoSetting);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoSetting);
    }


    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    return textureID;
}


VertexBuffer Utils::createRectangle(float width, float height) {
    float vertices[] = {
        0.0f, 0.0f,    
        width, 0.0f,   
        width, height, 
        0.0f, height   
    };
       
    return VertexBuffer(vertices, sizeof(vertices));
}

VertexBuffer Utils::createCircle(float radius, int num_segments)
{
    float* vertices = new float[num_segments * 2];
    Utils::generateCircleVertices(vertices, num_segments, radius);
    
    VertexBuffer vb(vertices, sizeof(vertices));
    delete vertices;
    return vb;
}

void Utils::generateCircleVertices(float* vertices, int segments, float radius) {
    float angleStep = 2.0f * M_PI / segments;
    for (int i = 0; i < segments; ++i) {
        float angle = i * angleStep;
        vertices[2 * i] = radius * cos(angle);
        vertices[2 * i + 1] = radius * sin(angle);
    }
}

std::string Utils::mat4ToString(const glm::mat4& matrix)
{
    std::ostringstream oss;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            oss << matrix[i][j];
            if (j < 3) oss << ", "; // Dodaj przecinek miêdzy elementami w wierszu
        }
        if (i < 3) oss << "\n"; // Dodaj now¹ liniê miêdzy wierszami
    }
    return oss.str();
}

std::string Utils::mat3ToString(const glm::mat3& matrix)
{
    std::ostringstream oss;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            oss << matrix[i][j];
            if (j < 2) oss << ", "; // Dodaj przecinek miêdzy elementami w wierszu
        }
        if (i < 2) oss << "\n"; // Dodaj now¹ liniê miêdzy wierszami
    }
    return oss.str();
}
std::string Utils::vec2ToString(const glm::vec2& vector)
{
    std::ostringstream oss;
    oss << vector.x << ", " << vector.y;
    return oss.str();
}

std::string Utils::vec3ToString(const glm::vec3& vector)
{
    std::ostringstream oss;
    oss << vector.x << ", " << vector.y << ", " << vector.z;
    return oss.str();
}

std::string Utils::vec4ToString(const glm::vec4& vector)
{
    std::ostringstream oss;
    oss << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w;
    return oss.str();
}

// Konwertuje pozycjê w oknie na znormalizowane wspó³rzêdne urz¹dzenia (NDC) dla osi X, Y i Z
glm::vec3 Utils::windowToNDC(int x, int y, float z, int windowWidth, int windowHeight) {
    float ndcX = 2.0f * x / windowWidth - 1.0f;
    float ndcY = 1.0f - 2.0f * y / windowHeight;
    float ndcZ = 2.0f * z - 1.0f;
    return glm::vec3(ndcX, ndcY, ndcZ);
}

// Konwertuje znormalizowane wspó³rzêdne urz¹dzenia (NDC) na pozycjê w oknie dla osi X, Y i Z
glm::vec3 Utils::ndcToWindow(float ndcX, float ndcY, float ndcZ, int windowWidth, int windowHeight) {
    int x = (ndcX + 1.0f) * 0.5f * windowWidth;
    int y = (1.0f - ndcY) * 0.5f * windowHeight;
    float z = (ndcZ + 1.0f) * 0.5f;
    return glm::vec3(x, y, z);
}
