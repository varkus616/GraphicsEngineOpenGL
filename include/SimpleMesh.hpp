#pragma once
#ifndef SIMPLE_MESH_HPP
#define SIMPLE_MESH_HPP

#include <vector>
#include <functional>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <VertexArray.hpp>
#include <VertexBuffer.hpp>
#include <VertexBufferLayout.hpp>

class SimpleMesh {
public:

    SimpleMesh(const void* vertexData, 
        size_t vertexCount, 
        size_t vertexSize,
        const VertexBufferLayout& layout,
        GLenum bufferType);
    
    SimpleMesh(
        const VertexBufferLayout& layout,
        GLenum bufferType);

    SimpleMesh();

    template<typename T>
    void setData(const std::vector<T>& data, GLenum usage = GL_DYNAMIC_DRAW);
    
    template<typename T>
    void updateData(const std::vector<T>& newData);

    void setupBuffers(VertexBufferLayout layout);
    
    void setBufferType(GLenum bufferType) { m_VBO.setBufferType(bufferType); }
    VertexArray& getVAO();
    size_t getVertexCount() const;

private:
    GLuint vertexCount;
    VertexArray m_VAO;
    VertexBuffer m_VBO;
    VertexBufferLayout m_layout;
};

template<typename T>
void SimpleMesh::setData(const std::vector<T>& data, GLenum usage)
{
    m_VBO.UploadDataToGPU(data.data(), data.size() * sizeof(T), usage);
}

template<typename T>
void SimpleMesh::updateData(const std::vector<T>& newData)
{
    m_VBO.UploadDataToGPU(newData.data(), newData.size() * sizeof(T), GL_DYNAMIC_DRAW);
}

#endif // !SIMPLE_MESH_HPP
