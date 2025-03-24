#pragma once
#ifndef ABSTRACT_CAMERA_HPP
#define ABSTRACT_CAMERA_HPP

#include <glm/glm.hpp>
#include <CPlane.hpp>

class CAbstractCamera
{
public:
	
	CAbstractCamera(void) = default;
	~CAbstractCamera(void) = default;
	
	void SetupProjection(const float fovy, const float aspectRatio, const float near=0.1f, const float far=1000.0f);
	
	virtual void Update() = 0;
	virtual void Rotate(const float yaw, const float pitch, const float roll);
	virtual void ResetRotation();
	
	const glm::mat4 GetViewMatrix() const { return V; }
	const glm::mat4 GetProjectionMatrix() const { return P; }

	void SetPosition(const glm::vec3& v);
	glm::vec3 GetPosition()const { return this->position; }
	glm::vec3 GetDirection()const { return this->look; }
	
	void SetFov(const float fov) { this->fov = fov; }
	const float	GetFov() const { return fov; }
	const float GetAspectRatio() const { return aspect_ratio; }

	const float GetNearPlane() const { return Znear; }
	const float GetFarPlane() const { return Zfar; }

	void CalcFrustumPlanes();
	bool IsPointInFrustum(const glm::vec3& point) const;
	bool IsSphereInFrustum(const glm::vec3& center, const float radius) const;
	bool IsBoxInFrustum(const glm::vec3& min, const glm::vec3& max) const;

	const CPlane* GetFrustumPlanes() const { return planes; }

	glm::vec3 farPts[4];
	glm::vec3 nearPts[3];
protected:
	float yaw, pitch, roll, fov, aspect_ratio, Znear, Zfar;
	static glm::vec3 UP;
	glm::vec3 look;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 position;
	glm::mat4 V;
	glm::mat4 P;
	CPlane planes[6];	
};





#endif // !ABSTRACT_CAMERA_HPP
