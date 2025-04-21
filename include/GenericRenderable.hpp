#pragma once
#ifndef GENERIC_RENDERABLE_HPP
#define GENERIC_RENDERABLE_HPP
#include <Renderable.hpp>
#include <VertexArray.hpp>
#include <Transformable.hpp>

class GenericRenderable : public Renderable, public Transformable
{
public:
    GenericRenderable(VertexArray* vao): m_VAO(vao){}
    GenericRenderable() = default;
    void draw(RenderTarget& target, RenderData& data);
    glm::mat4& getModelMatrix();
    glm::vec4 getColor();
    void setVAO(VertexArray* vao) { m_VAO = vao; }
private:
    VertexArray* m_VAO = nullptr;
};

#endif // !GENERIC_RENDERABLE_HPP
