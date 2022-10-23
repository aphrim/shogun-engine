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
private:
    void calcTransformMatrix();

    unsigned int VAO, VBO;
    int vertC;

    glm::mat4 transformMatrix;

};
}
