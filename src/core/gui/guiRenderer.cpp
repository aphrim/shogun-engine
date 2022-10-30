#include "guiRenderer.hpp";

GUIRenderer::renderToFramebuffer(Framebuffer* target) {
    for (GUIElement* el : scene->getGUIElements()) {
        el->render();
    }
}
