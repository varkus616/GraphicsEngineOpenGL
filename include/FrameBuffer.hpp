#pragma once
#ifndef FRAME_BUFFER_HPP
#define FRAME_BUFFER_HPP

#include <GL/glew.h>

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();


	void Bind();
	void UnBind();
private:
	GLuint id;
};


#endif // !FRAME_BUFFER_HPP