#pragma once
#ifndef PHYSICS_HPP
#define PHYSICS_HPP
#include <glm/glm.hpp>



glm::vec3 W_Euler(glm::vec3 f, float h)
{
	return f * h;
}


typedef struct Point{

	int flag;
	float mass;
	float invMass = 1.f / mass;

	glm::vec3 position;
	glm::vec3 speed;
	glm::vec3 force;
	
	glm::vec3 dr;
	glm::vec3 dv;

};


#endif // !PHYSICS_HPP
