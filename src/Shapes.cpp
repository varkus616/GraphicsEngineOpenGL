#include <cmath>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <Shapes.hpp>


//std::vector<Vertex> pyramidVertices = {
//
//{{0.f, 0.f}, { -1.0f, -1.0f, 1.0f }, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f, 1.f}   },
//{{0.f, 0.f}, { 1.0f, -1.0f, 1.0f }, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f, 1.f }},
//{{0.f, 0.f}, { 0.0f, 1.0f, 0.0f }, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f, 1.f } },
//
//{{0.f, 0.f}, { 1.0f, -1.0f, 1.0f }, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f, 1.f } },
//{{0.f, 0.f}, { 1.0f, -1.0f, -1.0f }, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f, 1.f } },
//{ {0.f, 0.f}, { 0.0f, 1.0f, 0.0f }, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f, 1.f } },
//
//{{0.f, 0.f}, { 1.0f, -1.0f, -1.0f }, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f, 1.f }  },
//{{0.f, 0.f}, { -1.0f, -1.0f, -1.0f }, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f, 1.f } },
//{{0.f, 0.f}, { 0.0f, 1.0f, 0.0f }, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f, 1.f }    },
//
//{{0.f, 0.f}, { -1.0f, -1.0f, -1.0f }, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f, 1.f } },
//{{0.f, 0.f}, { -1.0f, -1.0f, 1.0f }, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f, 1.f }  },
//{ {0.f, 0.f}, { 0.0f, 1.0f, 0.0f }, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f, 1.f }    },
//
//{{0.f, 0.f}, { -1.0f, -1.0f, -1.0f }, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f, 1.f } },
//{{0.f, 0.f}, { 1.0f, -1.0f, 1.0f }, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f, 1.f }   },
//{{0.f, 0.f}, { -1.0f, -1.0f, 1.0f }, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f, 1.f }  },
//
//{ {0.f, 0.f}, { 1.0f, -1.0f, 1.0f }, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f, 1.f }   },
//{ {0.f, 0.f}, { -1.0f, -1.0f, -1.0f }, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f, 1.f } },
//{ {0.f, 0.f}, { 1.0f, -1.0f, -1.0f }, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f, 1.f }  }
//
//};

//std::vector<Vertex> pyramidVertices = {
//	// Base
//	{{0.0f, 0.0f}, {-0.5f, 0.0f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
//	{{1.0f, 0.0f}, { 0.5f, 0.0f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
//	{{1.0f, 1.0f}, { 0.5f, 0.0f,  0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
//	{{0.0f, 1.0f}, {-0.5f, 0.0f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f}},
//	// Peak
//	{{0.5f, 0.5f}, { 0.0f, 0.8f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
//};
//
//// Triangle vertices
//std::vector<Vertex> triangleVertices = {
//	{{0.5f, 1.0f}, {0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
//	{{0.0f, 0.0f}, {-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
//	{{1.0f, 0.0f}, { 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
//};
//
//// Square vertices
//std::vector<Vertex> squareVertices = {
//	{{0.0f, 0.0f}, {-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
//	{{1.0f, 0.0f}, { 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
//	{{1.0f, 1.0f}, { 0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
//	{{0.0f, 1.0f}, {-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f, 1.0f}},
//};
//
std::vector<Vertex> cubeVertexes =
{
	// Front face
	{{0.f, 0.f}, {-0.5f, -0.5f,  0.5f}, {0.f, 0.f, 1.f}, {1.f, 1.f, 1.f, 0.f}}, // 0
	{{1.f, 0.f}, { 0.5f, -0.5f,  0.5f}, {0.f, 0.f, 1.f}, {1.f, 1.f, 1.f, 0.f}}, // 1
	{{1.f, 1.f}, { 0.5f,  0.5f,  0.5f}, {0.f, 0.f, 1.f}, {1.f, 1.f, 1.f, 0.f}}, // 2
	{{1.f, 1.f}, { 0.5f,  0.5f,  0.5f}, {0.f, 0.f, 1.f}, {1.f, 1.f, 1.f, 0.f}}, // 2
	{{0.f, 1.f}, {-0.5f,  0.5f,  0.5f}, {0.f, 0.f, 1.f}, {1.f, 1.f, 1.f, 0.f}}, // 3
	{{0.f, 0.f}, {-0.5f, -0.5f,  0.5f}, {0.f, 0.f, 1.f}, {1.f, 1.f, 1.f, 0.f}}, // 0

	// Back face
	{{1.f, 0.f}, { 0.5f, -0.5f, -0.5f}, {0.f, 0.f, -1.f}, {1.f, 1.f, 1.f, 0.f}}, // 4
	{{0.f, 0.f}, {-0.5f, -0.5f, -0.5f}, {0.f, 0.f, -1.f}, {1.f, 1.f, 1.f, 0.f}}, // 5
	{{0.f, 1.f}, {-0.5f,  0.5f, -0.5f}, {0.f, 0.f, -1.f}, {1.f, 1.f, 1.f, 0.f}}, // 6
	{{0.f, 1.f}, {-0.5f,  0.5f, -0.5f}, {0.f, 0.f, -1.f}, {1.f, 1.f, 1.f, 0.f}}, // 6
	{{1.f, 1.f}, { 0.5f,  0.5f, -0.5f}, {0.f, 0.f, -1.f}, {1.f, 1.f, 1.f, 0.f}}, // 7
	{{1.f, 0.f}, { 0.5f, -0.5f, -0.5f}, {0.f, 0.f, -1.f}, {1.f, 1.f, 1.f, 0.f}}, // 4

	// Left face
	{{0.f, 0.f}, {-0.5f, -0.5f, -0.5f}, {-1.f, 0.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 8
	{{1.f, 0.f}, {-0.5f, -0.5f,  0.5f}, {-1.f, 0.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 9
	{{1.f, 1.f}, {-0.5f,  0.5f,  0.5f}, {-1.f, 0.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 10
	{{1.f, 1.f}, {-0.5f,  0.5f,  0.5f}, {-1.f, 0.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 10
	{{0.f, 1.f}, {-0.5f,  0.5f, -0.5f}, {-1.f, 0.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 11
	{{0.f, 0.f}, {-0.5f, -0.5f, -0.5f}, {-1.f, 0.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 8

	// Right face
	{{1.f, 0.f}, { 0.5f, -0.5f,  0.5f}, {1.f, 0.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 12
	{{0.f, 0.f}, { 0.5f, -0.5f, -0.5f}, {1.f, 0.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 13
	{{0.f, 1.f}, { 0.5f,  0.5f, -0.5f}, {1.f, 0.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 14
	{{0.f, 1.f}, { 0.5f,  0.5f, -0.5f}, {1.f, 0.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 14
	{{1.f, 1.f}, { 0.5f,  0.5f,  0.5f}, {1.f, 0.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 15
	{{1.f, 0.f}, { 0.5f, -0.5f,  0.5f}, {1.f, 0.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 12

	// Top face
	{{0.f, 1.f}, {-0.5f,  0.5f, -0.5f}, {0.f, 1.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 16
	{{1.f, 1.f}, { 0.5f,  0.5f, -0.5f}, {0.f, 1.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 17
	{{1.f, 0.f}, { 0.5f,  0.5f,  0.5f}, {0.f, 1.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 18
	{{1.f, 0.f}, { 0.5f,  0.5f,  0.5f}, {0.f, 1.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 18
	{{0.f, 0.f}, {-0.5f,  0.5f,  0.5f}, {0.f, 1.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 19
	{{0.f, 1.f}, {-0.5f,  0.5f, -0.5f}, {0.f, 1.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 16

	{{0.f, 0.f}, {-0.5f, -0.5f, -0.5f}, {0.f, -1.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 20
	{{1.f, 0.f}, { 0.5f, -0.5f, -0.5f}, {0.f, -1.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 21
	{{1.f, 1.f}, { 0.5f, -0.5f,  0.5f}, {0.f, -1.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 22
	{{1.f, 1.f}, { 0.5f, -0.5f,  0.5f}, {0.f, -1.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 22
	{{0.f, 1.f}, {-0.5f, -0.5f,  0.5f}, {0.f, -1.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 23
	{{0.f, 0.f}, {-0.5f, -0.5f, -0.5f}, {0.f, -1.f, 0.f}, {1.f, 1.f, 1.f, 0.f}}, // 20
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
