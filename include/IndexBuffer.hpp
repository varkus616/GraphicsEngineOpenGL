#ifndef INDEX_BUFFER_HPP
#define INDEX_BUFFER_HPP

#include <GL/Glew.h>

class IndexBuffer 
{
public:
    IndexBuffer(const void* data, GLuint size);
    IndexBuffer() = default;

    ~IndexBuffer();


    IndexBuffer(const IndexBuffer& other);

    IndexBuffer& operator=(const IndexBuffer& other);

    IndexBuffer(IndexBuffer&& other) noexcept;

    IndexBuffer& operator=(IndexBuffer&& other) noexcept;

    void Bind() const;
    void Unbind() const;

    void BufferData(const void* data, GLuint size);
    const GLuint GetSize() const { return _size; }

private:
    GLuint _rendererID;
    GLuint _size;
};

#endif // INDEX_BUFFER_HPP
