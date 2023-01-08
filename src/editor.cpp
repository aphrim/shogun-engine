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
    GUIRenderer* guiRenderer = new GUIRenderer();
    guiRenderer->scene = scene;
    guiRenderer->window = window;

    window->addListener(mouseMoveListener, WE_MOUSE_MOVE);
    camera->scene = scene;
    fb->makeDefault();

    SSF ssf = SSF(scene);

    PerlinNoise pn(true);
    Shader* shader = new Shader("shaders/3dtextureshader.vert", "shaders/pbrshader.frag");
    Material* carpetMaterial = new Material("textures/mortar-bricks", "png");
    Material* rustedIronMaterial = new Material("textures/rusted-iron", "png");
    Model* model = new Model("models/cube.obj");

    Mesh* mesh = new Mesh(model, shader, rustedIronMaterial);
    mesh->id = "Cube 1";
    mesh->name = "Cube 1";
    mesh->setScale(Vector3(7,1,7));
    mesh->setPosition(Vector3(-5,0,4));
    scene->addEntity(mesh);

    mesh = new Mesh(model, shader, carpetMaterial);
    mesh->id = "Cube 2";
    mesh->name = "Cube 2";
    mesh->setScale(Vector3(7,1,7));
    mesh->setPosition(Vector3(5,0,5));
    scene->addEntity(mesh);

    Rect* rect = new Rect();
    rect->setScale(Vector3(500, 100, 0));
    rect->setPosition(Vector3(200, 200, 1));
    scene->addEntity(rect);



    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            Light* light = new Light();
            light->setPosition(Vector3(-4 + x * 8, 1, -4 + y * 8));
            light->setColor(Vector3(1, 1, 1));
            light->strength = 5;
            scene->addEntity(light);
        }
    }

    int tick = 0;
    ssf.serializeScene("src/sceneSave.ssf");
    while (!window->shouldClose()) {
        glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
        std::chrono::high_resolution_clock::time_point frameStart = std::chrono::high_resolution_clock::now();

        loop();

        glClear(GL_COLOR_BUFFER_BIT);
        rustedIronMaterial->use();
        camera->renderWidth = window->getWindowSize().x;
        camera->renderHeight = window->getWindowSize().y;
        camera->renderToFramebuffer(fb);

        std::cout << window->mouse << std::endl;
        rect->setRotation(rect->getRotation() + Vector3(1, 0, 0));
        if (rect->collides(window->mouse))
            rect->setColor(Vector3(0,1,0));
        else
            rect->setColor(Vector3(1,0,0));

        guiRenderer->renderToFramebuffer(fb);
        window->update();

        std::chrono::high_resolution_clock::time_point frameEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> dur = frameEnd - frameStart;
        std::cout << "Fps:" << 1000 / dur.count() << '\n';
        tick++;
    }

}
