#include "VertexBuffer.hpp"
#include <iostream>
#include "Utilities.hpp"

VertexBuffer::VertexBuffer(const void* data, GLuint size, GLuint vertexSize, GLint bufferType, GLint drawHint)
    : m_uiSize(size), m_iBufferType(bufferType)
{
    this->CreateVBO();
    this->Bind();
    this->UploadDataToGPU(data, size, drawHint);
}

VertexBuffer::~VertexBuffer()
{
    if (m_uiRendererID)
    {
        this->DeleteVBO();
        m_uiRendererID = 0;
    }
}

void VertexBuffer::CreateVBO()
{
    GLCall(glGenBuffers(1, &m_uiRendererID));
}

void VertexBuffer::DeleteVBO()
{
    GLCall(glDeleteBuffers(1, &m_uiRendererID));
    m_bDataUploaded = false;
}

VertexBuffer::VertexBuffer(const VertexBuffer& other)
    : m_uiSize(other.m_uiSize)
{
    GLCall(glGenBuffers(1, &m_uiRendererID));
    GLCall(glBindBuffer(GL_COPY_READ_BUFFER, other.m_uiRendererID));
    GLCall(glBindBuffer(GL_COPY_WRITE_BUFFER, m_uiRendererID));
    GLCall(glBufferData(GL_COPY_WRITE_BUFFER, other.m_uiSize, nullptr, GL_STATIC_DRAW));
    GLCall(glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, other.m_uiSize));

}

VertexBuffer& VertexBuffer::operator=(const VertexBuffer& other)
{
    if (this == &other)
        return *this;

    GLCall(glDeleteBuffers(1, &m_uiRendererID));

    m_uiSize = other.m_uiSize;
    GLCall(glGenBuffers(1, &m_uiRendererID));
    GLCall(glBindBuffer(GL_COPY_READ_BUFFER, other.m_uiRendererID));
    GLCall(glBindBuffer(GL_COPY_WRITE_BUFFER, m_uiRendererID));
    GLCall(glBufferData(GL_COPY_WRITE_BUFFER, other.m_uiSize, nullptr, GL_STATIC_DRAW));
    GLCall(glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, other.m_uiSize));

    return *this;
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
    : m_uiRendererID(other.m_uiRendererID), m_uiSize(other.m_uiSize)
{
    other.m_uiRendererID = 0;
    other.m_uiSize = 0;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
    if (this == &other)
        return *this;

    GLCall(glDeleteBuffers(1, &m_uiRendererID));

    m_uiRendererID = other.m_uiRendererID;
    m_uiSize = other.m_uiSize;

    other.m_uiRendererID = 0;
    other.m_uiSize = 0;

    return *this;
}

void VertexBuffer::UploadDataToGPU(const void* ptrData, GLuint size, int iDrawingHint)
{
    GLCall(glBufferData(m_iBufferType, size, ptrData, iDrawingHint));
    m_bDataUploaded = true;
    m_uiSize = size;
    m_uiCurrentSize = size;
}

void* VertexBuffer::MapBufferToMemory(int iUsageHint)
{
    if (!m_bDataUploaded)return NULL;
    void* ptrRes = glMapBuffer(m_iBufferType, iUsageHint);
    return ptrRes;
}

void* VertexBuffer::MapSubBufferToMemory(int iUsageHint, 
    GLuint uiOffset, GLuint uiLength)
{
    if (!m_bDataUploaded)return NULL;
    void* ptrRes = glMapBufferRange(m_iBufferType, uiOffset, uiLength, iUsageHint);
    return ptrRes;
}

void VertexBuffer::UnmapBuffer()
{
    glUnmapBuffer(m_iBufferType);
}

void VertexBuffer::Bind() const 
{
    GLCall(glBindBuffer(m_iBufferType, m_uiRendererID));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(m_iBufferType, 0));
}

void VertexBuffer::PrintInfo() const
{
    std::cout << "[VBO] ID: " << m_uiRendererID
        << " | Size in bytes: " << m_uiSize
        << " | Data uploaded: " << (m_bDataUploaded ? "yes" : "no")
        << std::endl;
}
