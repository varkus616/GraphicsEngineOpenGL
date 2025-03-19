#pragma once 
#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/glm.hpp>

struct Light
{
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;

	glm::vec3 position;

};


#endif // !LIGHT_HPP
