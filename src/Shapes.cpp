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

// Tr�jk�t
std::vector<glm::vec3> trianglePositions =
{
	{0.0f,  0.5f,  0.0f},  // Wierzcho�ek 1
	{-0.5f, -0.5f,  0.0f}, // Wierzcho�ek 2
	{0.5f, -0.5f,  0.0f},  // Wierzcho�ek 3
};

std::vector<glm::vec3> triangleNormals =
{
	{0.0f, 0.0f, 1.0f}, // Normalna w g�r�
	{0.0f, 0.0f, 1.0f}, // Normalna w g�r�
	{0.0f, 0.0f, 1.0f}, // Normalna w g�r�
};

std::vector<glm::vec2> triangleTextCoords =
{
	{0.5f, 1.0f}, // Wierzcho�ek 1
	{0.0f, 0.0f}, // Wierzcho�ek 2
	{1.0f, 0.0f}, // Wierzcho�ek 3
};

// Kwadrat
std::vector<glm::vec3> squarePositions =
{
	{-0.5f, -0.5f,  0.0f}, // Lewy dolny r�g
	{ 0.5f, -0.5f,  0.0f}, // Prawy dolny r�g
	{ 0.5f,  0.5f,  0.0f}, // Prawy g�rny r�g
	{ 0.5f,  0.5f,  0.0f}, // Prawy g�rny r�g
	{-0.5f,  0.5f,  0.0f}, // Lewy g�rny r�g
	{-0.5f, -0.5f,  0.0f}, // Lewy dolny r�g
};

std::vector<glm::vec3> squareNormals =
{
	{0.0f, 0.0f, 1.0f}, // Wszystkie normalne w stron� kamery
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
};

std::vector<glm::vec2> squareTextCoords =
{
	{0.0f, 0.0f}, // Lewy dolny r�g
	{1.0f, 0.0f}, // Prawy dolny r�g
	{1.0f, 1.0f}, // Prawy g�rny r�g
	{1.0f, 1.0f}, // Prawy g�rny r�g
	{0.0f, 1.0f}, // Lewy g�rny r�g
	{0.0f, 0.0f}, // Lewy dolny r�g
};

// Piramida (prosta piramida o podstawie kwadratu)
std::vector<glm::vec3> pyramidPositions =
{
	// Podstawa piramidy (kwadrat)
	{-0.5f, -0.5f, -0.5f}, // Lewy dolny r�g
	{ 0.5f, -0.5f, -0.5f}, // Prawy dolny r�g
	{ 0.5f, -0.5f,  0.5f}, // Prawy g�rny r�g
	{-0.5f, -0.5f,  0.5f}, // Lewy g�rny r�g

	// Wierzcho�ek piramidy
	{0.0f,  0.5f,  0.0f},  // Wierzcho�ek
};


//std::vector<glm::vec3> pyramidPositions =
//{ {-1.0f, -1.0f, 1.0f}, {1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, // front face
//{1.0f, -1.0f, 1.0f}, {1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, // right face
//{1.0f, -1.0f, -1.0f}, {-1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, // back face
//{-1.0f, -1.0f, -1.0f}, {-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, // left face
//{-1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, 1.0f}, {-1.0f, -1.0f, 1.0f}, // base � left front
//{1.0f, -1.0f, 1.0f}, {-1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, -1.0f }// base � right back
//};

std::vector<glm::vec3> pyramidNormals =
{
	{0.0f, -1.0f, 0.0f}, // Normalna do podstawy
	{0.0f, -1.0f, 0.0f},
	{0.0f, -1.0f, 0.0f},
	{0.0f, -1.0f, 0.0f},

	// Normalne do �cian piramidy (na przyk�ad wektor skierowany w g�r� w stron� wierzcho�ka)
	{0.0f,  1.0f,  0.0f},
};

std::vector<glm::vec2> pyramidTextCoords =
{
	{0.0f, 0.0f}, // Lewy dolny r�g
	{1.0f, 0.0f}, // Prawy dolny r�g
	{1.0f, 1.0f}, // Prawy g�rny r�g
	{0.0f, 1.0f}, // Lewy g�rny r�g

	// Wierzcho�ek piramidy
	{0.5f, 0.5f}, // Wierzcho�ek
};



void Sphere::init(GLint prec) {

	/*std::vector<Vertex> vertexes;
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
	*/
}
