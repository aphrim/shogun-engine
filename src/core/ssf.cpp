#include "ssf.hpp"

namespace SHOGUN {

SSF::SSF(Scene* scene) : scene(scene) {}

void SSF::serializeScene(std::string filePath) {
    
}

void SSF::loadFromFile(std::string filePath) {
    std::stringstream data;
    
    try {
        std::ifstream sceneFile;
        sceneFile.open(filePath);

        data << sceneFile.rdbuf();
        sceneFile.close();
    } catch (std::ifstream::failure e) {
        std::cout << "Error reading SSF File " << filePath << std::endl;
    }

    while (data.peek() != EOF) {
        loadNext(data);
    }
}

void SSF::loadNext(std::stringstream& data) {
    std::string type;
    data >> type;
    if (type == "Mesh")
        loadMesh(data);
}

void SSF::loadMesh(std::stringstream& data) {   
    Vector3 position, rotation, scale, color;
    std::string texturePath, modelPath, vertShaderPath, fragShaderPath;
    char _;
    while (true) {
        std::string property;
        data >> property;
        if (property == ";") break;

        if (property == "Position")
            data >> position.x >> position.y >> position.z;
        else if (property == "Rotation")
            data >> rotation.x >> rotation.y >> rotation.z;
        else if (property == "Scale")
            data >> scale.x >> scale.y >> scale.z;
        else if (property == "Color")
            data >> color.x >> color.y >> color.z;
        else if (property == "Shader")
            data >> vertShaderPath >> fragShaderPath;
        else if (property == "Texture")
            data >> texturePath;
        else if (property == "Model")
            data >> modelPath;
        //else cin >> _;

    }

    Shader* shader = new Shader(vertShaderPath.c_str(), fragShaderPath.c_str());
    Texture* texture = nullptr;
    if (texturePath != "")
        texture = new Texture(texturePath.c_str());
    std::vector<float> model = objParser.parseObj(modelPath.c_str());

    Mesh* mesh;
    if (texture != nullptr)
        mesh = new Mesh(&(model[0]), model.size() * sizeof(float), shader, texture);
    else
        mesh = new Mesh(&(model[0]), model.size() * sizeof(float), shader);

    mesh->setWorldPosition(position, false);
    mesh->setWorldRotation(rotation, false);
    mesh->setWorldScale(scale, false);
    mesh->setColor(color);

    scene->addEntity(mesh);
}

}
