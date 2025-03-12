#ifndef RENDER_DATA_HPP
#define RENDER_DATA_HPP
#include "Shader.hpp"
#include "Transform.hpp"
#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
#include "ShaderConfig.hpp"
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
    QUADS
};

struct RenderData {

    RenderData(const Shader& shader, const Transform& transform, const VertexBufferLayout& layout);
    RenderData(const Shader& shader, const Transform& transform);
    RenderData(const Shader& shader);
    RenderData() = default;

    std::function<void(Renderable&, RenderData&, Window&)> uniformUpdater = nullptr;
    
    void setUniformUpdater(std::function<void(Renderable&, RenderData&, Window&)> updater) {
        uniformUpdater = updater;
    }

    Shader shaderProgram;
    ShaderConfig shaderConfig;
    Transform transform;
    VertexBufferLayout layout;

    GLuint instancedDrawModeSize = 0;
    DrawMode drawMode = DrawMode::ARRAYS;
    PrimitiveType primitiveType = PrimitiveType::TRIANGLES;
};





#endif // !RENDER_DATA_HPP
