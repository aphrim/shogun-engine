#pragma once
#include "include.hpp"
#include "window.hpp"
#include "texture.hpp"

namespace SHOGUN {

class Framebuffer {
public:
    Framebuffer();
    ~Framebuffer();

    void bind();
    void makeDefault(); //Set framebuffer to default framebuffer
    static void bindDefault(); //Bind default framebuffer (0)

    void renderToTexture(Texture* texture);
private:
    unsigned int fbid, rbid; //Framebuffer id, Renderbuffer id
};
}
