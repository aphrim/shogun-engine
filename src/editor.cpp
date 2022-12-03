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
    Shader* shader = new Shader("shaders/3dtextureshader.vert", "shaders/pbrshader.frag");
    Texture* metallicTexture = new Texture("textures/rusted-iron/metallic.png");
    Texture* normalTexture = new Texture("textures/rusted-iron/normal.png");
    Texture* roughnessTexture = new Texture("textures/rusted-iron/roughness.png");
    Texture* albedoTexture = new Texture("textures/rusted-iron/albedo.png");
    shader->setInt("albedoMap", 0);
    shader->setInt("metallicMap", 1);
    shader->setInt("roughnessMap", 2);
    shader->setInt("normalMap", 3);
    Model* model = new Model("models/cube.obj");

    std::cout << "Created Textures" << std::endl;

    Mesh* mesh = new Mesh(model, shader);
    mesh->id = "Cube lol";
    mesh->name = "Cube lol";
    mesh->modelPath = "/models/cube.obj";
    mesh->setScale(Vector3(20,2,20));
    mesh->setPosition(Vector3(-5,0,-5));
    scene->addEntity(mesh);

    std::cout << "Added Mesh" << std::endl;

    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            Light* light = new Light();
            light->setPosition(Vector3(-4 + x * 8, 2, -4 + y * 8));
            light->setColor(Vector3(1, 1, 1));
            scene->addEntity(light);
        }
    }

    int tick = 0;

    std::cout << "Completed Initilization" << std::endl;
    while (!window->shouldClose()) {
        glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
        std::chrono::high_resolution_clock::time_point frameStart = std::chrono::high_resolution_clock::now();

        loop();

        glClear(GL_COLOR_BUFFER_BIT);
        camera->renderWidth = window->getWindowSize().x;
        camera->renderHeight = window->getWindowSize().y;
        camera->renderToFramebuffer(fb);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, albedoTexture->getId());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, metallicTexture->getId());
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, roughnessTexture->getId());
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, normalTexture->getId());

        GUIRenderer::renderWidth = window->getWindowSize().x;
        GUIRenderer::renderHeight = window->getWindowSize().y;
        guiRenderer->renderToFramebuffer(fb);
        window->update();

        std::chrono::high_resolution_clock::time_point frameEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> dur = frameEnd - frameStart;
        std::cout << "Fps:" << 1000 / dur.count() << '\n';
        tick++;
    }

    //ssf.serializeScene("src/sceneSaveNew.ssf");
}
