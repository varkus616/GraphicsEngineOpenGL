#pragma once

#include <Mesh.hpp>
#include <Transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Renderable.hpp>
#include <Transformable.hpp>
#include <Texture.hpp>

#include <vector>
#include <iostream>
#include <string>

class RenderableObject : public Renderable, public Transformable
{
public:
    RenderableObject(Mesh* mesh, DrawMode mode = DrawMode::ARRAYS);
    RenderableObject() = default;
    ~RenderableObject() = default;

    void addTexture(const Texture& texture, size_t meshIndex);
    void addMesh(Mesh* mesh);

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh* processMesh(aiMesh* mesh, const aiScene* scene);

    void setColor(const glm::vec4& color);
    glm::vec4 getColor() override { return this->color; }

    glm::mat4& getModelMatrix() override;

    void draw(RenderTarget& target, RenderData& data) override;

    DrawMode m_drawMode = DrawMode::ARRAYS;
    PrimitiveType m_primType;
private:
    std::vector<Mesh*> m_meshes;
    glm::vec4 color = glm::vec4(1.0f);
};
