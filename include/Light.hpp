#pragma once
#ifndef LIGHT_HPP
#define LIGHT_HPP
#include <glm/glm.hpp>


class Material {
public:
    GLuint diffuse;  // samplery 2D
    GLuint specular;
    glm::vec3 ambient;  // kolory
    float shininess;
    Material() = default;
    Material(GLuint diffuse, GLuint specular, glm::vec3 ambient, float shininess)
        : diffuse(diffuse), specular(specular), ambient(ambient), shininess(shininess) {
    }
};

class Light {
public:
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float constant;
    float linear;
    float quadratic;

    Light() {}

    Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
        float constant, float linear, float quadratic)
        : position(position), ambient(ambient), diffuse(diffuse), specular(specular),
        constant(constant), linear(linear), quadratic(quadratic) {
    }
};

class SpotLight : public Light {
public:
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

    SpotLight() {}

    SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
        float cutOff, float outerCutOff, float constant, float linear, float quadratic)
        : Light(position, ambient, diffuse, specular, constant, linear, quadratic),
        direction(direction), cutOff(cutOff), outerCutOff(outerCutOff) {
    }
};

class DirLight : public Light {
public:
    glm::vec3 direction;

    DirLight() {}

    DirLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
        float constant, float linear, float quadratic)
        : Light(glm::vec3(0.0f, 0.0f, 0.0f), ambient, diffuse, specular, constant, linear, quadratic),
        direction(direction) {
    }
};

class PointLight : public Light {
public:

    PointLight() {}

    PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
        float constant, float linear, float quadratic)
        : Light(position, ambient, diffuse, specular, constant, linear, quadratic) {
    }
};

#endif // !LIGHT_HPP
