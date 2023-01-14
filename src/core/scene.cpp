#include "scene.hpp"

namespace SHOGUN {

void Scene::addEntity(Entity* entity) {
    entities.push_back(entity);
    if (dynamic_cast<Light*>(entity) != nullptr) {
        lights.push_back(static_cast<Light*>(entity));
    } else if (dynamic_cast<GUIElement*>(entity) != nullptr) {
        guiElements.push_back(static_cast<GUIElement*>(entity));
    }
    idLookup[entity->id] = entity;
}

void Scene::tick() {
    for (Entity* entity : entities) entity->tick();
    for (GUIElement* el : guiElements) el->tick();
}

std::vector<Entity*> Scene::getEntities() {
    return entities;
}

std::vector<Light*> Scene::getLights() {
    return lights;
}

std::vector<GUIElement*> Scene::getGUIElements() {
    return guiElements;
}

Entity* Scene::getEntityById(std::string id) {
    if (!idLookup.count(id)) return nullptr;
    return idLookup[id];
}

}
