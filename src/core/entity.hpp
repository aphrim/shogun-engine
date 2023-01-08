#pragma once
#include "include.hpp"
#include "math.hpp"

namespace SHOGUN {

class Entity {
public:
    void setPosition(Vector3 pos);
    void setRotation(Vector3 rot);
    void setScale(Vector3 s);
    void setWorldPosition(Vector3 pos, bool fromParent);
    void setWorldRotation(Vector3 rot, bool fromParent);
    void setWorldScale(Vector3 s, bool fromParent);
    Vector3 getPosition();
    Vector3 getRotation();
    Vector3 getScale();
    Vector3 getWorldPosition();
    Vector3 getWorldRotation();
    Vector3 getWorldScale();

    virtual void render(Entity* camera);

    std::vector<Entity*> getChildren();
    void addChild(Entity* child);

    std::string name;
    std::string id;
protected:
    void updateChildrenPosition();
    void updateChildrenRotation();
    void updateChildrenScale();

    void updateTransformMatrix();
    void updateTransformMatrix(Vector3 position, Vector3 rotation, Vector3 scale);
    void updateTransformMatrix(Vector3 position, Vector3 rotation, Vector3 scale, Vector3 adjScale);

    Entity* parent = nullptr;
    std::vector<Entity*> children;

    Vector3 position;
    Vector3 rotation;
    Vector3 scale = Vector3(1);

    Vector3 worldPosition;
    Vector3 worldRotation;
    Vector3 worldScale = Vector3(1);

    glm::mat4 transformMatrix;

};
}
