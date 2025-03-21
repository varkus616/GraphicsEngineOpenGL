#pragma once
#include <Mesh.hpp>
#include <Transform.hpp>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Renderable.hpp>
#include <Transformable.hpp>
#include <Texture.hpp>

class RenderableObject : public Renderable, public Transformable 
{
public:
    RenderableObject(Mesh* mesh, DrawMode mode = DrawMode::ARRAYS);
    RenderableObject() = default;
    ~RenderableObject() = default;

    void addTexture(Texture texture, int meshId) { if (meshId < m_meshes.size()) m_meshes[meshId]->textures.push_back(texture); else exit(1); };
    void addMesh(Mesh* mesh) { if (mesh != nullptr ) m_meshes.push_back(mesh); }
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
    void setColor(const glm::vec4& color);
    glm::vec4 getColor()override { return this->color; }
    
    glm::mat4& getModelMatrix() override;

    std::vector<Mesh*> m_meshes;
    DrawMode m_drawMode;

    void draw(RenderTarget& target, RenderData& data) override;
private:
    glm::vec4 color;

};
 