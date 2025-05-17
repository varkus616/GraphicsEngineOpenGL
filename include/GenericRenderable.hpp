#pragma once
#ifndef GENERIC_RENDERABLE_HPP
#define GENERIC_RENDERABLE_HPP
#include <Renderable.hpp>
#include <VertexArray.hpp>
#include <Transformable.hpp>
#include <SimpleMesh.hpp>

class GenericRenderable : public Renderable, public Transformable
{
public:
    GenericRenderable(SimpleMesh* m): m_mesh(m){}
    GenericRenderable() = default;
    void draw(RenderTarget& target, RenderData& data);
    glm::mat4& getModelMatrix();
    glm::vec4 getColor();
    void setMesh(SimpleMesh* mesh) { m_mesh = mesh; }
private:
    SimpleMesh* m_mesh;
};

#endif // !GENERIC_RENDERABLE_HPP
