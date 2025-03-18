#ifndef TRANSFORMABLE_HPP
#define TRANSFORMABLE_HPP

#include <Transform.hpp>
#include <glm/ext/matrix_transform.hpp>

enum class Axis {X, Y, Z};

class Transformable {
public:
    Transform transform;

    glm::vec3 getPosition() const { return transform.position; }
    glm::vec3 getScale() const { return transform.scale; }
    glm::vec3 getSize() const { return transform.size; }
    float getAngle() const { return transform.angle; }

    void setPosition(float x, float y, float z) {
        transform.setPosition(x, y, z);
    }

    void setScale(float x, float y, float z) {
        transform.setScale(x, y, z);
    }

    void setSize(float x, float y, float z) {
        transform.setSize(x, y, z);
    }

    void setAngle(float ang) {
        transform.setAngle(ang);
    }
    void rotate(float ang, Axis axis)
    {

        switch (axis)
        {
        case Axis::X:
            transform.setRotationVector(1.f, 0.f, 0.f);
            break;
        case Axis::Y:
            transform.setRotationVector(0.f, 1.f, 0.f);
            break;
        case Axis::Z:
            transform.setRotationVector(0.f, 0.f, 1.f);
            break;
        }

        transform.setAngle(ang);

    }

    void updateModelMatrix() {
        transform.modelMatrix =
            glm::translate(glm::mat4(1.f), transform.position) *
            glm::rotate(glm::mat4(1.f), glm::radians(transform.angle), transform.rotationVector) *
            glm::scale(glm::mat4(1.f), transform.scale * transform.size);
    }

};

#endif // TRANSFORMABLE_HPP
 