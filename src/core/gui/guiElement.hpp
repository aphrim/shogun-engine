#pragma once
#include "../include.hpp"
#include "../entity.hpp"
#include "../vector.hpp"

//Not much difference between <Entity> and <GUIElement> other than a method to render without requiring camera.
//Also, even though position and scale are scored in Vector3s, only the X and Y are used.
//For rotation, just the X component of the Vector3 is used.
namespace SHOGUN {
class GUIElement : public Entity {
public:
    GUIElement();

    virtual void render();
}
}
