#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "IndexBuffer.hpp"
#include "RenderData.hpp"
#include "Renderable.hpp"
#include "Transformable.hpp"
#include "GeometryData.hpp"
#include <Texture.hpp>


struct Vertex
{
    glm::vec3   pos;
    glm::vec2   texture;
};


class Mesh {

public:
    
    Mesh(std::vector<GLfloat> vertices,
        std::vector<GLuint> indices,
        std::vector<GLfloat> texturCoords);
    
    Mesh(std::vector<GLfloat> vertices,
        std::vector<GLuint> indices);

    Mesh(std::vector<GLfloat> vertices);


    Mesh(const GLfloat* vertices, size_t vertexCount, 
        const GLuint* indices, size_t indexCount, 
        const GLfloat* textureCoords, size_t coordsCount);

    Mesh(const GLfloat* vertices, size_t vertexCount,
        const GLuint* indices, size_t indexCount);

    Mesh(const GLfloat* vertices, size_t vertexCount);

    Mesh();

    Mesh(const Mesh& other) = default;

    Mesh& operator=(const Mesh& other) = default ;

    Mesh(Mesh&& other) = default;

    ~Mesh() = default;

    void setupBuffers(const VertexBufferLayout& layout);
    void bindTextures() const;
    void unbindTextures() const;

    VertexBuffer& getBuffer()  { return m_VBO; }
    VertexBuffer& getTextureBuffer() { return m_TextureVBO; }
    IndexBuffer&  getIndexBuffer() { return m_EBO; }
    VertexArray&  getVertexArray() { return m_VAO; }


    std::vector<Texture>  textures;
private:
    VertexArray     m_VAO;
    VertexBuffer    m_VBO;
    VertexBuffer    m_TextureVBO;
    VertexBufferLayout m_bufferLayout;

    IndexBuffer     m_EBO;
    

};
#endif // !MESH_HPP

