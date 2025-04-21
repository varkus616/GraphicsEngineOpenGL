#include <GenericRenderable.hpp>


void GenericRenderable::draw(RenderTarget& target, RenderData& data)
{
    if (m_VAO)
	    target.draw(*m_VAO, data);
}

glm::mat4& GenericRenderable::getModelMatrix()
{
    if (transform.dirty) {
        updateModelMatrix();
        transform.dirty = false;
    }
    return transform.modelMatrix;
}
glm::vec4 GenericRenderable::getColor()
{
    return glm::vec4(1);
}