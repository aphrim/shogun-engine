#include "scene.hpp"

namespace SHOGUN {

void Scene::addEntity(Entity* entity) {
    entities.push_back(entity);
    if (dynamic_cast<Light*>(entity) != nullptr) {
        lights.push_back(static_cast<Light*>(entity));
    }
}

std::vector<Entity*> Scene::getEntities() {
    return entities;
}

std::vector<Light*> Scene::getLights() {
    return lights;
}

}
