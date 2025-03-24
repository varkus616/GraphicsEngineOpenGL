#include <ShadowMapFBO.hpp>


ShadowMapFBO::ShadowMapFBO(GLuint width, GLuint height) :
    m_width(width),
    m_height(height)
{
    glGenTextures(1, &m_shadowMapID);
    glBindTexture(GL_TEXTURE_2D, m_shadowMapID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
        m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    m_fbo.Bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER,
        GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_shadowMapID, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    m_fbo.UnBind();

}

void ShadowMapFBO::BindForWrite()
{
    glViewport(0, 0, m_width, m_height);
    m_fbo.Bind();
    glClear(GL_DEPTH_BUFFER_BIT);

}