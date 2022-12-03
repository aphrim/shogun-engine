#pragma once
#include "../include.hpp"
#include "../entity.hpp"
#include "../math.hpp"

//Not much difference between <Entity> and <GUIElement> other than a method to render without requiring camera.
//Also, even though position and scale are scored in Vector3s, only the X and Y are used.
namespace SHOGUN {
class GUIElement : public Entity {
public:
    virtual void render() {}
    virtual bool collides(Vector2 pos) {return true;}
};
}
