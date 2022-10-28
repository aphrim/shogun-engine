#include "mesh.hpp"

namespace SHOGUN {
    
Mesh::Mesh(Model* model, Shader* shader) : Entity(), shader(shader), model(model) {
    transformMatrix = glm::mat4(1);
    calcTransformMatrix();
}

Mesh::Mesh(Model* model, Shader* shader, Texture* texture) : Entity(), shader(shader), texture(texture), model(model) {
    transformMatrix = glm::mat4(1);
}

void Mesh::render(Entity* c) {
    calcTransformMatrix();

    Camera* camera = static_cast<Camera*>(c);
    
    if (texture != nullptr && (camera->boundTexture != texture->getId())) {
        texture->use();
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
    }

    shader->setMat4("transform", transformMatrix);
    shader->setVec3("color", color);

    //camera->setShaderLights(shader);
    glDrawArrays(GL_TRIANGLES, 0, model->getVertC() / 5);
}


void Mesh::calcTransformMatrix() {
    transformMatrix = glm::mat4(1.0f);
    transformMatrix = glm::translate(transformMatrix, worldPosition.glm());
    transformMatrix = glm::rotate(transformMatrix, glm::radians(worldRotation.x), glm::vec3(1,0,0));
    transformMatrix = glm::rotate(transformMatrix, glm::radians(worldRotation.y), glm::vec3(0,1,0));
    transformMatrix = glm::rotate(transformMatrix, glm::radians(worldRotation.z), glm::vec3(0,0,1));
    transformMatrix = glm::scale(transformMatrix, worldScale.glm());
}

void Mesh::setColor(Vector3 c) {
    color = c;
}

Vector3 Mesh::getColor() {
    return color;
}

}
