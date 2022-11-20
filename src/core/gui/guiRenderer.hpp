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
    std::vector<GUIElement*> handleCollisions(Vector2 pos);
    static int renderWidth;
    static int renderHeight;
    Scene* scene;

    static glm::mat4 projectionMatrix;
};


}
