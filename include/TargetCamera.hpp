#pragma once
#ifndef TARGET_CAMERA_HPP
#define TARGET_CAMERA_HPP
#include <AbstractCamera.hpp>

class CTargetCamera : public CAbstractCamera
{
public:
	CTargetCamera() = default;
	~CTargetCamera() = default;
	
	void Update();
	void Rotate(const float yaw, const float pitch, const float roll);
	void SetTarget(const glm::vec3 tgt) { this->target = tgt; }

	const glm::vec3 GetTarget() const { return target; }

	void Pan(const float dx, const float dy);
	void Zoom(const float amount);
	void Move(const float dx, const float dz);

protected:
	glm::vec3 target;
	float minRy, maxRy;
	float distance;
	float minDistance, maxDistance;
};

#endif // !TARGET_CAMERA_HPP

