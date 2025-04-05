#pragma once
#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <GL/Glew.h>
#include <glm/glm.hpp>
#include <VertexArray.hpp>
#include <VertexBuffer.hpp>
#include <VertexBufferLayout.hpp>
#include <IndexBuffer.hpp>
#include <Texture.hpp>


struct Vertex
{
    glm::vec2   TextureCoords;
    glm::vec3   Position;
    glm::vec3   Normal;
    glm::vec4   VertexColors;
};


class Mesh {

public:
public:
    Mesh(const void* vertexData, size_t vertexCount, size_t vertexSize,
        const std::vector<GLuint>& indices,
        const VertexBufferLayout& layout);

    Mesh(const void* vertexData, size_t vertexCount, size_t vertexSize,
        const VertexBufferLayout& layout); // bez indeksów

    Mesh();

    Mesh(const Mesh& other) = default;

    Mesh& operator=(const Mesh& other) = default ;

    Mesh(Mesh&& other) = default;

    ~Mesh() = default;

    static Mesh CreateWithPositions(const std::vector<glm::vec3>& positions);
    static Mesh CreateWithPositionsAndColors(const std::vector<glm::vec3>& positions,
        const std::vector<glm::vec4>& colors);

    static Mesh CreateWithPositionsAndNormals(const std::vector<glm::vec3>& positions,
        const std::vector<glm::vec3>& normals);

    static Mesh CreateWithFullData(const std::vector<glm::vec2>& uvs,
        const std::vector<glm::vec3>& positions,
        const std::vector<glm::vec3>& normals,
        const std::vector<glm::vec4>& colors,
        const std::vector<GLuint>& indices);


    void setupBuffers();
    void bindTextures() const;
    void unbindTextures() const;

    VertexBuffer& getBuffer()  { return m_VBO; }
    IndexBuffer&  getIndexBuffer() { return m_EBO; }
    VertexArray&  getVertexArray() { return m_VAO; }


    std::vector<Texture>  textures;
private:
    VertexBufferLayout m_layout;
    VertexArray     m_VAO;
    VertexBuffer    m_VBO;
    IndexBuffer     m_EBO;
    

};
#endif // !MESH_HPP

