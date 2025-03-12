#pragma once
#include <unordered_map>
#include <string>
#include <glm/glm.hpp>
#include <Shader.hpp>
#include <utility>

enum class UniformType {
    BOOL,
    INT,
    FLOAT,
    VEC2,
    VEC3,
    VEC4,
    MAT2,
    MAT3,
    MAT4
};

struct UniformValue {
    UniformValue(UniformType dt, GLboolean d) :dataType(dt), boolUnif(d) {};
    UniformValue(UniformType dt, GLint     d) :dataType(dt), intUnif(d) {};
    UniformValue(UniformType dt, GLfloat   d) :dataType(dt), floatUnif(d) {};
    UniformValue(UniformType dt, glm::vec2 d) :dataType(dt), vec2Unif(d) {};
    UniformValue(UniformType dt, glm::vec3 d) :dataType(dt), vec3Unif(d) {};
    UniformValue(UniformType dt, glm::vec4 d) :dataType(dt), vec4Unif(d) {};
    UniformValue(UniformType dt, glm::mat2 d) :dataType(dt), mat2Unif(d) {};
    UniformValue(UniformType dt, glm::mat3 d) :dataType(dt), mat3Unif(d) {};
    UniformValue(UniformType dt, glm::mat4 d) :dataType(dt), mat4Unif(d) {};
    UniformValue() = default;
    UniformType dataType;
    union {
        GLboolean  boolUnif;
        GLint      intUnif;
        GLfloat    floatUnif;
        glm::vec2  vec2Unif;
        glm::vec3  vec3Unif;
        glm::vec4  vec4Unif;
        glm::mat2  mat2Unif;
        glm::mat3  mat3Unif;
        glm::mat4  mat4Unif;
    };
};

struct ShaderConfig {

    
    std::unordered_map<std::string, UniformValue> uniforms;
    
    void apply(Shader& shader) const {
            for (auto it = uniforms.begin(); it != uniforms.end(); ++it) {
                switch (it->second.dataType)
                {
                case UniformType::BOOL:
                    shader.setBool(it->first, it->second.boolUnif);
                    break;

                case UniformType::INT:
                    shader.setInt(it->first, it->second.intUnif);
                    break;

                case UniformType::FLOAT:
                    shader.setFloat(it->first, it->second.floatUnif);
                    break;

                case UniformType::VEC2:
                    shader.setVec2(it->first, it->second.vec2Unif);
                    break;

                case UniformType::VEC3:
                    shader.setVec3(it->first, it->second.vec3Unif);
                    break;

                case UniformType::VEC4:
                    shader.setVec4(it->first, it->second.vec4Unif);
                    break;

                case UniformType::MAT2:
                    shader.setMat2(it->first, it->second.mat2Unif);
                    break;

                case UniformType::MAT3:
                    shader.setMat3(it->first, it->second.mat3Unif);
                    break;

                case UniformType::MAT4:
                    shader.setMat4(it->first, it->second.mat4Unif);
                    break;
                default:
                    std::cerr << "Error: Unknown uniform type!\n";
                    std::exit(EXIT_FAILURE);
                }

            }
        };
};
