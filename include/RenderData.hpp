#ifndef RENDER_DATA_HPP
#define RENDER_DATA_HPP

#include <Shader.hpp>
#include <Transform.hpp>
#include <memory>
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
    TRIANGLE_STRIP,
    POINTS
};

inline GLenum GetGLPrimitiveType(PrimitiveType type) {
    switch (type) {
    case PrimitiveType::TRIANGLES:      return GL_TRIANGLES;
    case PrimitiveType::QUADS:          return GL_QUADS;
    case PrimitiveType::TRIANGLE_FAN:   return GL_TRIANGLE_FAN;
    case PrimitiveType::TRIANGLE_STRIP: return GL_TRIANGLE_STRIP;
    case PrimitiveType::POINTS:         return GL_POINTS; 
    default:                            return GL_TRIANGLES; // Fallback
    }
}

struct RenderData { 
    RenderData() = default;

    std::function<void(Renderable&, RenderData&, Window&)> uniformUpdater = nullptr;
    std::function<void()> GenericUniformUpdater = nullptr;

    Shader* shaderProgram = nullptr;

    GLuint instancedDrawModeSize = 0;
    GLuint startPosition = 0;
    GLuint indexCount = 0;
    GLuint vertexCount = 0;

    DrawMode drawMode = DrawMode::ARRAYS;
    PrimitiveType primitiveType = PrimitiveType::TRIANGLES;
};





#endif // !RENDER_DATA_HPP
