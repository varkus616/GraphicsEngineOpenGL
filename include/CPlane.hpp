#pragma once
#ifndef CPLANE_HPP
#define CPLANE_HPP

#include <glm/glm.hpp>

class CPlane {
public:
    glm::vec3 normal;
    float d;

    CPlane() : normal(0.0f, 0.0f, 0.0f), d(0.0f) {}

    CPlane(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3) {
        normal = glm::normalize(glm::cross(p2 - p1, p3 - p1));
        d = -glm::dot(normal, p1);
    }

    CPlane(const glm::vec3& normal, float d) : normal(normal), d(d) {}

    float Distance(const glm::vec3& point) const {
        return glm::dot(normal, point) + d;
    }

    bool IsPointInFront(const glm::vec3& point) const {
        return Distance(point) >= 0;
    }

    glm::vec4 getPoints() const { glm::vec4(normal, d); }

};
#endif // !CPLANE_HPP
