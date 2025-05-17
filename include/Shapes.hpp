#pragma once
#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <vector>
#include <RenderableObject.hpp>
#include <Mesh.hpp>

extern const Mesh CreateSphere(GLfloat radius, GLint stackCount, GLint sectorCount);

extern std::vector<glm::vec3> cubePositions;
extern std::vector<glm::vec3> cubeNormals;
extern std::vector<glm::vec2> cubeTextCoords;

extern std::vector<glm::vec3> squarePositions;
extern std::vector<glm::vec3> squareNormals;
extern std::vector<glm::vec2> squareTextCoords;


static Mesh* sharedCubeMesh = nullptr;

class Sphere : public RenderableObject {
public:

    Sphere(float radius = 1.f) : RenderableObject(new Mesh(CreateSphere(radius, 36, 12)), DrawMode::ELEMENTS, PrimitiveType::TRIANGLES) 
    {
    }
};


class Cube : public RenderableObject {
public:
    Cube() : RenderableObject() {
        this->m_drawMode = DrawMode::ARRAYS;
        this->m_primType = PrimitiveType::TRIANGLES;
        if (!sharedCubeMesh) {
            sharedCubeMesh = new Mesh(Mesh::CreateWithPositionsNormalsAndTextures(cubePositions, cubeNormals, cubeTextCoords));
        }
        addMesh(sharedCubeMesh);
    }
};

#endif // !SHAPES_HPP


