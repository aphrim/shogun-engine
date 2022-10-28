#pragma once
#include "include.hpp"
#include "entity.hpp"
#include "vector.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "framebuffer.hpp"

namespace SHOGUN {

class Camera : public Entity {
public:
    Camera();

    virtual void render(Camera* camera);
    void renderToFramebuffer(Framebuffer* target);
    void setShaderLights(Shader* shader);

    float fov = 70;
    int renderWidth = 800;
    int renderHeight = 600;
    int boundVAO, boundVBO, boundShader, boundTexture;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    Scene* scene;
private:
    void renderEntity(Entity* e);
    unsigned int cameraUBO;
};

}
