#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) Utils::GLClearError();\
	x;\
	ASSERT(Utils::GLLogCall(#x, __FILE__, __LINE__));


#include "glm/glm.hpp"
#include <string>
#include <GL/glew.h>

class VertexBuffer;
class VertexArray;
class Mesh;
namespace Utils {
	Mesh generatePlane(const int SIZE_X, const  int SIZE_Z);
	void GLClearError();
	bool GLLogCall(const char* function, const char* file, int line);
	//std::vector<GLuint> generateIndicies(VertexBuffer& vb);

	GLuint loadTexture(const char* texImagePath);

	void filterMouseMoves(float dx, float dy);

	std::string mat4ToString(const glm::mat4& matrix);
	std::string mat3ToString(const glm::mat3& matrix);
	std::string vec2ToString(const glm::vec2& vector);
	std::string vec3ToString(const glm::vec3& vector);
	std::string vec4ToString(const glm::vec4& vector);

	glm::vec4* goldAmbient();
	glm::vec4* goldDiffuse();
	glm::vec4* goldSpecular();
	float  goldShininess();
	float* silverAmbient();
	float* silverDiffuse();
	float* silverSpecular();
	float  silverShininess();
	float* bronzeAmbient();
	float* bronzeDiffuse();
	float* bronzeSpecular();
	float  bronzeShininess();


}

#endif // ! UTILITIES_HPP
