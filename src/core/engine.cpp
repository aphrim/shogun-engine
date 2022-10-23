#include "engine.hpp"

namespace SHOGUN {

static void windowSizeChangeCallback(Vector2 size) {
    glViewport(0, 0, size.x, size.y);
}

Engine::Engine(Window* window) : window(window) {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw "Glad initalization error";
    }
    glViewport(0, 0, window->getWindowSize().x, window->getWindowSize().y);
    glEnable(GL_DEPTH_TEST);
    window->addListener(windowSizeChangeCallback, WE_SIZE_CHANGE);
}

void Engine::render() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}
}
