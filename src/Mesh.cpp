#include "Mesh.hpp"


Mesh::Mesh(std::vector<GLfloat> vertices,
    std::vector<GLuint> indices,
    std::vector<GLfloat> textureCoords) :
    m_VBO(vertices.data(), vertices.size() * sizeof(GLfloat)),
    m_EBO(indices.data(), indices.size() * sizeof(GLuint)),
    m_TextureVBO(textureCoords.data(), textureCoords.size() * sizeof(GLfloat)){}

Mesh::Mesh(std::vector<GLfloat> vertices,
    std::vector<GLuint> indices) :
    m_VBO(vertices.data(), vertices.size() * sizeof(GLfloat)),
    m_EBO(indices.data(), indices.size() * sizeof(GLuint)),
    m_TextureVBO(0, 0){}

Mesh::Mesh(std::vector<GLfloat> vertices) :
    m_VBO(vertices.data(), vertices.size() * sizeof(GLfloat)),
    m_EBO(0, 0),
    m_TextureVBO(0, 0) {}

Mesh::Mesh(const GLfloat* vertices, size_t vertexCount,
    const GLuint* indices, size_t indexCount,
    const GLfloat* textureCoords, size_t coordsCount) : 
    m_VBO(vertices, vertexCount * sizeof(GLfloat)),
    m_EBO(indices, indexCount * sizeof(GLuint)),
    m_TextureVBO(textureCoords, coordsCount * sizeof(GLfloat)) {}

Mesh::Mesh(const GLfloat* vertices, size_t vertexCount,
    const GLuint* indices, size_t indexCount) :
    m_VBO(vertices, vertexCount * sizeof(GLfloat)),
    m_EBO(indices, indexCount * sizeof(GLuint)),
    m_TextureVBO(0, 0) {}

Mesh::Mesh(const GLfloat* vertices, size_t vertexCount) :
    m_VBO(vertices, vertexCount * sizeof(GLfloat)),
    m_EBO(0, 0),
    m_TextureVBO(0, 0) {}

Mesh::Mesh() :
    m_VBO(0, 0),
    m_EBO(0, 0),
    m_TextureVBO(0, 0)
{}


void Mesh::setupBuffers(const VertexBufferLayout& layout) {
    m_VAO.AddBuffer(m_VBO, layout);

    VertexBufferLayout textLayout;
    textLayout.Push<GLfloat>(2);
    m_VAO.AddBuffer(m_TextureVBO, textLayout);
}

void Mesh::bindTextures() const {
    for (size_t i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(i));
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
}

void Mesh::unbindTextures() const {
    for (size_t i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(i));
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}