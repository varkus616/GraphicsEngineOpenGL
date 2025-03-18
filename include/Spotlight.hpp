#pragma once
#include <glm/glm.hpp>

class SpotLight {
public:
    glm::vec3 position;
    glm::vec3 direction;
    float cutoff; // K¹t graniczny sto¿ka œwiat³a (w stopniach)
    float outerCutoff; // Zewnêtrzny cutoff dla smooth transition

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    // Parametry t³umienia œwiat³a
    float constant;
    float linear;
    float quadratic;

    SpotLight(
        glm::vec3 pos, glm::vec3 dir, float cut, float outerCut,
        glm::vec3 amb, glm::vec3 diff, glm::vec3 spec,
        float c, float l, float q)
        : position(pos), direction(glm::normalize(dir)),
        cutoff(glm::cos(glm::radians(cut))),
        outerCutoff(glm::cos(glm::radians(outerCut))),
        ambient(amb), diffuse(diff), specular(spec),
        constant(c), linear(l), quadratic(q) {}

    void sendToShader(GLuint shaderID) {
        glUniform3fv(glGetUniformLocation(shaderID, "spotLight.position"), 1, &position[0]);
        glUniform3fv(glGetUniformLocation(shaderID, "spotLight.direction"), 1, &direction[0]);
        glUniform1f(glGetUniformLocation(shaderID, "spotLight.cutoff"), cutoff);
        glUniform1f(glGetUniformLocation(shaderID, "spotLight.outerCutoff"), outerCutoff);

        glUniform3fv(glGetUniformLocation(shaderID, "spotLight.ambient"), 1, &ambient[0]);
        glUniform3fv(glGetUniformLocation(shaderID, "spotLight.diffuse"), 1, &diffuse[0]);
        glUniform3fv(glGetUniformLocation(shaderID, "spotLight.specular"), 1, &specular[0]);

        glUniform1f(glGetUniformLocation(shaderID, "spotLight.constant"), constant);
        glUniform1f(glGetUniformLocation(shaderID, "spotLight.linear"), linear);
        glUniform1f(glGetUniformLocation(shaderID, "spotLight.quadratic"), quadratic);
    }
};
