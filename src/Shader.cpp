#define GLEW_STATIC

#include "Shader.hpp"
#include <glm/gtc/type_ptr.hpp>

Shader::Shader() {
    
    ID = glCreateProgram();
}


Shader::~Shader() {
    for (GLuint shader : shaders) {
        glDeleteShader(shader);
    }
    glDeleteProgram(ID);
}

Shader::Shader(const Shader& other) {
    copyFrom(other);
}

Shader& Shader::operator=(const Shader& other) {
    if (this != &other) {
        for (GLuint shader : shaders) {
            glDeleteShader(shader);
        }
        glDeleteProgram(ID);

        copyFrom(other);
    }
    return *this;
}

void Shader::copyFrom(const Shader& other) {
    ID = glCreateProgram();
    shaders = other.shaders;

    for (GLuint shader : shaders) {
        glAttachShader(ID, shader);
    }

    glLinkProgram(ID);
}

void Shader::addShader(const char* shaderPath, GLenum shaderType) {
    std::string code;
    std::ifstream shaderFile;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shaderFile.open(shaderPath);
        std::stringstream shaderStream;

        shaderStream << shaderFile.rdbuf();
        shaderFile.close();

        code = shaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    const char* shaderCode = code.c_str();

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);
    checkCompileErrors(shader, "SHADER");

    glAttachShader(ID, shader);
    shaders.push_back(shader);
}

void Shader::addShaderFromString(const std::string& shaderCode, GLenum shaderType) {
    const char* code = shaderCode.c_str();
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);
    checkCompileErrors(shader, "SHADER");

    glAttachShader(ID, shader);
    shaders.push_back(shader);
}

void Shader::bindAttribute(GLuint index, const std::string& name) {
    glBindAttribLocation(ID, index, name.c_str());
}

void Shader::bindTransformFeedbackVaryings(const std::vector<const char*>& varyings, GLenum bufferMode) {
    glTransformFeedbackVaryings(ID, varyings.size(), varyings.data(), bufferMode);
}

void Shader::bindTransformFeedback(GLenum target, GLuint id) {
    glBindTransformFeedback(target, id);
}

void Shader::linkProgram() {
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    for (GLuint shader : shaders) {
        glDetachShader(ID, shader);
        glDeleteShader(shader);
    }
    shaders.clear();
}

void Shader::use() const {
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) const {
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const {
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat, GLboolean transpose_flag) const {
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, transpose_flag, glm::value_ptr(mat));
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat, GLboolean transpose_flag) const {
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, transpose_flag, glm::value_ptr(mat));
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat, GLboolean transpose_flag) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, transpose_flag, glm::value_ptr(mat));
}

void Shader::checkCompileErrors(GLuint shader, std::string type) {
    int success;
    int len = 0;
    char* infoLog = nullptr;
    if (type == "SHADER") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
        if (!success) {
            infoLog = (char*)malloc(len);
            glGetShaderInfoLog(shader, len, nullptr, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            free(infoLog);
        }
    }
    else if (type == "PROGRAM") {
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &len);
        if (!success) {
            infoLog = (char*)malloc(len);
            glGetProgramInfoLog(ID, len, nullptr, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << "ID:" << ID << " " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            free(infoLog);
        }
    }
}