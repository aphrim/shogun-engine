#include "mesh.hpp"

namespace SHOGUN {
    
Mesh::Mesh(Model* model, Shader* shader, Material* material) : Entity(), shader(shader), model(model), material(material) {
    transformMatrix = glm::mat4(1);
}

void Mesh::render(Entity* c) {
    updateTransformMatrix();

    Camera* camera = static_cast<Camera*>(c);
    
    if (camera->boundMaterial != material->getId()) {
        material->use();
        camera->boundMaterial = material->getId();
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
