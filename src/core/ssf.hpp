//Shogun Save File (SSF)
#pragma once
#include "include.hpp"
#include "scene.hpp"
#include "obj.hpp"
#include "mesh.hpp"

namespace SHOGUN {

class SSF {
public:
    SSF(Scene* scene);

    void serializeScene(std::string filePath);
    void loadFromFile(std::string filePath);

private:
    Scene* scene;
    OBJParser objParser;

    void loadNext(std::stringstream& data);
    void loadMesh(std::stringstream& data);
};

}
