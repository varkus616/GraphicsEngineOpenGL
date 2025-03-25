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
    MAT4,
    INT_ARRAY,
    FLOAT_ARRAY,
    VEC2_ARRAY,
    VEC3_ARRAY,
    VEC4_ARRAY,
    MAT4_ARRAY,
    NONE
};


struct UniformValue {
    UniformType dataType;
    const void* dataPtr = nullptr;  
    size_t size = 0;                

    UniformValue() : dataType(UniformType::NONE), dataPtr(nullptr) {}
    UniformValue(UniformType dt, const GLboolean& d) : dataType(dt), dataPtr(&d) {}
    UniformValue(UniformType dt, const GLint& d) : dataType(dt), dataPtr(&d) {}
    UniformValue(UniformType dt, const GLfloat& d) : dataType(dt), dataPtr(&d) {}
    UniformValue(UniformType dt, const glm::vec2& d) : dataType(dt), dataPtr(&d) {}
    UniformValue(UniformType dt, const glm::vec3& d) : dataType(dt), dataPtr(&d) {}
    UniformValue(UniformType dt, const glm::vec4& d) : dataType(dt), dataPtr(&d) {}
    UniformValue(UniformType dt, const glm::mat2& d) : dataType(dt), dataPtr(&d) {}
    UniformValue(UniformType dt, const glm::mat3& d) : dataType(dt), dataPtr(&d) {}
    UniformValue(UniformType dt, const glm::mat4& d) : dataType(dt), dataPtr(&d) {}

    // Przechowywanie wskaŸnika na tablicê (bez kopiowania)
    template <typename T>
    UniformValue(UniformType dt, const std::vector<T>& arr)
        : dataType(dt), dataPtr(arr.data()), size(arr.size()) {}

    ~UniformValue() = default;
};


struct ShaderConfig {

    
    std::unordered_map<std::string, UniformValue> uniforms;
    
    void apply(Shader& shader) const {
        for (auto& it : uniforms) {
            const std::string& name = it.first;
            const UniformValue& value = it.second;

            switch (value.dataType) {
            case UniformType::BOOL:
                shader.setBool(name, *reinterpret_cast<const GLboolean*>(value.dataPtr));
                break;
            case UniformType::INT:
                shader.setInt(name, *reinterpret_cast<const GLint*>(value.dataPtr));
                break;
            case UniformType::FLOAT:
                shader.setFloat(name, *reinterpret_cast<const GLfloat*>(value.dataPtr));
                break;
            case UniformType::VEC2:
                shader.setVec2(name, *reinterpret_cast<const glm::vec2*>(value.dataPtr));
                break;
            case UniformType::VEC3:
                shader.setVec3(name, *reinterpret_cast<const glm::vec3*>(value.dataPtr));
                break;
            case UniformType::VEC4:
                shader.setVec4(name, *reinterpret_cast<const glm::vec4*>(value.dataPtr));
                break;
            case UniformType::MAT2:
                shader.setMat2(name, *reinterpret_cast<const glm::mat2*>(value.dataPtr), GL_FALSE);
                break;
            case UniformType::MAT3:
                shader.setMat3(name, *reinterpret_cast<const glm::mat3*>(value.dataPtr), GL_FALSE);
                break;
            case UniformType::MAT4:
                shader.setMat4(name, *reinterpret_cast<const glm::mat4*>(value.dataPtr), GL_FALSE);
                break;

                // Obs³uga tablic
            case UniformType::INT_ARRAY:
                shader.setIntArray(name, (const GLint*)value.dataPtr, value.size);
                break;
            case UniformType::FLOAT_ARRAY:
                shader.setFloatArray(name, (const GLfloat*)value.dataPtr, value.size);
                break;
            case UniformType::VEC2_ARRAY:
                shader.setVec2Array(name, (const glm::vec2*)value.dataPtr, value.size);
                break;
            case UniformType::VEC3_ARRAY:
                shader.setVec3Array(name, (const glm::vec3*)value.dataPtr, value.size);
                break;
            case UniformType::VEC4_ARRAY:
                shader.setVec4Array(name, (const glm::vec4*)value.dataPtr, value.size);
                break;
            case UniformType::MAT4_ARRAY:
                shader.setMat4Array(name, (const glm::mat4*)value.dataPtr, value.size);
                break;

            default:
                std::cerr << "Error: Unknown uniform type!\n";
                std::exit(EXIT_FAILURE);
            }
        }
    }

    
    void printUniforms() const {
        for (const auto& it : uniforms) {
            const std::string& name = it.first;
            const UniformValue& value = it.second;

            std::cout << "Uniform Name: " << name << ", Type: ";

            switch (value.dataType) {
            case UniformType::BOOL:
                std::cout << "BOOL\n";
                break;
            case UniformType::INT:
                std::cout << "INT\n";
                break;
            case UniformType::FLOAT:
                std::cout << "FLOAT\n";
                break;
            case UniformType::VEC2:
                std::cout << "VEC2\n";
                break;
            case UniformType::VEC3:
                std::cout << "VEC3\n";
                break;
            case UniformType::VEC4:
                std::cout << "VEC4\n";
                break;
            case UniformType::MAT2:
                std::cout << "MAT2\n";
                break;
            case UniformType::MAT3:
                std::cout << "MAT3\n";
                break;
            case UniformType::MAT4:
                std::cout << "MAT4\n";
                break;
            case UniformType::INT_ARRAY:
                std::cout << "INT_ARRAY\n";
                break;
            case UniformType::FLOAT_ARRAY:
                std::cout << "FLOAT_ARRAY\n";
                break;
            case UniformType::VEC2_ARRAY:
                std::cout << "VEC2_ARRAY\n";
                break;
            case UniformType::VEC3_ARRAY:
                std::cout << "VEC3_ARRAY\n";
                break;
            case UniformType::VEC4_ARRAY:
                std::cout << "VEC4_ARRAY\n";
                break;
            case UniformType::MAT4_ARRAY:
                std::cout << "MAT4_ARRAY\n";
                break;
            default:
                std::cout << "UNKNOWN\n";
                break;
            }
        }
    }

};
