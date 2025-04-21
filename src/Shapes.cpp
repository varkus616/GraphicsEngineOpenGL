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

std::vector<glm::vec2> cubeTextCoords =
{
	{0.0f, 0.0f},
	{1.0f, 0.0f},
	{1.0f, 1.0f},
	{1.0f, 1.0f},
	{0.0f, 1.0f},
	{0.0f, 0.0f},

	{0.0f, 0.0f},
	{1.0f, 0.0f},
	{1.0f, 1.0f},
	{1.0f, 1.0f},
	{0.0f, 1.0f},
	{0.0f, 0.0f},

	{1.0f, 0.0f},
	{1.0f, 1.0f},
	{0.0f, 1.0f},
	{0.0f, 1.0f},
	{0.0f, 0.0f},
	{1.0f, 0.0f},

	{1.0f, 0.0f},
	{1.0f, 1.0f},
	{0.0f, 1.0f},
	{0.0f, 1.0f},
	{0.0f, 0.0f},
	{1.0f, 0.0f},

	{0.0f, 1.0f},
	{1.0f, 1.0f},
	{1.0f, 0.0f},
	{1.0f, 0.0f},
	{0.0f, 0.0f},
	{0.0f, 1.0f},

	{0.0f, 1.0f},
	{1.0f, 1.0f},
	{1.0f, 0.0f},
	{1.0f, 0.0f},
	{0.0f, 0.0f},
	{0.0f, 1.0f},
};

const Mesh CreateSphere(GLfloat radius, GLint stackCount, GLint sectorCount) {

	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TextureCoords;
	};

	std::vector<Vertex> vertices;

	const float PI = 3.14159265359f;

	for (int i = 0; i <= stackCount; ++i) {
		float stackAngle = PI / 2 - i * PI / stackCount;   // φ: od +π/2 do -π/2
		float xy = radius * cosf(stackAngle);              // promień okręgu na tej szerokości
		float z = radius * sinf(stackAngle);               // wysokość

		for (int j = 0; j <= sectorCount; ++j) {
			float sectorAngle = j * 2 * PI / sectorCount;  // θ: od 0 do 2π

			// Pozycja
			float x = xy * cosf(sectorAngle);
			float y = xy * sinf(sectorAngle);

			// Normalna (dla sfery jednostkowej = pozycja znormalizowana)
			float nx = x / radius;
			float ny = y / radius;
			float nz = z / radius;

			// UV (u od 0 do 1, v od 0 do 1)
			float u = (float)j / sectorCount;
			float v = (float)i / stackCount;

			vertices.push_back({ {x, y, z }, {nx, ny, nz}, {u, v}
		});
		}
	}
	std::vector<GLuint> indices;
	int k1, k2;

	for (int i = 0; i < stackCount; ++i) {
		k1 = i * (sectorCount + 1);     // początek bieżącego rzędu
		k2 = k1 + sectorCount + 1;      // początek następnego rzędu

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
			if (i != 0) {
				// pierwsze trójkąt
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}
			if (i != (stackCount - 1)) {
				// drugie trójkąt
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}
	VertexBufferLayout layout;
	layout.Push<GLfloat>(3);
	layout.Push<GLfloat>(3);
	layout.Push<GLfloat>(2);
	return 	Mesh(vertices.data(), vertices.size(), sizeof(Vertex), indices, layout, GL_ARRAY_BUFFER);
}
