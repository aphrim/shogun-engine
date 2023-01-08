#include "entity.hpp"

namespace SHOGUN {

void Entity::render(Entity* camera) {
}

std::vector<Entity*> Entity::getChildren() {
    return children;
}

void Entity::addChild(Entity* entity) {
    children.push_back(entity);
}

void Entity::setPosition(Vector3 pos) {
    position = pos;
    if (parent) {
        worldPosition = parent->getWorldPosition() + pos;
    } else worldPosition = pos;
    updateChildrenPosition();
}

void Entity::setRotation(Vector3 rot) {
    rotation = rot;
    if (parent)
        worldRotation = parent->getWorldRotation() + rot;
    else worldRotation = rot;
    updateChildrenRotation();
}

void Entity::setScale(Vector3 s) {
    scale = s;
    if (parent)
        worldScale = parent->getWorldScale() + s;
    else worldScale = s;
    updateChildrenScale();
}

void Entity::setWorldPosition(Vector3 pos, bool fromParent) {
    worldPosition = pos;
    if (!fromParent)
        if (parent)
            position = pos - parent->getWorldPosition();
        else position = pos;
    updateChildrenPosition();
}

void Entity::setWorldRotation(Vector3 rot, bool fromParent) {
    worldRotation = rot;
    if (!fromParent)
        if (parent)
            rotation = rot - parent->getWorldRotation();
        else rotation = rot;
    updateChildrenRotation();
}


void Entity::setWorldScale(Vector3 s, bool fromParent) {
    worldScale = s;
    if (!fromParent)
        if (parent)
            scale = s - parent->getWorldScale();
        else scale = s;
    updateChildrenScale();
}

void Entity::updateChildrenPosition() {
    for (Entity* child : children) {
        child->setWorldPosition(child->getPosition() + worldPosition, true);
    }
}

void Entity::updateChildrenRotation() {
    for (Entity* child : children) {
        child->setWorldRotation(child->getRotation() + worldRotation, true);
    }
}

void Entity::updateChildrenScale() {
    for (Entity* child : children) {
        child->setWorldScale(child->getScale() + worldScale, true);
    }
}

Vector3 Entity::getPosition() {
    return position;
}

Vector3 Entity::getRotation() {
    return rotation;
}

Vector3 Entity::getScale() {
    return scale;
}

Vector3 Entity::getWorldPosition() {
    return worldPosition;
}

Vector3 Entity::getWorldRotation() {
    return worldRotation;
}

Vector3 Entity::getWorldScale() {
    return worldScale;
}

void Entity::updateTransformMatrix() {
    transformMatrix = calc_transform_matrix(worldPosition, worldRotation, worldScale);
}

void Entity::updateTransformMatrix(Vector3 position, Vector3 rotation, Vector3 scale) {
    transformMatrix = calc_transform_matrix(position, rotation, scale);
}

void Entity::updateTransformMatrix(Vector3 position, Vector3 rotation, Vector3 scale, Vector3 adjScale) {
    transformMatrix = calc_transform_matrix(position, rotation, scale, adjScale);
}


}
