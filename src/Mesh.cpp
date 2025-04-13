#include "Mesh.hpp"
#include <Texture.hpp>

Mesh::Mesh(const void* vertexData, size_t vertexCount, size_t vertexSize,
    const std::vector<GLuint>& indices,
    const VertexBufferLayout& layout)
    : m_VBO(vertexData, vertexCount * vertexSize),
    m_EBO(indices.data(), indices.size() * sizeof(GLuint)),
    m_layout(layout),
    m_vertexCount(vertexCount),
    m_indexCount(indices.size())
{
    setupBuffers();
}

Mesh::Mesh(const void* vertexData, size_t vertexCount, size_t vertexSize,
    const VertexBufferLayout& layout)
    : m_VBO(vertexData, vertexCount* vertexSize),
    m_EBO(nullptr, 0),
    m_layout(layout),
    m_vertexCount(vertexCount),
    m_indexCount(0)
{
    setupBuffers();
}

Mesh::Mesh() :
    m_VBO(0, 0),
    m_EBO(0, 0)
{
}

Mesh::Mesh(const Mesh& other)
{
    this->m_EBO = other.m_EBO;
    this->m_VBO = other.m_VBO;
    this->m_layout = other.m_layout;
    this->m_VAO = other.m_VAO;
}

Mesh::Mesh(Mesh&& other) noexcept
{
    this->m_EBO = std::move(other.m_EBO);
    this->m_VBO = std::move(other.m_VBO);
    this->m_layout = std::move(other.m_layout);
    this->m_VAO    = std::move(other.m_VAO);
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
    this->m_EBO = std::move(other.m_EBO);
    this->m_VBO = std::move(other.m_VBO);
    this->m_layout = std::move(other.m_layout);
    this->m_VAO = std::move(other.m_VAO);
    return *this;
}

Mesh& Mesh::operator=(const Mesh& other)
{
    this->m_EBO = other.m_EBO;
    this->m_VBO = other.m_VBO;
    this->m_layout = other.m_layout;
    this->m_VAO = other.m_VAO;
    return *this;
}

void Mesh::setupBuffers() {
    m_EBO.Bind();
    m_VAO.AddBuffer(m_VBO, m_layout);
        m_VAO.Unbind();
}

void Mesh::bindBuffers()
{
    m_VBO.Bind();
    m_EBO.Bind();
    m_VAO.Bind();
}

void Mesh::unbindBuffers()
{
    m_VBO.Unbind();
    m_VAO.Unbind();
    m_EBO.Unbind();
}

void Mesh::addTexture(const Texture* texture)
{
    if (texture != nullptr){
        m_textures.push_back(texture);
    }
    else {
        Logger& loger = Logger::getInstance();
        loger.log(LogLevel::WARNING, "[Mesh] Added Texture is null.");
    }
}

void Mesh::bindTextures() const {
    for (size_t i = 0; i < m_textures.size(); i++) {
        m_textures[i]->bind();
    }
}

void Mesh::unbindTextures() const {
    for (size_t i = 0; i < m_textures.size(); i++) {
        m_textures[i]->unbind();
    }
}

Mesh Mesh::CreateWithPositions(const std::vector<glm::vec3>& positions) {
    struct Vertex {
        glm::vec3 Position;
    };

    std::vector<Vertex> vertices(positions.size());
    for (size_t i = 0; i < positions.size(); ++i) {
        vertices[i].Position = positions[i];
    }

    VertexBufferLayout layout;
    layout.Push<GLfloat>(3); // Position

    return Mesh(vertices.data(), vertices.size(), sizeof(Vertex), layout);
}

Mesh Mesh::CreateWithPositionsAndColors(const std::vector<glm::vec3>& positions,
    const std::vector<glm::vec4>& colors) {
    struct Vertex {
        glm::vec3 Position;
        glm::vec4 Color;
    };

    assert(positions.size() == colors.size() && "Positions and colors must match");

    std::vector<Vertex> vertices(positions.size());
    for (size_t i = 0; i < positions.size(); ++i) {
        vertices[i].Position = positions[i];
        vertices[i].Color = colors[i];
    }

    VertexBufferLayout layout;
    layout.Push<GLfloat>(3); // Position
    layout.Push<GLfloat>(4); // Color

    return Mesh(vertices.data(), vertices.size(), sizeof(Vertex), layout);
}

Mesh Mesh::CreateWithPositionsAndNormals(const std::vector<glm::vec3>& positions,
    const std::vector<glm::vec3>& normals) {
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
    };

    assert(positions.size() == normals.size() && "Positions and normals must match");

    std::vector<Vertex> vertices(positions.size());
    for (size_t i = 0; i < positions.size(); ++i) {
        vertices[i].Position = positions[i];
        vertices[i].Normal = normals[i];
    }

    VertexBufferLayout layout;
    layout.Push<GLfloat>(3); // Position
    layout.Push<GLfloat>(3); // Normal

    return Mesh(vertices.data(), vertices.size(), sizeof(Vertex), layout);
}


Mesh Mesh::CreateWithPositionsNormalsAndTextures(const std::vector<glm::vec3>& positions,
    const std::vector<glm::vec3>& normals,
    const std::vector<glm::vec2>& textCoords)
{
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TextCoords;
    };

    assert(positions.size() == normals.size() && "Positions and normals must match");

    std::vector<Vertex> vertices(positions.size());
    for (size_t i = 0; i < positions.size(); ++i) {
        vertices[i].Position = positions[i];
        vertices[i].Normal = normals[i];
        vertices[i].TextCoords = textCoords[i];
    }

    VertexBufferLayout layout;
    layout.Push<GLfloat>(3); // Position
    layout.Push<GLfloat>(3); // Normal
    layout.Push<GLfloat>(2); // Normal

    return Mesh(vertices.data(), vertices.size(), sizeof(Vertex), layout);
}


Mesh Mesh::CreateWithFullData(const std::vector<glm::vec2>& uvs,
    const std::vector<glm::vec3>& positions,
    const std::vector<glm::vec3>& normals,
    const std::vector<glm::vec4>& colors,
    const std::vector<GLuint>& indices) {
    struct Vertex {
        glm::vec2 UV;
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec4 Color;
    };

    size_t count = positions.size();
    assert(uvs.size() == count && normals.size() == count && colors.size() == count);

    std::vector<Vertex> vertices(count);
    for (size_t i = 0; i < count; ++i) {
        vertices[i].UV = uvs[i];
        vertices[i].Position = positions[i];
        vertices[i].Normal = normals[i];
        vertices[i].Color = colors[i];
    }

    VertexBufferLayout layout;
    layout.Push<GLfloat>(2); // UV
    layout.Push<GLfloat>(3); // Position
    layout.Push<GLfloat>(3); // Normal
    layout.Push<GLfloat>(4); // Color

    return Mesh(vertices.data(), vertices.size(), sizeof(Vertex), indices, layout);
}
