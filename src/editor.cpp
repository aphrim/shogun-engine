#include <iostream>
#include "core/window.hpp"
#include "core/engine.hpp"
#include "core/mesh.hpp"
#include "core/scene.hpp"
#include "core/camera.hpp"
#include "core/shader.hpp"
#include "core/texture.hpp"
#include "core/obj.hpp"
#include "core/light.hpp"
#include "core/aabb.hpp"
#include "core/include.hpp"

using namespace SHOGUN;

Scene* scene;
Camera* camera;
Framebuffer* fb;
Window* window;
Engine* engine;

std::vector<AABB> collision;
OBJParser objParser;

void mouseMoveListener(Vector2 delta) {
    if (window->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        camera->setRotation(camera->getRotation() + Vector3(-delta.y, delta.x, 0));
}

void loop() {
    Vector3 moveVector; 
    if (window->isKeyPressed(GLFW_KEY_W))
        moveVector += Vector3(0,0,1);
    if (window->isKeyPressed(GLFW_KEY_S))
        moveVector -= Vector3(0,0,1);
    if (window->isKeyPressed(GLFW_KEY_A))
        moveVector += Vector3(1,0,0);
    if (window->isKeyPressed(GLFW_KEY_D))
        moveVector -= Vector3(1,0,0);
    if (window->isKeyPressed(GLFW_KEY_Q))
        moveVector += Vector3(0,1,0);
    if (window->isKeyPressed(GLFW_KEY_E))
        moveVector -= Vector3(0,1,0);

    float angle = camera->getRotation().radians().y;
    moveVector = Vector3(
        cos(angle) * moveVector.x - sin(angle) * moveVector.z,
        moveVector.y,
        sin(angle) * moveVector.x + cos(angle) * moveVector.z
    );
    camera->setPosition(camera->getPosition() + moveVector / 3);
}

int main() {
    window = new Window(Vector2(800, 600), "my window", false);
    engine = new Engine(window);
    scene = new Scene();
    camera = new Camera();
    fb = new Framebuffer();
    Framebuffer* cubefb = new Framebuffer();

    window->addListener(mouseMoveListener, WE_MOUSE_MOVE);
    camera->scene = scene;
    fb->makeDefault();

    OBJParser objParser;
    Shader* shader = new Shader("shaders/3dtextureshader.vert", "shaders/3dtextureshader.frag");
    Shader* colorShader = new Shader("shaders/3dshader.vert", "shaders/3dshaderlight.frag");
    Texture* texture = new Texture(2560, 1390);
    std::vector<float> cubeModel = objParser.parseObj("models/cube.obj");
    std::vector<float> teapotModel = objParser.parseObj("models/teapot.obj");
    Mesh* cubeMesh = new Mesh(&(cubeModel[0]), cubeModel.size() * sizeof(float), shader, texture);
    cubeMesh->setScale(Vector3(2560/1390.0,1390/2560.0,2560/1390.0) * 10);
    cubeMesh->setPosition(Vector3(0,5,0));


    Texture* groundTexture = new Texture("textures/proto.png");
    Mesh* ground = new Mesh(&(cubeModel[0]), cubeModel.size() * sizeof(float), shader, groundTexture);
    ground->setPosition(Vector3(0,-2,0));
    ground->setScale(Vector3(100,1,100));

    Mesh* teapot = new Mesh(&(teapotModel[0]), teapotModel.size() * sizeof(float), colorShader);
    teapot->setScale(Vector3(0.1,0.1,0.1));
    teapot->setPosition(Vector3(10,5,0));

    camera->renderWidth = 800, camera->renderHeight = 800;
    camera->renderToFramebuffer(cubefb);
    cubefb->renderToTexture(texture);

    scene->addEntity(cubeMesh);
    scene->addEntity(ground);
    scene->addEntity(teapot);

    int tick = 0;
    while (!window->shouldClose()) {
        glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
        std::chrono::high_resolution_clock::time_point frameStart = std::chrono::high_resolution_clock::now();

        loop();

        teapot->setRotation(teapot->getRotation() + Vector3(0.3,0.3,0));
        teapot->setColor(Vector3(sin(tick/30.0) + 1 / 2.0, sin(tick/20.0) + 1 / 2.0, sin(tick/50.0) + 1 / 2.0));

        cubefb->bind();
        glClear(GL_COLOR_BUFFER_BIT);
        camera->renderToFramebuffer(cubefb);
        cubefb->renderToTexture(texture);
        camera->renderWidth = window->getWindowSize().x;
        camera->renderHeight = window->getWindowSize().y;
        camera->renderToFramebuffer(fb);
        window->update();

        std::chrono::high_resolution_clock::time_point frameEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> dur = frameEnd - frameStart;
        std::cout << "Fps:" << 1000 / dur.count() << std::endl;
        tick++;
    }
}
