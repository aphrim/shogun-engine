#include "button.hpp"

namespace SHOGUN {

void Button::tick() {
    if (window != nullptr && collides(window->mouse)) {
        if (!isHovered) window->hoverCount++;
        isHovered = true;
        if (window->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
            isPressed = true; 
            setColor(pressColor);
        } else {
            setColor(hoverColor); 
        }
    } else {
        if (window != nullptr && isHovered) window->hoverCount--;
        setColor(baseColor);
        isHovered = false;
        isPressed = false;
    }
}

}
