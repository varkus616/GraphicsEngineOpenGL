#pragma once
#ifndef SHADOW_MAP_FBO_HPP
#define SHADOW_MAP_FBO_HPP
#include <FrameBuffer.hpp>


class ShadowMapFBO
{
public:
	
	ShadowMapFBO(GLuint width, GLuint height);
	
	~ShadowMapFBO() = default;

	void BindForWrite();
	void BindForRead();
	void Unbind();

	GLuint m_width = 0;
	GLuint m_height = 0;

private:
	FrameBuffer m_fbo;
	GLuint m_shadowMapID;
};


#endif // SHADOW_MAP_FBO_HPP
