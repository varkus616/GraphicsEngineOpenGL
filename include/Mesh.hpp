#pragma once
#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <GL/Glew.h>
#include <glm/glm.hpp>
#include <VertexArray.hpp>
#include <VertexBuffer.hpp>
#include <VertexBufferLayout.hpp>
#include <Texture.hpp>


class Mesh {

public:
public:
    Mesh(const void* vertexData, size_t vertexCount, size_t vertexSize,
        const std::vector<GLuint>& indices,
        const VertexBufferLayout& layout,
        GLint bufferType);

    Mesh(const void* vertexData, size_t vertexCount, size_t vertexSize,
        const VertexBufferLayout& layout,
        GLint bufferType); // bez indeksów

    Mesh();

    Mesh(const Mesh& other);

    Mesh& operator=(const Mesh& other);

    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other)noexcept;
    ~Mesh() = default;

    static Mesh CreateWithPositions(const std::vector<glm::vec3>& positions);
    static Mesh CreateWithPositionsAndColors(const std::vector<glm::vec3>& positions,
        const std::vector<glm::vec4>& colors);

    static Mesh CreateWithPositionsAndNormals(const std::vector<glm::vec3>& positions,
        const std::vector<glm::vec3>& normals);

    static Mesh CreateWithPositionsNormalsAndTextures(const std::vector<glm::vec3>& positions,
        const std::vector<glm::vec3>& normals,
        const std::vector<glm::vec2>& textCoords);

    static Mesh CreateWithFullData(const std::vector<glm::vec2>& uvs,
        const std::vector<glm::vec3>& positions,
        const std::vector<glm::vec3>& normals,
        const std::vector<glm::vec4>& colors,
        const std::vector<GLuint>& indices);


    void setupBuffers(GLint bufferType);
    void bindTextures() const;
    void unbindTextures() const;
    void addTexture(const Texture* texture);
    void bindBuffers();
    void unbindBuffers();

    VertexBuffer& getBuffer()  { return m_VBO; }
    VertexBuffer&  getIndexBuffer() { return m_EBO; }
    VertexArray&  getVertexArray() { return m_VAO; }

    const GLuint getVertexCount() const { return m_vertexCount; }
    const GLuint getIndexCount() const { return m_indexCount; }

    std::vector<const Texture*>  m_textures;

private:
    GLuint m_vertexCount;
    GLuint m_indexCount;
    VertexBufferLayout m_layout;
    VertexArray     m_VAO;
    VertexBuffer    m_VBO;
    VertexBuffer    m_EBO;
};
#endif // !MESH_HPP

