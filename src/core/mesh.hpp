#pragma once
#include "include.hpp"
#include "entity.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "camera.hpp"

namespace SHOGUN {
class Mesh : public Entity {
public:
    Mesh(float* vertV, int vertC, Shader* shader);
    Mesh(float* vertV, int vertC, Shader* shader, Texture* texture);

    void render(Entity* camera);

    Shader* shader;
    Texture* texture = nullptr;

    void setColor(Vector3 c);
    Vector3 getColor();

private:
    unsigned int VAO, VBO;
    void calcTransformMatrix();

    int vertC;

    glm::mat4 transformMatrix;

    Vector3 color;
};
}
