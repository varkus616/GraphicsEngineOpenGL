#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <glm/glm.hpp>

struct Transform {

    bool dirty = true;
    float angle = 0.f;

    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
    glm::vec3 size = glm::vec3(1.0f);
    glm::vec3 rotationVector = glm::vec3(1.f);

    glm::mat4 modelMatrix = glm::mat4(1.0f);


    void setPosition(float x, float y, float z) {
        position.x = x;
        position.y = y;
        position.z = z;
        dirty = true;
    }

    void setScale(float x, float y, float z) {
        scale.x = x;
        scale.y = y;
        scale.z = z;
        dirty = true;
    }

    void setSize(float x, float y, float z) {
        size.x = x;
        size.y = y;
        size.z = z;
        dirty = true;
    }

    void setRotationVector(float x, float y, float z) {
        rotationVector.x = x;
        rotationVector.y = y;
        rotationVector.z = z;
        dirty = true;
    }

    void setAngle(float ang) {
        angle = ang;
        dirty = true;
    }
};

#endif // TRANSFORM_HPP
