#pragma once
#include "guiElement.hpp"
#include "guiRenderer.hpp"
#include "rect.hpp"

namespace SHOGUN {
class Button: public Rect {
public:
    void tick();

    bool isPressed;
    bool isHovered;

    Vector3 baseColor;
    Vector3 hoverColor;
    Vector3 pressColor;
};
}
