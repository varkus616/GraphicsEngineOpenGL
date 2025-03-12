#include <cmath>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include "Shapes.hpp"

Sphere::Sphere() {
	init(48);

}
Sphere::Sphere(int prec) {
	init(prec);
}

void Sphere::init(GLint prec) {

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	std::vector<GLfloat> indices;
	std::vector<GLfloat> pvalues;
	std::vector<GLfloat> tvalues;

	size_t numVertices = (prec + 1) * (prec + 1);
	size_t numIndices = prec * prec * 6;
	for (size_t i = 0; i < numVertices; i++) { vertices.push_back(glm::vec3()); }	// std::vector::push_back()
	for (size_t i = 0; i < numVertices; i++) { texCoords.push_back(glm::vec2()); }	// inserts new element at
	for (size_t i = 0; i < numVertices; i++) { normals.push_back(glm::vec3()); }	// the end of a vector and
	for (size_t i = 0; i < numIndices; i++) { indices.push_back(0); }				// increases the vector size by 1

	// calculate triangle vertices
	for (size_t i = 0; i <= prec; i++) {
		for (size_t j = 0; j <= prec; j++) {
			GLfloat y = (GLfloat)cos(glm::radians(180.0f - i * 180.0f / prec));
			GLfloat x = -(GLfloat)cos(glm::radians(j * 360.0f / prec)) * (GLfloat)abs(cos(asin(y)));
			GLfloat z = (GLfloat)sin(glm::radians(j * 360.0f / prec)) * (GLfloat)abs(cos(asin(y)));
			vertices[i * (prec + 1) + j] = glm::vec3(x, y, z);

			texCoords[i * (prec + 1) + j] = glm::vec2(((GLfloat)j / prec), ((GLfloat)i / prec));

			normals[i * (prec + 1) + j] = glm::vec3(x, y, z);
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

	for (int i = 0; i < numIndices; i++) {
		pvalues.push_back((vertices[indices[i]]).x);
		pvalues.push_back((vertices[indices[i]]).y);
		pvalues.push_back((vertices[indices[i]]).z);
		tvalues.push_back((vertices[indices[i]]).s);
		tvalues.push_back((vertices[indices[i]]).t);
	}

	this->getBuffer().BufferData(pvalues.data(), pvalues.size() * sizeof(GLfloat));
	this->getTextureBuffer().BufferData(tvalues.data(), tvalues.size() * sizeof(GLfloat));

}
