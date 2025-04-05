#pragma once
#ifndef CUBEMAP_HPP
#define CUBEMAP_HPP
#include <GL/glew.h>
#include <string>
#include <vector>

class Cubemap
{
public:
	Cubemap(std::vector<std::string> faces);
	~Cubemap();


private:
	GLuint m_textureID;
};

#endif // !CUBEMAP_HPP
