#include <TargetCamera.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <algorithm>

void CTargetCamera::Update()
{
	glm::mat4 R = glm::yawPitchRoll(this->yaw, this->pitch, this->roll);
	glm::vec3 T = glm::vec3(0, 0, distance);
	T = glm::vec3(R * glm::vec4(T, 0.f));

	position = target + T;
	look = glm::normalize(target - position);
	up = glm::vec3(R * glm::vec4(0.f, 1.f, 0.f, 0.f));
	right = glm::cross(look, up);
	V = glm::lookAt(position, target, up);

}

void CTargetCamera::Move(const float dx, const float dz)
{
	glm::vec3 X = right * dx;
	glm::vec3 Y = look * dz;
	position += X + Y;
	target += X + Y;
	Update();
}

void CTargetCamera::Pan(const float dx, const float dy)
{
	glm::vec3 X = right * dx;
	glm::vec3 Y = up * dy;

	position += X + Y;
	target += X + Y;
	Update();
}

void CTargetCamera::Zoom(const float amount)
{
	position += look * amount;
	distance = glm::distance(position, target);
	distance = std::max(minDistance, std::min(distance, maxDistance));
	Update();
}

void CTargetCamera::Rotate(const float yaw, const float pitch, const float roll)
{
	CAbstractCamera::Rotate(yaw, pitch, roll);
}