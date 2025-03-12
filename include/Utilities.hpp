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
namespace Utils {
	void GLClearError();
	bool GLLogCall(const char* function, const char* file, int line);
	//std::vector<GLuint> generateIndicies(VertexBuffer& vb);

	GLuint loadTexture(const char* texImagePath);

	VertexBuffer createRectangle(float width, float height);
	VertexBuffer createCircle(float radius, int num_segments);
	void generateCircleVertices(float* vertices, int segments, float radius);

	glm::vec3 windowToNDC(int x, int y, float z, int windowWidth, int windowHeight);
	glm::vec3 ndcToWindow(float ndcX, float ndcY, float ndcZ, int windowWidth, int windowHeight);

	std::string mat4ToString(const glm::mat4& matrix);
	std::string mat3ToString(const glm::mat3& matrix);
	std::string vec2ToString(const glm::vec2& vector);
	std::string vec3ToString(const glm::vec3& vector);
	std::string vec4ToString(const glm::vec4& vector);
}
#endif // ! UTILITIES_HPP
