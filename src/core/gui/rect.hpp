#pragma once
#include "guiElement.hpp"
#include "guiRenderer.hpp"

namespace SHOGUN {
class Rect : public GUIElement {
public:
    Rect();
    Shader* shader;

    void render();
    
    bool collides(Vector2 pos);

    void setColor(Vector3 c);
    Vector3 getColor();

private:
    unsigned int VAO, VBO;

    Vector3 color;
};
}
