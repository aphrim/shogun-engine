#include "camera.hpp"

namespace SHOGUN {

Camera::Camera() {
    glGenBuffers(1, &cameraUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, cameraUBO);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, cameraUBO, 0, sizeof(glm::mat4) * 2);
}

void Camera::render(Camera* camera) {

}

void Camera::renderToFramebuffer(Framebuffer* target) {
    target->bind();    
    boundVAO = -1, boundVBO = -1, boundShader = -1;
    std::vector<Entity*> entities = scene->getEntities();

    viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::rotate(viewMatrix, glm::radians(worldRotation.x), glm::vec3(1,0,0));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(worldRotation.y), glm::vec3(0,1,0));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(worldRotation.z), glm::vec3(0,0,1));
    viewMatrix = glm::translate(viewMatrix, worldPosition.glm());

    projectionMatrix = glm::perspective(glm::radians(fov), (float) renderWidth / renderHeight, 0.1f, 100.0f);

    glBindBuffer(GL_UNIFORM_BUFFER, cameraUBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(viewMatrix));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(projectionMatrix));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    for (Entity* e : entities) {
        renderEntity(e);
    }
}

void Camera::renderEntity(Entity* e) {
    e->render(this);
    for (Entity* c : e->getChildren()) renderEntity(c);
}

void Camera::setShaderLights(Shader* shader) {
    std::vector<Light*> lights = scene->getLights();
    shader->setFloat("lightCount", lights.size()); 
    char buffer[50];
    for (int i = 0; i < lights.size(); i++) {
        Light* light = lights[i];
        sprintf(buffer, "pointLights[%d].color", i);
        shader->setVec3(buffer, light->getColor());
        sprintf(buffer, "pointLights[%d].position", i);
        shader->setVec3(buffer, light->getWorldPosition());
        sprintf(buffer, "pointLights[%d].strength", i);
        shader->setFloat(buffer, light->strength);
    }
}

}
