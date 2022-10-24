#pragma once
#include "include.hpp"
#include "entity.hpp"
#include "vector.hpp"

namespace SHOGUN {
class Light : public Entity {
public:
    float strength;

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
