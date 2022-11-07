#pragma once
#include "guiElement.hpp"
#include "guiRenderer.hpp"

namespace SHOGUN {
class Rect : public GUIElement {
public:
    Rect();
    Shader* shader;

    void render();
private:
    unsigned int VAO, VBO;
};
}
