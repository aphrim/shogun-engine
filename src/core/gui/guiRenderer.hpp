#pragma once
#include "../include.hpp"
#include "../entity.hpp"
#include "../vector.hpp"
#include "../scene.hpp"
#include "../shader.hpp"
#include "../framebuffer.hpp"

namespace SHOGUN {

class GUIRenderer {
public:
    void renderToFramebuffer(Framebuffer* target);
    static int renderWidth;
    static int renderHeight;
    Scene* scene;

    static glm::mat4 projectionMatrix;
};


}
