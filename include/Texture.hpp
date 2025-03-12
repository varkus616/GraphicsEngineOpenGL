#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>

struct Texture
{
	Texture() = default;
	Texture(GLuint id) :id(id) {};
	GLuint id;
};
#endif // TEXTURE_HPP
