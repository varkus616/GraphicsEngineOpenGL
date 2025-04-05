#pragma once
#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <vector>
#include <RenderableObject.hpp>
#include <Mesh.hpp>

extern std::vector<glm::vec3> cubePositions;
extern std::vector<glm::vec3> cubeNormals;
extern std::vector<Vertex> triangleVertexes;

static Mesh* sharedCubeMesh = nullptr;
static Mesh* sharedPyramidMesh = nullptr;
static Mesh* sharedTriangleMesh = nullptr;
static Mesh* sharedSquareMesh = nullptr;

//class Pyramid : public RenderableObject {
//public:
//    Pyramid() : RenderableObject(sharedPyramidMesh) {
//        this->m_drawMode = DrawMode::ELEMENTS;
//        if (!sharedPyramidMesh) {
//            sharedPyramidMesh = new Mesh(pyramidVertices);
//            addMesh(sharedPyramidMesh);
//        }
//    }
//};

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
            sharedCubeMesh = new Mesh(Mesh::CreateWithPositionsAndNormals(cubePositions, cubeNormals));
            
            addMesh(sharedCubeMesh);
        }
    }
};

class Triangle : public RenderableObject {
public:
    //Triangle() : RenderableObject(sharedTriangleMesh) {
    //    if (!sharedTriangleMesh) {
    //        sharedTriangleMesh = new Mesh(triangleVertexes);
    //        addMesh(sharedTriangleMesh);
    //    }
    //}
};
//
//class Square : public RenderableObject {
//public:
//    Square() : RenderableObject(sharedSquareMesh) {
//        if (!sharedSquareMesh) {
//            sharedSquareMesh = new Mesh(squareVerticies, sizeof(squareVerticies) / sizeof(float));
//            addMesh(sharedSquareMesh);
//        }
//    }
//};
#endif // !SHAPES_HPP


