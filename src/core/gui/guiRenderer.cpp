#include "guiRenderer.hpp"

namespace SHOGUN {
    glm::mat4 GUIRenderer::projectionMatrix = glm::ortho(0, 800, 600, 0);
    int GUIRenderer::renderWidth = 800, GUIRenderer::renderHeight = 600;

    void GUIRenderer::renderToFramebuffer(Framebuffer* target) {
        glDisable(GL_DEPTH_TEST);
        projectionMatrix = glm::ortho(0, renderWidth, renderHeight, 0);
        for (GUIElement* el : scene->getGUIElements()) {
            el->render();
        }
        glEnable(GL_DEPTH_TEST);
    }
}
