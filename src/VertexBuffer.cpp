#include "VertexBuffer.hpp"
#include <iostream>
#include "Utilities.hpp"

VertexBuffer::VertexBuffer(const void* data, GLsizeiptr size)
    : _size(size)
{
    GLCall(glGenBuffers(1, &_rendererID));
    Bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    if (_rendererID)
    {
        GLCall(glDeleteBuffers(1, &_rendererID));
        _rendererID = 0;
    }
}

VertexBuffer::VertexBuffer(const VertexBuffer& other)
    : _size(other._size)
{
    GLCall(glGenBuffers(1, &_rendererID));
    GLCall(glBindBuffer(GL_COPY_READ_BUFFER, other._rendererID));
    GLCall(glBindBuffer(GL_COPY_WRITE_BUFFER, _rendererID));
    GLCall(glBufferData(GL_COPY_WRITE_BUFFER, other._size, nullptr, GL_STATIC_DRAW));
    GLCall(glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, other._size));

}

VertexBuffer& VertexBuffer::operator=(const VertexBuffer& other)
{
    if (this == &other)
        return *this;

    GLCall(glDeleteBuffers(1, &_rendererID));

    _size = other._size;
    GLCall(glGenBuffers(1, &_rendererID));
    GLCall(glBindBuffer(GL_COPY_READ_BUFFER, other._rendererID));
    GLCall(glBindBuffer(GL_COPY_WRITE_BUFFER, _rendererID));
    GLCall(glBufferData(GL_COPY_WRITE_BUFFER, other._size, nullptr, GL_STATIC_DRAW));
    GLCall(glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, other._size));

    return *this;
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
    : _rendererID(other._rendererID), _size(other._size)
{
    other._rendererID = 0;
    other._size = 0;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
    if (this == &other)
        return *this;

    GLCall(glDeleteBuffers(1, &_rendererID));

    _rendererID = other._rendererID;
    _size = other._size;

    other._rendererID = 0;
    other._size = 0;

    return *this;
}

void VertexBuffer::BufferData(const void* data, GLuint size)
{
    Bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    _size = size;
    Unbind();
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, _rendererID));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
