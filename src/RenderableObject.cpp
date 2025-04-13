#include <RenderableObject.hpp>
#include <Logger.hpp>
#include <sstream>
RenderableObject::RenderableObject(Mesh* mesh, DrawMode mode, PrimitiveType type)
    : m_drawMode(mode), m_primType(type)
{
    if (mesh) {
        m_meshes.push_back(mesh);
    }
    else {
        Logger& logger = Logger::getInstance();
        logger.log(LogLevel::WARNING, "[RenderableObject] Constructor received null Mesh pointer.");
    }
}

void RenderableObject::addMesh(Mesh* mesh)
{
    if (mesh) {
        m_meshes.emplace_back(mesh);
    }
    else {
        Logger& logger = Logger::getInstance();
        logger.log(LogLevel::WARNING, "[RenderableObject] Tried to add null Mesh pointer.");
    }
}

void RenderableObject::addTexture(const Texture* texture, size_t meshIndex)
{
    if (meshIndex >= m_meshes.size()) {
        Logger& logger = Logger::getInstance();
        std::stringstream ss;

        ss << "[RenderableObject] Error: Mesh index out of bounds (" << meshIndex
            << " / " << m_meshes.size() << ")";
        logger.log(LogLevel::ERROR, ss.str());
        return;
    }

    m_meshes[meshIndex]->addTexture(texture);
}


void RenderableObject::draw(RenderTarget& target, RenderData& data)
{
    for (size_t i = 0; i < m_meshes.size(); i++) {
        auto& mesh = m_meshes[i];
        if (mesh != nullptr) {
            mesh->bindBuffers();
            mesh->bindTextures();

            data.drawMode = m_drawMode;
            data.primitiveType = m_primType;
            data.vertexCount = mesh->getVertexCount();
            data.indexCount = mesh->getIndexCount();
            
            if (m_MeshStartIndices.size() == m_meshes.size())
                data.startPosition = m_MeshStartIndices[i];
            else data.startPosition = 0;
         
            target.draw(mesh->getVertexArray(), data);

        }
    }
}

glm::mat4& RenderableObject::getModelMatrix() {
    if (transform.dirty) {
        updateModelMatrix();
        transform.dirty = false;
    }
    return transform.modelMatrix;
}

void RenderableObject::loadModel(std::string path)
{
    Utils::loadModel(path, m_meshes, m_MeshStartIndices);
}

void RenderableObject::setColor(const glm::vec4& color) {
    
    this->color = color;
}