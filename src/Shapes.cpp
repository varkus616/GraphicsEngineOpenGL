#include <cmath>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <Shapes.hpp>


std::vector<glm::vec3> cubePositions =
{
	// Front face
	{-0.5f, -0.5f, -0.5f},
	{ 0.5f, -0.5f, -0.5f},
	{ 0.5f,  0.5f, -0.5f},
	{ 0.5f,  0.5f, -0.5f},
	{-0.5f,  0.5f, -0.5f},
	{-0.5f, -0.5f, -0.5f},

	// Back face
	{-0.5f, -0.5f,  0.5f},
	{ 0.5f, -0.5f,  0.5f},
	{ 0.5f,  0.5f,  0.5f},
	{ 0.5f,  0.5f,  0.5f},
	{-0.5f,  0.5f,  0.5f},
	{-0.5f, -0.5f,  0.5f},

	// Left face
	{-0.5f,  0.5f,  0.5f},
	{-0.5f,  0.5f, -0.5f},
	{-0.5f, -0.5f, -0.5f},
	{-0.5f, -0.5f, -0.5f},
	{-0.5f, -0.5f,  0.5f},
	{-0.5f,  0.5f,  0.5f},

	// Right face
	{ 0.5f,  0.5f,  0.5f},
	{ 0.5f,  0.5f, -0.5f},
	{ 0.5f, -0.5f, -0.5f},
	{ 0.5f, -0.5f, -0.5f},
	{ 0.5f, -0.5f,  0.5f},
	{ 0.5f,  0.5f,  0.5f},

	// Top face
	{-0.5f, -0.5f, -0.5f},
	{ 0.5f, -0.5f, -0.5f},
	{ 0.5f, -0.5f,  0.5f},
	{ 0.5f, -0.5f,  0.5f},
	{-0.5f, -0.5f,  0.5f},
	{-0.5f, -0.5f, -0.5f},

	// Bottom face
	{-0.5f,  0.5f, -0.5f},
	{ 0.5f,  0.5f, -0.5f},
	{ 0.5f,  0.5f,  0.5f},
	{ 0.5f,  0.5f,  0.5f},
	{-0.5f,  0.5f,  0.5f},
	{-0.5f,  0.5f, -0.5f},
};

std::vector<glm::vec3> cubeNormals = 
{
	{0.0f,  0.0f, -1.0f},
	{0.0f,  0.0f, -1.0f},
	{0.0f,  0.0f, -1.0f},
	{0.0f,  0.0f, -1.0f},
	{0.0f,  0.0f, -1.0f},
	{0.0f,  0.0f, -1.0f},

	{0.0f,  0.0f,  1.0f},
	{0.0f,  0.0f,  1.0f},
	{0.0f,  0.0f,  1.0f},
	{0.0f,  0.0f,  1.0f},
	{0.0f,  0.0f,  1.0f},
	{0.0f,  0.0f,  1.0f},

	{-1.0f,  0.0f,  0.0f},
	{-1.0f,  0.0f,  0.0f},
	{-1.0f,  0.0f,  0.0f},
	{-1.0f,  0.0f,  0.0f},
	{-1.0f,  0.0f,  0.0f},
	{-1.0f,  0.0f,  0.0f},

	{1.0f,  0.0f,  0.0f},
	{1.0f,  0.0f,  0.0f},
	{1.0f,  0.0f,  0.0f},
	{1.0f,  0.0f,  0.0f},
	{1.0f,  0.0f,  0.0f},
	{1.0f,  0.0f,  0.0f},

	{0.0f, -1.0f,  0.0f},
	{0.0f, -1.0f,  0.0f},
	{0.0f, -1.0f,  0.0f},
	{0.0f, -1.0f,  0.0f},
	{0.0f, -1.0f,  0.0f},
	{0.0f, -1.0f,  0.0f},

	{0.0f,  1.0f,  0.0f},
	{0.0f,  1.0f,  0.0f},
	{0.0f,  1.0f,  0.0f},
	{0.0f,  1.0f,  0.0f},
	{0.0f,  1.0f,  0.0f},
	{0.0f,  1.0f,  0.0f},
};

std::vector<Vertex> cubeVertexes =
{
	// Front face
	{{0.0f, 0.0f}, {-0.5f, -0.5f, -0.5f}, {0.0f,  0.0f, -1.0f}, {}}, // 0
	{{1.0f, 0.0f}, { 0.5f, -0.5f, -0.5f}, {0.0f,  0.0f, -1.0f}, {}}, // 1
	{{1.0f, 1.0f}, { 0.5f,  0.5f, -0.5f}, {0.0f,  0.0f, -1.0f}, {}}, // 2
	{{1.0f, 1.0f}, { 0.5f,  0.5f, -0.5f}, {0.0f,  0.0f, -1.0f}, {}}, // 2
	{{0.0f, 1.0f}, {-0.5f,  0.5f, -0.5f}, {0.0f,  0.0f, -1.0f}, {}}, // 3
	{{0.0f, 0.0f}, {-0.5f, -0.5f, -0.5f}, {0.0f,  0.0f, -1.0f}, {}}, // 0

	// Back face
	{{0.0f, 0.0f}, {-0.5f, -0.5f,  0.5f}, {0.0f,  0.0f,  1.0f}, {}}, // 4
	{{1.0f, 0.0f}, { 0.5f, -0.5f,  0.5f}, {0.0f,  0.0f,  1.0f}, {}}, // 5
	{{1.0f, 1.0f}, { 0.5f,  0.5f,  0.5f}, {0.0f,  0.0f,  1.0f}, {}}, // 6
	{{1.0f, 1.0f}, { 0.5f,  0.5f,  0.5f}, {0.0f,  0.0f,  1.0f}, {}}, // 6
	{{0.0f, 1.0f}, {-0.5f,  0.5f,  0.5f}, {0.0f,  0.0f,  1.0f}, {}}, // 7
	{{0.0f, 0.0f}, {-0.5f, -0.5f,  0.5f}, {0.0f,  0.0f,  1.0f}, {}}, // 4

	// Left face
	{{1.0f, 0.0f}, {-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {}}, // 8
	{{1.0f, 1.0f}, {-0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {}}, // 9
	{{0.0f, 1.0f}, {-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {}}, // 10
	{{0.0f, 1.0f}, {-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {}}, // 10
	{{0.0f, 0.0f}, {-0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {}}, // 11
	{{1.0f, 0.0f}, {-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {}}, // 8

	// Right face
	{{1.0f, 0.0f}, { 0.5f,  0.5f,  0.5f}, {1.0f,  0.0f,  0.0f}, {}}, // 12
	{{1.0f, 1.0f}, { 0.5f,  0.5f, -0.5f}, {1.0f,  0.0f,  0.0f}, {}}, // 13
	{{0.0f, 1.0f}, { 0.5f, -0.5f, -0.5f}, {1.0f,  0.0f,  0.0f}, {}}, // 14
	{{0.0f, 1.0f}, { 0.5f, -0.5f, -0.5f}, {1.0f,  0.0f,  0.0f}, {}}, // 14
	{{0.0f, 0.0f}, { 0.5f, -0.5f,  0.5f}, {1.0f,  0.0f,  0.0f}, {}}, // 15
	{{1.0f, 0.0f}, { 0.5f,  0.5f,  0.5f}, {1.0f,  0.0f,  0.0f}, {}}, // 12

	// Top face
	{{0.0f, 1.0f}, {-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f,  0.0f}, {}}, // 16
	{{1.0f, 1.0f}, { 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f,  0.0f}, {}}, // 17
	{{1.0f, 0.0f}, { 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f,  0.0f}, {}}, // 18
	{{1.0f, 0.0f}, { 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f,  0.0f}, {}}, // 18
	{{0.0f, 0.0f}, {-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f,  0.0f}, {}}, // 19
	{{0.0f, 1.0f}, {-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f,  0.0f}, {}}, // 16

	// Bottom face
	{{0.0f, 1.0f}, {-0.5f,  0.5f, -0.5f}, {0.0f,  1.0f,  0.0f}, {}}, // 20
	{{1.0f, 1.0f}, { 0.5f,  0.5f, -0.5f}, {0.0f,  1.0f,  0.0f}, {}}, // 21
	{{1.0f, 0.0f}, { 0.5f,  0.5f,  0.5f}, {0.0f,  1.0f,  0.0f}, {}}, // 22
	{{1.0f, 0.0f}, { 0.5f,  0.5f,  0.5f}, {0.0f,  1.0f,  0.0f}, {}}, // 22
	{{0.0f, 0.0f}, {-0.5f,  0.5f,  0.5f}, {0.0f,  1.0f,  0.0f}, {}}, // 23
	{{0.0f, 1.0f}, {-0.5f,  0.5f, -0.5f}, {0.0f,  1.0f,  0.0f}, {}}, // 20
};

std::vector<Vertex> triangleVertexes =
{
	{{0.f, 0.f}, {0.0f, 0.5f, 0.0f},   {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f, 0.f} },
	{{0.f, 0.f}, {-0.5f, -0.5f, 0.0f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f, 0.f} },
	{{0.f, 0.f}, { 0.5f, -0.5f, 0.0f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f, 0.f} }
};

void Sphere::init(GLint prec) {

	std::vector<Vertex> vertexes;
	std::vector<GLfloat> indices;

	size_t numVertices = (prec + 1) * (prec + 1);
	size_t numIndices = prec * prec * 6;
	for (size_t i = 0; i < numVertices; i++) { vertexes.push_back(Vertex()); }	
	for (size_t i = 0; i < numIndices; i++) { indices.push_back(0); }			

	// calculate triangle vertices
	for (size_t i = 0; i <= prec; i++) {
		for (size_t j = 0; j <= prec; j++) {
			GLfloat y = (GLfloat)cos(glm::radians(180.0f - i * 180.0f / prec));
			GLfloat x = -(GLfloat)cos(glm::radians(j * 360.0f / prec)) * (GLfloat)abs(cos(asin(y)));
			GLfloat z = (GLfloat)sin(glm::radians(j * 360.0f / prec)) * (GLfloat)abs(cos(asin(y)));
			
			vertexes[i * (prec + 1) + j].Position = glm::vec3(x, y, z);

			vertexes[i * (prec + 1) + j].TextureCoords = glm::vec2(((GLfloat)j / prec), ((GLfloat)i / prec));

			vertexes[i * (prec + 1) + j].Normal = glm::vec3(x, y, z);
		}
	}

	// calculate triangle indices
	for (int i = 0; i < prec; i++) {
		for (int j = 0; j < prec; j++) {
			indices[6 * (i * prec + j) + 0] = i * (prec + 1) + j;
			indices[6 * (i * prec + j) + 1] = i * (prec + 1) + j + 1;
			indices[6 * (i * prec + j) + 2] = (i + 1) * (prec + 1) + j;
			indices[6 * (i * prec + j) + 3] = i * (prec + 1) + j + 1;
			indices[6 * (i * prec + j) + 4] = (i + 1) * (prec + 1) + j + 1;
			indices[6 * (i * prec + j) + 5] = (i + 1) * (prec + 1) + j;
		}
	}


	this->getBuffer().BufferData(vertexes.data(), vertexes.size() * sizeof(Vertex));

}
