#pragma once
#include <Mesh.hpp>
#include <Transform.hpp>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class RenderableObject : public Renderable, public Transformable 
{
public:
    RenderableObject(Mesh* mesh);
    RenderableObject() = default;
    ~RenderableObject() = default;

    void addTexture(Texture texture, int meshId) { if (meshId < m_meshes.size()) m_meshes[meshId]->textures.push_back(texture); else exit(1); };
    void addMesh(Mesh* mesh) { if (mesh != nullptr ) m_meshes.push_back(mesh); }
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh* processMesh(aiMesh* mesh, const aiScene* scene);




    std::vector<Mesh*> m_meshes;
    glm::mat4& getModelMatrix() override;
    

    void draw(RenderTarget& target, RenderData& data) override;
};
 