#include "Mesh.hpp"
#include <Texture.hpp>


VertexBufferLayout Mesh::m_bufferLayout = []() {
    VertexBufferLayout layout;
    
    layout.Push<GLfloat>(2); // TextureCoords (vec2)
    layout.Push<GLfloat>(3); // Position (vec3)
    layout.Push<GLfloat>(3); // Normal (vec3)
    layout.Push<GLfloat>(4); // VertexColors (vec4)
    
    return layout;
    }();


Mesh::Mesh(std::vector<Vertex> vertexes, 
           std::vector<GLuint> indices) : 
        m_VBO(vertexes.data(), vertexes.size() * sizeof(Vertex)),
        m_EBO(indices.data(), indices.size() * sizeof(GLuint))
{
}

Mesh::Mesh(std::vector<Vertex> vertexes) :
    m_VBO(vertexes.data(), vertexes.size() * sizeof(Vertex)),
    m_EBO(0, 0)
{}

Mesh::Mesh() :
    m_VBO(0, 0),
    m_EBO(0, 0)
{}

void Mesh::setupBuffers() {
    m_VAO.AddBuffer(m_VBO, m_bufferLayout);
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