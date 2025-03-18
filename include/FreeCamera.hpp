#pragma once
#ifndef FREE_CAMERA_HPP
#define FREE_CAMERA_HPP
#include <AbstractCamera.hpp>

class CFreeCamera : public CAbstractCamera
{
public:
	CFreeCamera() = default;
	~CFreeCamera() = default;

	void Update() override;
	void Walk(const float dt);
	void Strafe(const float dt);
	void Lift(const float dt);
	void SetTranslation(const glm::vec3& t) { this->translation = t; }

	glm::vec3 GetTranslation() const { return this->translation; }
	void SetSpeed(const float speed) { this->speed = speed; }
	const float GetSpeet() const { return this->speed; }

protected:
	float speed;
	glm::vec3 translation;


};

#endif // !FREE_CAMERA_HPP
