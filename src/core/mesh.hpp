#pragma once
#include "include.hpp"
#include "entity.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "model.hpp"

namespace SHOGUN {
class Mesh : public Entity {
public:
    Mesh(Model* model, Shader* shader);
    Mesh(Model* model, Shader* shader, Texture* texture);

    void render(Entity* camera);

    Shader* shader;
    Texture* texture = nullptr;
    Model* model;

    void setColor(Vector3 c);
    Vector3 getColor();

    std::string modelPath;
private:
    void calcTransformMatrix();

    glm::mat4 transformMatrix;

    Vector3 color;
};
}
