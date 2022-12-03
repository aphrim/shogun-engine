#include "mesh.hpp"

namespace SHOGUN {
    
Mesh::Mesh(Model* model, Shader* shader) : Entity(), shader(shader), model(model) {
    transformMatrix = glm::mat4(1);
}

Mesh::Mesh(Model* model, Shader* shader, Texture* texture) : Entity(), shader(shader), texture(texture), model(model) {
    transformMatrix = glm::mat4(1);
}

void Mesh::render(Entity* c) {
    updateTransformMatrix();

    Camera* camera = static_cast<Camera*>(c);
    
    if (texture != nullptr && (camera->boundTexture != texture->getId())) {
        //texture->use();
        camera->boundTexture = texture->getId();
    }

    if (camera->boundVAO != model->getVAO()) {
        glBindVertexArray(model->getVAO());
        camera->boundVAO = model->getVAO();
    }

    if (camera->boundVBO != model->getVBO()) {
        glBindBuffer(GL_ARRAY_BUFFER, model->getVBO());
        camera->boundVBO = model->getVBO();
    }

    if (camera->boundShader != shader->ID) {
        shader->use();
        camera->boundShader = shader->ID;
        camera->setShaderLights(shader);
    }

    shader->setMat4("transform", transformMatrix);
    shader->setVec3("color", color);

    glDrawArrays(GL_TRIANGLES, 0, model->getVertC() / 5);
}

void Mesh::setColor(Vector3 c) {
    color = c;
}

Vector3 Mesh::getColor() {
    return color;
}

}
