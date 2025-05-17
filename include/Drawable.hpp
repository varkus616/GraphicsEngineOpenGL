#pragma once
#ifndef DRAWABLE_HPP
#define	DRAWABLE_HPP
#include <RenderTarget.hpp>

class Drawable {
public:
    virtual void draw(RenderTarget& target, RenderData& data) = 0;
    virtual ~Drawable() = default;
};



#endif // !DRAWABLE_HPP
