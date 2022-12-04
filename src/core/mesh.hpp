#pragma once
#include "include.hpp"
#include "entity.hpp"
#include "shader.hpp"
#include "material.hpp"
#include "camera.hpp"
#include "model.hpp"

namespace SHOGUN {
class Mesh : public Entity {
public:
    Mesh(Model* model, Shader* shader, Material* material);

    void render(Entity* camera);

    Shader* shader;
    Material* material = nullptr;
    Model* model;

    void setColor(Vector3 c);
    Vector3 getColor();
private:
    Vector3 color;
};
}
