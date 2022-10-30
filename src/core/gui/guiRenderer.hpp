#pragma once
#include "../include.hpp"
#include "entity.hpp"
#include "vector.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "framebuffer.hpp"

namespace SHOGUN {

class GUIRenderer {
public:
    GUIRenderer();
    void renderToFramebuffer(Framebuffer* target);
    int renderWidth = 800;
    int renderHeight = 600;
    Scene* scene;
}
}
