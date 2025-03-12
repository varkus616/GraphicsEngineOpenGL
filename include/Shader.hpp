#ifndef SHADER_HPP
#define SHADER_HPP

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <string>

class Shader {
public:
    Shader();
    ~Shader();

    Shader(const Shader& other); // Copy constructor
    Shader& operator=(const Shader& other); // Copy assignment operator

    void addShader(const char* shaderPath, GLenum shaderType);
    void addShaderFromString(const std::string& shaderCode, GLenum shaderType);
    void bindAttribute(GLuint index, const std::string& name);
    void bindTransformFeedbackVaryings(const std::vector<const char*>& varyings, GLenum bufferMode);
    void bindTransformFeedback(GLenum target, GLuint id);
    void linkProgram();
    void use() const;

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setMat2(const std::string& name, const glm::mat2& mat, GLboolean transpose_flag = GL_FALSE) const;
    void setMat3(const std::string& name, const glm::mat3& mat, GLboolean transpose_flag = GL_FALSE) const;
    void setMat4(const std::string& name, const glm::mat4& mat, GLboolean transpose_flag = GL_FALSE) const;

    unsigned int getID() const { return ID; }

private:
    unsigned int ID;
    std::vector<GLuint> shaders;

    void checkCompileErrors(GLuint shader, std::string type);
    void copyFrom(const Shader& other);
};

#endif // SHADER_HPP