#include "camera.hpp"

namespace SHOGUN {

void Camera::render(Camera* camera) {

}

void Camera::renderToFramebuffer(Framebuffer* target) {
    target->bind();    
    std::vector<Entity*> entities = scene->getEntities();

    viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::rotate(viewMatrix, glm::radians(worldRotation.x), glm::vec3(1,0,0));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(worldRotation.y), glm::vec3(0,1,0));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(worldRotation.z), glm::vec3(0,0,1));
    viewMatrix = glm::translate(viewMatrix, worldPosition.glm());

    projectionMatrix = glm::perspective(glm::radians(fov), (float) renderWidth / renderHeight, 0.1f, 100.0f);

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
