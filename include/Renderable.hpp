#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include <RenderTarget.hpp>
#include <RenderData.hpp>

class Renderable {
public:
    virtual void draw(RenderTarget& target, RenderData& data) = 0;
    virtual glm::mat4& getModelMatrix() = 0;
};


#endif // RENDERABLE_HPP
