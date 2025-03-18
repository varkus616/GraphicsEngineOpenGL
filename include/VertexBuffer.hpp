#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include <GL/glew.h>

class VertexBuffer 
{
public:

    VertexBuffer(const void* data, GLuint size);
    VertexBuffer() = default;

    ~VertexBuffer();

    VertexBuffer(const VertexBuffer& other);
    VertexBuffer& operator=(const VertexBuffer& other);

    VertexBuffer(VertexBuffer&& other) noexcept;
    VertexBuffer& operator=(VertexBuffer&& other) noexcept;

    void Bind() const;
    void Unbind() const;

    void BufferData(const void* data, GLuint size);

    const GLuint GetSize() const { return _size; }
    const GLuint GetID() const { return _rendererID; }
 
private:
    GLuint _rendererID;
    GLuint _size;

};

#endif // VERTEX_BUFFER_HPP
