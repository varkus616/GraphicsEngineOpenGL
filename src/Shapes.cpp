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

// Trójkąt
std::vector<glm::vec3> trianglePositions =
{
	{0.0f,  0.5f,  0.0f},  // Wierzchołek 1
	{-0.5f, -0.5f,  0.0f}, // Wierzchołek 2
	{0.5f, -0.5f,  0.0f},  // Wierzchołek 3
};

std::vector<glm::vec3> triangleNormals =
{
	{0.0f, 0.0f, 1.0f}, // Normalna w górę
	{0.0f, 0.0f, 1.0f}, // Normalna w górę
	{0.0f, 0.0f, 1.0f}, // Normalna w górę
};

std::vector<glm::vec2> triangleTextCoords =
{
	{0.5f, 1.0f}, // Wierzchołek 1
	{0.0f, 0.0f}, // Wierzchołek 2
	{1.0f, 0.0f}, // Wierzchołek 3
};

// Kwadrat
std::vector<glm::vec3> squarePositions =
{
	{-0.5f, -0.5f,  0.0f}, // Lewy dolny róg
	{ 0.5f, -0.5f,  0.0f}, // Prawy dolny róg
	{ 0.5f,  0.5f,  0.0f}, // Prawy górny róg
	{ 0.5f,  0.5f,  0.0f}, // Prawy górny róg
	{-0.5f,  0.5f,  0.0f}, // Lewy górny róg
	{-0.5f, -0.5f,  0.0f}, // Lewy dolny róg
};

std::vector<glm::vec3> squareNormals =
{
	{0.0f, 0.0f, 1.0f}, // Wszystkie normalne w stronę kamery
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
};

std::vector<glm::vec2> squareTextCoords =
{
	{0.0f, 0.0f}, // Lewy dolny róg
	{1.0f, 0.0f}, // Prawy dolny róg
	{1.0f, 1.0f}, // Prawy górny róg
	{1.0f, 1.0f}, // Prawy górny róg
	{0.0f, 1.0f}, // Lewy górny róg
	{0.0f, 0.0f}, // Lewy dolny róg
};

// Piramida (prosta piramida o podstawie kwadratu)
std::vector<glm::vec3> pyramidPositions =
{
	// Podstawa piramidy (kwadrat)
	{-0.5f, -0.5f, -0.5f}, // Lewy dolny róg
	{ 0.5f, -0.5f, -0.5f}, // Prawy dolny róg
	{ 0.5f, -0.5f,  0.5f}, // Prawy górny róg
	{-0.5f, -0.5f,  0.5f}, // Lewy górny róg

	// Wierzchołek piramidy
	{0.0f,  0.5f,  0.0f},  // Wierzchołek
};


//std::vector<glm::vec3> pyramidPositions =
//{ {-1.0f, -1.0f, 1.0f}, {1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, // front face
//{1.0f, -1.0f, 1.0f}, {1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, // right face
//{1.0f, -1.0f, -1.0f}, {-1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, // back face
//{-1.0f, -1.0f, -1.0f}, {-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, // left face
//{-1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, 1.0f}, {-1.0f, -1.0f, 1.0f}, // base – left front
//{1.0f, -1.0f, 1.0f}, {-1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, -1.0f }// base – right back
//};

std::vector<glm::vec3> pyramidNormals =
{
	{0.0f, -1.0f, 0.0f}, // Normalna do podstawy
	{0.0f, -1.0f, 0.0f},
	{0.0f, -1.0f, 0.0f},
	{0.0f, -1.0f, 0.0f},

	// Normalne do ścian piramidy (na przykład wektor skierowany w górę w stronę wierzchołka)
	{0.0f,  1.0f,  0.0f},
};

std::vector<glm::vec2> pyramidTextCoords =
{
	{0.0f, 0.0f}, // Lewy dolny róg
	{1.0f, 0.0f}, // Prawy dolny róg
	{1.0f, 1.0f}, // Prawy górny róg
	{0.0f, 1.0f}, // Lewy górny róg

	// Wierzchołek piramidy
	{0.5f, 0.5f}, // Wierzchołek
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
	return 	Mesh(vertices.data(), vertices.size(), sizeof(Vertex), indices, layout);
}
