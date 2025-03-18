#pragma once
#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
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

    Mesh(std::vector<Vertex> vertexes,
        std::vector<GLuint> indices);
    Mesh(std::vector<Vertex> vertexes);

    Mesh();

    Mesh(const Mesh& other) = default;

    Mesh& operator=(const Mesh& other) = default ;

    Mesh(Mesh&& other) = default;

    ~Mesh() = default;

    void setupBuffers();
    void bindTextures() const;
    void unbindTextures() const;
    void setColor(const glm::vec4& color);

    VertexBuffer& getBuffer()  { return m_VBO; }
    IndexBuffer&  getIndexBuffer() { return m_EBO; }
    VertexArray&  getVertexArray() { return m_VAO; }


    std::vector<Texture>  textures;
private:
    static VertexBufferLayout m_bufferLayout;
    VertexArray     m_VAO;
    VertexBuffer    m_VBO;
    IndexBuffer     m_EBO;
    

};
#endif // !MESH_HPP

