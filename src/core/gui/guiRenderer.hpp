#pragma once
#include "../include.hpp"
#include "../entity.hpp"
#include "../math.hpp"
#include "../scene.hpp"
#include "../shader.hpp"
#include "../framebuffer.hpp"
#include "../window.hpp"

namespace SHOGUN {

class GUIRenderer {
public:
    void renderToFramebuffer(Framebuffer* target);
    Scene* scene;
    Window* window;

    static glm::mat4 projectionMatrix;
};


}
