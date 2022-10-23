#include "framebuffer.hpp"

namespace SHOGUN {

Framebuffer::Framebuffer() {
    glGenFramebuffers(1, &fbid);
    glGenRenderbuffers(1, &rbid);
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &fbid);    
}

void Framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, fbid);
}

void Framebuffer::bindDefault() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::makeDefault() {
    fbid = 0;
    rbid = 0;
}

void Framebuffer::renderToTexture(Texture* texture) {
    glBindFramebuffer(GL_FRAMEBUFFER, fbid);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->getId(), 0);
}

}
