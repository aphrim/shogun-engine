#pragma once
#include "include.hpp"
#include "entity.hpp"
#include "light.hpp"
#include "gui/guiElement.hpp"

namespace SHOGUN {
class Scene {
public:
    void addEntity(Entity* entity);
    void tick();
    std::vector<Entity*> getEntities();
    std::vector<Light*> getLights();
    std::vector<GUIElement*> getGUIElements();

    Entity* getEntityById(std::string id);
private:
    std::vector<Entity*> entities;
    std::vector<Light*> lights;
    std::vector<GUIElement*> guiElements;

    std::unordered_map<std::string, Entity*> idLookup;
};
}
