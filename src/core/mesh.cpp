#include "mesh.hpp"

namespace SHOGUN {
    
Mesh::Mesh(float* vertV, int vertC, Shader* shader) : Entity(), shader(shader), vertC(vertC) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertC, vertV, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6*sizeof(float)));
    glEnableVertexAttribArray(2);

    transformMatrix = glm::mat4(1);
    calcTransformMatrix();
}

Mesh::Mesh(float* vertV, int vertC, Shader* shader, Texture* texture) : Entity(), shader(shader), texture(texture), vertC(vertC) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertC, vertV, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6*sizeof(float)));
    glEnableVertexAttribArray(2);

    transformMatrix = glm::mat4(1);
}

void Mesh::render(Entity* c) {
    calcTransformMatrix();

    if (texture != nullptr)
        texture->use();

     
    Camera* camera = static_cast<Camera*>(c);
    
    int curVAO, curVBO;

    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &curVAO);
    if (curVAO != VAO) 
        glBindVertexArray(VAO);

    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &curVBO);
    if (curVBO != VBO)
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

    shader->use();
    shader->setMat4("projection", camera->projectionMatrix);
    shader->setMat4("view", camera->viewMatrix);
    shader->setMat4("transform", transformMatrix);
    shader->setVec3("viewPos", camera->getWorldPosition());

    camera->setShaderLights(shader);
    glDrawArrays(GL_TRIANGLES, 0, vertC / 5);
}


void Mesh::calcTransformMatrix() {
    transformMatrix = glm::mat4(1.0f);
    transformMatrix = glm::translate(transformMatrix, worldPosition.glm());
    transformMatrix = glm::rotate(transformMatrix, glm::radians(worldRotation.x), glm::vec3(1,0,0));
    transformMatrix = glm::rotate(transformMatrix, glm::radians(worldRotation.y), glm::vec3(0,1,0));
    transformMatrix = glm::rotate(transformMatrix, glm::radians(worldRotation.z), glm::vec3(0,0,1));
    transformMatrix = glm::scale(transformMatrix, worldScale.glm());
}

}
