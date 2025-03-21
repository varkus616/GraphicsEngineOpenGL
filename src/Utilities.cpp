#include "Utilities.hpp"
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <SOIL2/soil2.h>
#include <Mesh.hpp>
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

Mesh Utils::generatePlane(const int SIZE_X, const  int SIZE_Z)
{
    std::vector<Vertex> vertexes;
    std::vector<GLuint> indices;

    //GLuint* id = &indices[0];

    int count = 0;
    int HALF_SIZE_X = SIZE_X / 2;
    int HALF_SIZE_Z = SIZE_Z / 2;
    for (int i = 0; i <= SIZE_Z; i++) {
        for (int j = 0; j <= SIZE_X; j++) {
            
            Vertex v;
            v.Position.x = ((float(j) / (SIZE_X - 1)) * 2 - 1) * HALF_SIZE_X;
            v.Position.y = 0;
            v.Position.z = ((float(i) / (SIZE_Z - 1)) * 2 - 1) * HALF_SIZE_Z;

            v.TextureCoords = glm::vec2(float(j) / SIZE_X, float(i) / SIZE_Z);
            v.Normal = glm::vec3(0.0f, 1.0f, 0.0f); // Normal skierowany w górê
            v.VertexColors = glm::vec4(1.0f); // Bia³y kolor

            vertexes.push_back(v);
        }
    }
    
    for (int i = 0; i < SIZE_Z; i++) {
        for (int j = 0; j < SIZE_X; j++){
            int i0 = i * (SIZE_X + 1) + j;
            int i1 = i0 + 1;
            int i2 = i0 + (SIZE_X + 1);
            int i3 = i2 + 1;
            if ((j + i) % 2){
                indices.push_back(i0);
                indices.push_back(i2);
                indices.push_back(i1);


                indices.push_back(i1);
                indices.push_back(i2);
                indices.push_back(i3);

                //*id++ = i0; *id++ = i2; *id++ = i1;
                //*id++ = i1; *id++ = i2; *id++ = i3;
            }
            else {
                indices.push_back(i0);
                indices.push_back(i2);
                indices.push_back(i3);


                indices.push_back(i0);
                indices.push_back(i3);
                indices.push_back(i1);
                //*id++ = i0; *id++ = i2; *id++ = i3;
                //*id++ = i0; *id++ = i3; *id++ = i1;
            }
        }
    }

    return Mesh(vertexes, indices);
}

// GOLD material
glm::vec4* Utils::goldAmbient() { static glm::vec4 a = { 0.2473f, 0.1995f, 0.0745f, 1 }; return &a; }
glm::vec4* Utils::goldDiffuse() { static glm::vec4 a = { 0.7516f, 0.6065f, 0.2265f, 1 }; return &a; }
glm::vec4* Utils::goldSpecular() { static glm::vec4 a = { 0.6283f, 0.5558f, 0.3661f, 1 }; return &a; }
float Utils::goldShininess() { return 51.2f; }

// SILVER material - ambient, diffuse, specular, and shininess
float* Utils::silverAmbient() { static float a[4] = { 0.1923f, 0.1923f, 0.1923f, 1 }; return (float*)a; }
float* Utils::silverDiffuse() { static float a[4] = { 0.5075f, 0.5075f, 0.5075f, 1 }; return (float*)a; }
float* Utils::silverSpecular() { static float a[4] = { 0.5083f, 0.5083f, 0.5083f, 1 }; return (float*)a; }
float Utils::silverShininess() { return 51.2f; }

// BRONZE material - ambient, diffuse, specular, and shininess
float* Utils::bronzeAmbient() { static float a[4] = { 0.2125f, 0.1275f, 0.0540f, 1 }; return (float*)a; }
float* Utils::bronzeDiffuse() { static float a[4] = { 0.7140f, 0.4284f, 0.1814f, 1 }; return (float*)a; }
float* Utils::bronzeSpecular() { static float a[4] = { 0.3935f, 0.2719f, 0.1667f, 1 }; return (float*)a; }
float Utils::bronzeShininess() { return 25.6f; }