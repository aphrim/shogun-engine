#pragma once
#include "include.hpp"
#include "entity.hpp"
#include "vector.hpp"

namespace SHOGUN {
class Light : public Entity {
public:
    float strength;
    Vector3 color;
};
}
