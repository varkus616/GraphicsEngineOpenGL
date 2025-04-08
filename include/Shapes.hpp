#pragma once
#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <vector>
#include <RenderableObject.hpp>
#include <Mesh.hpp>

extern std::vector<glm::vec3> cubePositions;
extern std::vector<glm::vec3> cubeNormals;
extern std::vector<glm::vec2> cubeTextCoords;

extern std::vector<glm::vec3> trianglePositions;
extern std::vector<glm::vec3> triangleNormals;
extern std::vector<glm::vec2> triangleTextCoords;

extern std::vector<glm::vec3> squarePositions;
extern std::vector<glm::vec3> squareNormals;
extern std::vector<glm::vec2> squareTextCoords;

extern std::vector<glm::vec3> pyramidPositions;
extern std::vector<glm::vec3> pyramidNormals;
extern std::vector<glm::vec2> pyramidTextCoords;

static Mesh* sharedCubeMesh = nullptr; 
static Mesh* sharedPyramidMesh = nullptr;
static Mesh* sharedTriangleMesh = nullptr;
static Mesh* sharedSquareMesh = nullptr;

class Pyramid : public RenderableObject {
public:
    Pyramid() : RenderableObject(sharedPyramidMesh) {
        this->m_drawMode = DrawMode::ARRAYS;
        this->m_primType = PrimitiveType::TRIANGLE_FAN;
        if (!sharedPyramidMesh) {
            sharedPyramidMesh = new Mesh(Mesh::CreateWithPositionsNormalsAndTextures(pyramidPositions, pyramidNormals, pyramidTextCoords));
            addMesh(sharedPyramidMesh);
        }
    }
};

class Sphere : public Mesh {
private:
    void init(int prec);
public:

    Sphere(int prec) {
        init(prec);
    }
    Sphere() : Sphere(48) {}
};

class Cube : public RenderableObject {
public:
    Cube() : RenderableObject(sharedCubeMesh) {
        if (!sharedCubeMesh) {
            sharedCubeMesh = new Mesh(Mesh::CreateWithPositionsNormalsAndTextures(cubePositions, cubeNormals, cubeTextCoords));
            addMesh(sharedCubeMesh);
        }
    }
};

class Triangle : public RenderableObject {
public:
    Triangle() : RenderableObject(sharedTriangleMesh) {
        if (!sharedTriangleMesh) {
            sharedTriangleMesh = new Mesh(Mesh::CreateWithPositionsNormalsAndTextures(trianglePositions, triangleNormals, triangleTextCoords));
            addMesh(sharedTriangleMesh);
        }
    }
};

class Square : public RenderableObject {
public:
    Square() : RenderableObject(sharedSquareMesh) {
        if (!sharedSquareMesh) {
            sharedSquareMesh = new Mesh(Mesh::CreateWithPositionsNormalsAndTextures(squarePositions, squareNormals, squareTextCoords));
            addMesh(sharedSquareMesh);
        }
    }
};
#endif // !SHAPES_HPP


