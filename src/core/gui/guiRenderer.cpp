#include "guiRenderer.hpp"

namespace SHOGUN {
    glm::mat4 GUIRenderer::projectionMatrix = glm::ortho(0, 800, 600, 0);

    void GUIRenderer::renderToFramebuffer(Framebuffer* target) {
        glDisable(GL_DEPTH_TEST);
        projectionMatrix = glm::ortho(0, (int) window->size.x, (int) window->size.y, 0);
        for (GUIElement* el : scene->getGUIElements()) {
            el->window = window;
            el->render();
        }
        glEnable(GL_DEPTH_TEST);
    }

    std::vector<GUIElement*> GUIRenderer::handleCollisions(Vector2 pos) {
        std::vector<GUIElement*> ret;
        for (GUIElement* el : scene->getGUIElements()) {
            if (el->collides(pos)) {
                ret.push_back(el);
            }
        }
        return ret;
    }
}
