#include <FrameBuffer.hpp>
#include <Utilities.hpp>



FrameBuffer::FrameBuffer()
{
	GLCall(glGenFramebuffers(1, &id));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, id));
}

FrameBuffer::~FrameBuffer()
{
	if (id) {
		GLCall(glDeleteFramebuffers(1, &id));
		id = 0;
	}
}

void FrameBuffer::UnBind()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}
void FrameBuffer::Bind()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, id));
}