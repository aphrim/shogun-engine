//Shogun Save File (SSF)
#pragma once
#include "include.hpp"
#include "scene.hpp"
#include "obj.hpp"

#include "mesh.hpp"
#include "model.hpp"
#include "material.hpp"
#include "texture.hpp"
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

    Material* loadMaterial(std::string albedoPath, std::string metallicPath,
                            std::string roughnessPath, std::string normalPath);
    Model* loadModel(std::string path);
    Texture* loadTexture(std::string path);
    Shader* loadShader(std::string vertShaderPath, std::string fragShaderPath);

    std::map<std::string, Material*> materialCache;
    std::map<std::string, Model*> modelCache;
    std::map<std::string, Shader*> shaderCache;
    std::map<std::string, Texture*> textureCache;
};

}
