#include "IndexBuffer.hpp"
#include "Utilities.hpp"

IndexBuffer::IndexBuffer(const void* data, GLuint size)
    : _size(size)
{
    GLCall(glGenBuffers(1, &_rendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));//in bytes
    Unbind();
}

IndexBuffer::~IndexBuffer()
{
    if (_rendererID) {
        GLCall(glDeleteBuffers(1, &_rendererID));
        _rendererID = 0;
    }
}

IndexBuffer::IndexBuffer(const IndexBuffer& other)
    : _size(other._size)
{
    GLCall(glGenBuffers(1, &_rendererID));
    GLCall(glBindBuffer(GL_COPY_READ_BUFFER, other._rendererID));
    GLCall(glBindBuffer(GL_COPY_WRITE_BUFFER, _rendererID));
    GLCall(glBufferData(GL_COPY_WRITE_BUFFER, other._size, nullptr, GL_STATIC_DRAW));
    GLCall(glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, other._size));
}

IndexBuffer& IndexBuffer::operator=(const IndexBuffer& other)
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

IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
    : _rendererID(other._rendererID), _size(other._size)
{
    other._rendererID = 0;
    other._size = 0;
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
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
void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID));
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::BufferData(const void* data, GLuint size)
{
    _size = size;
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));//in bytes
}
