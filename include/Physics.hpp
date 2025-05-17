#pragma once
#ifndef PHYSICS_HPP
#define PHYSICS_HPP


#define P_ZAW	0x00000001
#define P_NORM	0x00000002
#include <glm/glm.hpp>

inline glm::vec3 W_Euler(glm::vec3 f, float h)
{
	return f * h;
}


typedef struct SferaN
{
	glm::vec3 pos = { 0,0,0 };
	float R = 0;
	float tlum = 0;
};

typedef struct Point{

	Point() = default;
	Point(float x, float y, float z):position(x,y,z){}

	int flag = 0;
	float mass = 0;
	float invMass = 0;

	glm::vec3 position = {0, 0, 0};
	glm::vec3 speed = {0, 0, 0};
	glm::vec3 force = {0, 0, 0};
	
	glm::vec3 dr = { 0, 0, 0 };
	glm::vec3 dv = { 0, 0, 0 };

};


#endif // !PHYSICS_HPP
