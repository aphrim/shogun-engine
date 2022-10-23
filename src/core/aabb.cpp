#include "aabb.hpp"

namespace SHOGUN {

AABB::AABB(Vector3 position, Vector3 scale) {
    position = position.negate();
    xBounds = {position.x - scale.x / 2, position.x + scale.x / 2};
    yBounds = {position.y - scale.y / 2, position.y + scale.y / 2};
    zBounds = {position.z - scale.z / 2, position.z + scale.z / 2};
}

AABB::AABB(Vector2 xBounds, Vector2 yBounds, Vector2 zBounds) : xBounds(xBounds), yBounds(yBounds), zBounds(zBounds) {}

bool AABB::collides(Vector3 point) {
    return (
        (point.x >= xBounds.x && point.x <= xBounds.y) &&
        (point.y >= yBounds.x && point.y <= yBounds.y) &&
        (point.z >= zBounds.x && point.z <= zBounds.y)
    );
}

bool AABB::collides(AABB aabb) {
    return (
        (xBounds.x <= aabb.xBounds.y && xBounds.y >= aabb.xBounds.x) &&
        (yBounds.x <= aabb.yBounds.y && yBounds.y >= aabb.yBounds.x) &&
        (zBounds.x <= aabb.zBounds.y && zBounds.y >= aabb.zBounds.x)
    );
}

}
