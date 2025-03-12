#pragma once

#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include <Mesh.hpp>
#include <RenderableObject.hpp>



const float pyramidPositions[] =
{ -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // front face

1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,    // right face

1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // back face

-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // left face

-1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, // base – left front

1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f  // base – right back

};



const float cubeVertices[] = {
-1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,

1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,

1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,

1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,

1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

-1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,

-1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,

-1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,

1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,

-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,

1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f

};

const float triangleVertices[] = {
     0.0f,  0.5f, 0.0f,

    -0.5f, -0.5f, 0.0f,

     0.5f, -0.5f, 0.0f

};

const float squareVerticies[] =
{
    -1.0f, 1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,

    1.0f, -1.0f, -1.0f,

    1.0f, -1.0f, -1.0f,

    1.0f, 1.0f, -1.0f,

    -1.0f, 1.0f, -1.0f

};

// Wspó³rzêdne UV dla ka¿dej œciany (6 œcian, 2 trójk¹ty na œcianê, 4 wierzcho³ki)
const float texCoords[] = {
    // Przednia œciana
    0.0f, 0.0f,  // Lewy dolny
    1.0f, 0.0f,  // Prawy dolny
    1.0f, 1.0f,  // Prawy górny
    0.0f, 1.0f,  // Lewy górny

    // Tylna œciana
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    // Lewa œciana
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    // Prawa œciana
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,

    // Górna œciana
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,

    // Dolna œciana
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f
};
const unsigned int indi[] = { 1 };

static Mesh* sharedCubeMesh = nullptr;
static Mesh* sharedPyramidMesh = nullptr;
static Mesh* sharedTriangleMesh = nullptr;
static Mesh* sharedSquareMesh = nullptr;

class Sphere : public Mesh {
private:
    void init(int prec);
public:
    Sphere();
    Sphere(int prec);
};

class Pyramid : public RenderableObject {
public:
    Pyramid() : RenderableObject(sharedPyramidMesh) {
        if (!sharedPyramidMesh) {
            sharedPyramidMesh = new Mesh(pyramidPositions, sizeof(pyramidPositions) / sizeof(float));
            addMesh(sharedPyramidMesh);
        }
    }
};

class Cube : public RenderableObject {
public:
    Cube() : RenderableObject(sharedCubeMesh) {
        if (!sharedCubeMesh) {
            sharedCubeMesh = new Mesh(cubeVertices, sizeof(cubeVertices) / sizeof(float));
            addMesh(sharedCubeMesh);
        }
    }
};

class Triangle : public RenderableObject {
public:
    Triangle() : RenderableObject(sharedTriangleMesh) {
        if (!sharedTriangleMesh) {
            sharedTriangleMesh = new Mesh(triangleVertices, sizeof(triangleVertices) / sizeof(float));
            addMesh(sharedTriangleMesh);
        }
    }
};

class Square : public RenderableObject {
public:
    Square() : RenderableObject(sharedSquareMesh) {
        if (!sharedSquareMesh) {
            sharedSquareMesh = new Mesh(squareVerticies, sizeof(squareVerticies) / sizeof(float));
            addMesh(sharedSquareMesh);
        }
    }
};

