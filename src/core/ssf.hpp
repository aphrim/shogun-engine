//Shogun Save File (SSF)
#pragma once
#include "include.hpp"
#include "scene.hpp"
#include "obj.hpp"

#include "mesh.hpp"
#include "light.hpp"

namespace SHOGUN {

class SSF {
public:
    SSF(Scene* scene);

    void serializeScene(std::string filePath);
    void loadFromFile(std::string filePath);

private:
    Scene* scene;
    OBJParser objParser;

    void serializeEntity(std::ofstream& sceneFile, Entity* entity);
    void serializeMesh(std::ofstream& sceneFile, Mesh* entity);
    void serializeLight(std::ofstream& sceneFile, Light* entity);

    void loadNext(std::stringstream& data);
    void loadMesh(std::stringstream& data);
    void loadLight(std::stringstream& data);
};

}
