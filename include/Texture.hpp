#pragma once
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>
#include <SOIL2/SOIL2.h>
#include <iostream>
#include <string>

class Texture {
public:
    Texture() = default;
    explicit Texture(const std::string& path) {
        loadFromFile(path);
    }

    ~Texture() {
        if (id != 0) {
            glDeleteTextures(1, &id);
        }
    }

    Texture(const Texture&) = delete;               // nie kopiujemy tekstur
    Texture& operator=(const Texture&) = delete;

    Texture(Texture&& other) noexcept {
        id = other.id;
        other.id = 0;
    }

    Texture& operator=(Texture&& other) noexcept {
        if (this != &other) {
            if (id != 0) glDeleteTextures(1, &id);
            id = other.id;
            other.id = 0;
        }
        return *this;
    }

    bool loadFromFile(const std::string& path) {
        id = SOIL_load_OGL_texture(
            path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y
        );

        if (id == 0) {
            std::cerr << "[Texture] Warning: could not load texture: " << path << std::endl;
            return false;
        }

        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);

        if (glewIsSupported("GL_EXT_texture_filter_anisotropic")) {
            GLfloat aniso = 0.0f;
            glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);
        }

        glBindTexture(GL_TEXTURE_2D, 0);
        return true;
    }

    void bind(GLenum textureUnit = GL_TEXTURE0) const {
        glActiveTexture(textureUnit);
        glBindTexture(GL_TEXTURE_2D, id);
    }

    void unbind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    GLuint getID() const { return id; }

    bool isValid() const { return id != 0; }

private:
    GLuint id = 0;
};

#endif // TEXTURE_HPP
