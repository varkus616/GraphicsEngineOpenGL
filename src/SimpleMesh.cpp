#pragma once

#include "SimpleMesh.hpp"

SimpleMesh::SimpleMesh(const void* vertexData,
    size_t vertexCount,
    size_t vertexSize,
    const VertexBufferLayout& layout,
    GLenum bufferType)
    :m_VBO(vertexData, vertexCount * vertexSize, vertexSize, bufferType),
    m_layout(layout)
{
    m_VBO.setBufferType(bufferType);
    setupBuffers(m_layout);
}
SimpleMesh::SimpleMesh(
    const VertexBufferLayout& layout,
    GLenum bufferType)
    :m_layout(layout)
{
    m_VBO.CreateVBO();
    m_VBO.setBufferType(bufferType);
    setupBuffers(m_layout);
}

SimpleMesh::SimpleMesh()
{
    m_VBO.CreateVBO();
}

void SimpleMesh::setupBuffers(VertexBufferLayout layout) {
    m_VAO.AddBuffer(m_VBO, layout);
}
VertexArray& SimpleMesh::getVAO()
{
    return m_VAO;
}

size_t SimpleMesh::getVertexCount() const
{
    return vertexCount;
}
