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

    Entity* getEntityById(std::string id);
private:
    std::vector<Entity*> entities;
    std::vector<Light*> lights;

    std::unordered_map<std::string, Entity*> idLookup;
};
}
