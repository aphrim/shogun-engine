#pragma once
#include "include.hpp"
#include "window.hpp"
#include "entity.hpp"

namespace SHOGUN {
class Engine {
public:
    Engine(Window* window);

    void render();
private:
    Window* window;
};
}
