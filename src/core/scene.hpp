#pragma once
#include "include.hpp"
#include "entity.hpp"
#include "light.hpp"

namespace SHOGUN {
class Scene {
public:
    void addEntity(Entity* entity);
    std::vector<Entity*> getEntities();
    std::vector<Light*> getLights();
private:
    std::vector<Entity*> entities;
    std::vector<Light*> lights;
};
}
