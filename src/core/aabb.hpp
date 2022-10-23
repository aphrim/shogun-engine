#pragma once
#include "include.hpp"
#include "vector.hpp"

namespace SHOGUN {
class AABB {
public:
    AABB(Vector3 position, Vector3 scale);
    AABB(Vector2 xBounds, Vector2 yBounds, Vector2 zBounds);

    bool collides(Vector3 point);
    bool collides(AABB aabb);

    Vector2 xBounds, yBounds, zBounds;
};
}
