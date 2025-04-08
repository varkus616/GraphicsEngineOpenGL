#ifndef RENDER_DATA_HPP
#define RENDER_DATA_HPP

#include "Shader.hpp"
#include "Transform.hpp"
#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
#include <memory>
#include <Window.hpp>
#include <functional>


class Window;

enum class DrawMode {
    ELEMENTS,
    ARRAYS,
    INSTANCED
};

enum class PrimitiveType {
    TRIANGLES,
    QUADS,
    TRIANGLE_FAN,
    TRIANGLE_STRIP
};

struct RenderData {
    //RenderData(const Shader& shader, const Transform& transform, const VertexBufferLayout& layout);
    //RenderData(const Shader& shader, const Transform& transform);
    //RenderData(const Shader& shader);
    RenderData() = default;

    std::function<void(Renderable&, RenderData&, Window&)> uniformUpdater = nullptr;

    Shader shaderProgram;


    GLuint instancedDrawModeSize = 0;
    DrawMode drawMode = DrawMode::ARRAYS;
    PrimitiveType primitiveType = PrimitiveType::TRIANGLES;
};





#endif // !RENDER_DATA_HPP
