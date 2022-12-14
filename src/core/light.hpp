#pragma once
#include "include.hpp"
#include "entity.hpp"
#include "math.hpp"

namespace SHOGUN {
class Light : public Entity {
public:
    float strength = 1;

    Vector3 getColor() {
        return color;
    }

    void setColor(Vector3 c) {
        color = c;
    }
private:
    Vector3 color;
};
}
