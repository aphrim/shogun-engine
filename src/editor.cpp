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

    window->addListener(mouseMoveListener, WE_MOUSE_MOVE);
    camera->scene = scene;
    fb->makeDefault();

    SSF ssf = SSF(scene);
    //ssf.loadFromFile("src/sceneSaveNew.ssf");

    //Entity* teapot = scene->getEntityById("2");

    PerlinNoise pn(true);
    Shader* shader = new Shader("shaders/3dtextureshader.vert", "shaders/3dtextureshader.frag");
    Texture* texture = new Texture("textures/dirt.png");
    Model* model = new Model("models/cube-mapped.obj");
    for (int x = 0; x < 50; x++) {
        for (int y = 0; y < 50; y++) {
            int h = pn.noise(x / 20.0, y / 20.0, 0) * 20;
            for (int z = 0; z < 3; z++) {
                Mesh* mesh = new Mesh(model, shader, texture);
                mesh->setPosition(Vector3(x, h - z, y));
                mesh->id = std::to_string(x + y * x + 3);
                mesh->name = "Cube lol";
                mesh->modelPath = "/models/cube-mapped.obj";
                mesh->setRotation(Vector3(270, 0, 0));
                scene->addEntity(mesh);
            }
        }
    }

    Rect* rect = new Rect();
    rect->setScale(Vector3(0.2, 0.2, 1));
    rect->setPosition(Vector3(0.25, 0.25, 0));
    scene->addEntity(rect);

    int tick = 0;

    while (!window->shouldClose()) {
        glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
        std::chrono::high_resolution_clock::time_point frameStart = std::chrono::high_resolution_clock::now();

        loop();

        //teapot->setRotation(teapot->getRotation() + Vector3(1, 0, 0));
        rect->setRotation(rect->getRotation() + Vector3(1, 0, 0));

        guiRenderer->handleCollisions(window->getGUISpaceMousePosition());

        glClear(GL_COLOR_BUFFER_BIT);
        camera->renderWidth = window->getWindowSize().x;
        camera->renderHeight = window->getWindowSize().y;
        camera->renderToFramebuffer(fb);

        GUIRenderer::renderWidth = window->getWindowSize().x;
        GUIRenderer::renderHeight = window->getWindowSize().y;
        guiRenderer->renderToFramebuffer(fb);
        window->update();

        std::chrono::high_resolution_clock::time_point frameEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> dur = frameEnd - frameStart;
        if (tick % 1000 == 0)
            std::cout << "Fps:" << 1000 / dur.count() << '\n';
        tick++;
    }

    //ssf.serializeScene("src/sceneSaveNew.ssf");
}
