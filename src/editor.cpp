#include <iostream>
#include "core/window.hpp"
#include "core/engine.hpp"
#include "core/mesh.hpp"
#include "core/scene.hpp"
#include "core/camera.hpp"
#include "core/shader.hpp"
#include "core/texture.hpp"
#include "core/material.hpp"
#include "core/obj.hpp"
#include "core/light.hpp"
#include "core/aabb.hpp"
#include "core/include.hpp"
#include "core/ssf.hpp"
#include "core/model.hpp"
#include "core/gui/rect.hpp"
#include "core/gui/button.hpp"
#include "core/gui/guiRenderer.hpp"
#include "util/noise.hpp"


using namespace SHOGUN;

Scene* scene;
Camera* camera;
Framebuffer* fb;
Window* window;
Engine* engine;

std::vector<AABB> collision;
OBJParser objParser;

void mouseMoveListener(Vector2 delta) {
    if (window->isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
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
    GUIRenderer* guiRenderer = new GUIRenderer();
    guiRenderer->scene = scene;
    guiRenderer->window = window;

    window->addListener(mouseMoveListener, WE_MOUSE_MOVE);
    camera->scene = scene;
    fb->makeDefault();

    SSF ssf = SSF(scene);

    PerlinNoise pn(true);
    Shader* shader = new Shader("shaders/3dtextureshader.vert", "shaders/pbrshader.frag");
    Material* brickMaterial = new Material("textures/mortar-bricks", "png");
    Material* rustedIronMaterial = new Material("textures/rusted-iron", "png");
    Model* model = new Model("models/cube.obj");

    Mesh* ironMesh = new Mesh(model, shader, rustedIronMaterial);
    ironMesh->id = "Cube 1";
    ironMesh->name = "Cube 1";
    ironMesh->setScale(Vector3(1,7,7));
    ironMesh->setRotation(Vector3(90,0,0));
    ironMesh->setPosition(Vector3(-1,0,5));
    scene->addEntity(ironMesh);

    Mesh* brickMesh = new Mesh(model, shader, brickMaterial);
    brickMesh->id = "Cube 2";
    brickMesh->name = "Cube 2";
    brickMesh->setScale(Vector3(7,1,7));
    brickMesh->setPosition(Vector3(3.5,0,5));
    scene->addEntity(brickMesh);

    Button* button = new Button();
    button->setScale(Vector3(500, 100, 0));
    button->setPosition(Vector3(200, 200, 1));
    button->pressColor = Vector3(0,0,1);
    button->hoverColor = Vector3(0,1,0);
    button->baseColor = Vector3(1,0,0);
    scene->addEntity(button);

    Light* light = new Light();
    light->setPosition(Vector3(5, 2, 5));
    light->setColor(Vector3(1, 1, 1));
    light->strength = 3;
    scene->addEntity(light);

    int tick = 0;
    ssf.serializeScene("src/sceneSave.ssf");
    while (!window->shouldClose()) {
        glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
        std::chrono::high_resolution_clock::time_point frameStart = std::chrono::high_resolution_clock::now();

        loop();

        ironMesh->setRotation(ironMesh->getRotation() + Vector3(0.1,0,0));
        light->setPosition(Vector3((sin(tick / 200.0f) + 1) * 2, 2, 5));

        glClear(GL_COLOR_BUFFER_BIT);
        rustedIronMaterial->use();
        camera->renderWidth = window->getWindowSize().x;
        camera->renderHeight = window->getWindowSize().y;
        camera->renderToFramebuffer(fb);

        std::cout << window->mouse << std::endl;
        button->setRotation(button->getRotation() + Vector3(1, 0, 0));
        scene->tick();

        guiRenderer->renderToFramebuffer(fb);
        window->update();

        std::chrono::high_resolution_clock::time_point frameEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> dur = frameEnd - frameStart;
        std::cout << "Fps:" << 1000 / dur.count() << '\n';
        tick++;
    }

}
