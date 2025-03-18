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

void Shader::setIntArray(const std::string& name, const std::vector<GLint>& values) const {
    glUniform1iv(glGetUniformLocation(ID, name.c_str()), values.size(), values.data());
}

void Shader::setFloatArray(const std::string& name, const std::vector<GLfloat>& values) const {
    glUniform1fv(glGetUniformLocation(ID, name.c_str()), values.size(), values.data());
}

void Shader::setVec2Array(const std::string& name, const std::vector<glm::vec2>& values) const {
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), values.size(), &values[0][0]);
}

void Shader::setVec3Array(const std::string& name, const std::vector<glm::vec3>& values) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), values.size(), &values[0][0]);
}

void Shader::setVec4Array(const std::string& name, const std::vector<glm::vec4>& values) const {
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), values.size(), &values[0][0]);
}

void Shader::setMat2Array(const std::string& name, const std::vector<glm::mat2>& values, GLboolean transpose_flag) const {
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), values.size(), transpose_flag, glm::value_ptr(values[0]));
}

void Shader::setMat3Array(const std::string& name, const std::vector<glm::mat3>& values, GLboolean transpose_flag) const {
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), values.size(), transpose_flag, glm::value_ptr(values[0]));
}

void Shader::setMat4Array(const std::string& name, const std::vector<glm::mat4>& values, GLboolean transpose_flag) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), values.size(), transpose_flag, glm::value_ptr(values[0]));
}

void Shader::setIntArray(const std::string& name, const int* values, const size_t size) const {
    GLint location = glGetUniformLocation(ID, name.c_str());
    if (location != -1) {
        glUniform1iv(location, size, values);
    }
}

void Shader::setFloatArray(const std::string& name, const float* values, const size_t size) const {
    GLint location = glGetUniformLocation(ID, name.c_str());
    if (location != -1) {
        glUniform1fv(location, size, values);
    }
}

void Shader::setVec2Array(const std::string& name, const glm::vec2* values, const size_t size) const {
    GLint location = glGetUniformLocation(ID, name.c_str());
    if (location != -1) {
        glUniform2fv(location, size, reinterpret_cast<const float*>(values));
    }
}

void Shader::setVec3Array(const std::string& name, const glm::vec3* values, const size_t size) const {
    GLint location = glGetUniformLocation(ID, name.c_str());
    if (location != -1) {
        glUniform3fv(location, size, reinterpret_cast<const float*>(values));
    }
}

void Shader::setVec4Array(const std::string& name, const glm::vec4* values, const size_t size) const {
    GLint location = glGetUniformLocation(ID, name.c_str());
    if (location != -1) {
        glUniform4fv(location, size, reinterpret_cast<const float*>(values));
    }
}

void Shader::setMat2Array(const std::string& name, const glm::mat2* values, const size_t size, GLboolean transpose_flag) const {
    GLint location = glGetUniformLocation(ID, name.c_str());
    if (location != -1) {
        glUniformMatrix2fv(location, size, transpose_flag, reinterpret_cast<const float*>(values));
    }
}

void Shader::setMat3Array(const std::string& name, const glm::mat3* values, const size_t size, GLboolean transpose_flag) const {
    GLint location = glGetUniformLocation(ID, name.c_str());
    if (location != -1) {
        glUniformMatrix3fv(location, size, transpose_flag, reinterpret_cast<const float*>(values));
    }
}

void Shader::setMat4Array(const std::string& name, const glm::mat4* values, const size_t size, GLboolean transpose_flag) const {
    GLint location = glGetUniformLocation(ID, name.c_str());
    if (location != -1) {
        glUniformMatrix4fv(location, size, transpose_flag, reinterpret_cast<const float*>(values));
    }
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