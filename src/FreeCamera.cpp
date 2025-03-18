#include <FreeCamera.hpp>
#include <glm/gtx/euler_angles.hpp>

void CFreeCamera::Walk(const float dt)
{
	translation += (look * dt);
}

void CFreeCamera::Strafe(const float dt)
{
	translation += (right * dt);
}

void CFreeCamera::Lift(const float dt)
{
	translation += (up * dt);
}

void CFreeCamera::Update() 
{
	glm::mat4 rot = glm::yawPitchRoll(glm::radians(this->yaw),
		glm::radians(this->pitch), glm::radians(this->roll));
	
	this->position += translation;
	translation = glm::vec3(0);
	
	look = glm::vec3(rot * glm::vec4(0, 0, 1, 0));
	up = glm::vec3(rot * glm::vec4(0, 1, 0, 0));
	right = glm::cross(look, up);
	
	glm::vec3 tgt = position + look;
	
	V = glm::lookAt(position, tgt, up);

}