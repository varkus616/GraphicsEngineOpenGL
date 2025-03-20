#pragma once 
#ifndef LIGHT_HPP
#define LIGHT_HPP
#include <glm/glm.hpp>




struct DirectionalLight {
    glm::vec3 direction;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;


    DirectionalLight(glm::vec3 dir = { -2.2f, 1.0f, 2.0f },
        glm::vec3 amb = { 0.2f, 0.2f, 0.2f },
        glm::vec3 diff = { 0.5f, 0.5f, 0.5f },
        glm::vec3 spec = { 1.0f, 1.0f, 1.0f })
        : direction(dir), ambient(amb), diffuse(diff), specular(spec) {}
};





struct Light {
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float  constant;
    float  linear;
    float  quadratic;
    float  cutOff;

    Light(glm::vec3 pos = { -2.2f, 1.0f, 2.0f },
        glm::vec3 amb = { 0.2f, 0.2f, 0.2f },
        glm::vec3 diff = { 0.5f, 0.5f, 0.5f },
        glm::vec3 spec = { 1.0f, 1.0f, 1.0f })
        : position(pos), ambient(amb), diffuse(diff), specular(spec) {}
};

struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

    Material(glm::vec3 amb = { 1.f, 0.5f, 0.31f },
        glm::vec3 diff = { 1.f, 0.5f, 0.31f },
        glm::vec3 spec = { 0.5f, 0.5f, 0.5f },
        float shine = 32.f)
        : ambient(amb), diffuse(diff), specular(spec), shininess(shine) {}
};


#endif // !LIGHT_HPP
