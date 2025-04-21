#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include <GL/glew.h>
#include <vector>

class VertexBuffer 
{
public:

    VertexBuffer(const void* data, GLuint size, GLuint vertexSize, GLint bufferType = GL_ARRAY_BUFFER, GLint drawHint = GL_STATIC_DRAW);
    VertexBuffer() = default;

    void CreateVBO();
    void DeleteVBO();

    ~VertexBuffer();
    VertexBuffer(const VertexBuffer& other);
    VertexBuffer& operator=(const VertexBuffer& other);

    VertexBuffer(VertexBuffer&& other) noexcept;
    VertexBuffer& operator=(VertexBuffer&& other) noexcept;

    void* MapBufferToMemory(GLint iUsageHint);
    void* MapSubBufferToMemory(GLint iUsageHint,
        GLuint uiOffset, GLuint uiLength);
    void UnmapBuffer();

    void Bind() const;
    void Unbind() const;
    void UploadDataToGPU(const void* ptrData, GLuint size, int iUsageHint);

    inline const GLuint GetSize() const { return m_uiSize; }
    inline const GLuint GetCurrentSize() const { return m_uiCurrentSize; }
    inline const GLuint GetID() const { return m_uiRendererID; }
    inline const void* GetDataPointer() const { return m_data; }

    void setBufferType(GLint bufferType) { m_iBufferType = bufferType; }
    void setDataPointer(void* data) { m_data = data; }
    void setDataSize(GLuint size) { m_uiSize = size; }
    void PrintInfo() const;


private:
    GLuint m_uiRendererID;
    GLuint m_uiSize;
    GLuint m_uiCurrentSize;
    GLint  m_iBufferType;
    GLuint m_uiVertexSize;
    void* m_data = nullptr; 
    bool m_bDataUploaded;
};

#endif // VERTEX_BUFFER_HPP
