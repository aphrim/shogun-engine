#include "ssf.hpp"

namespace SHOGUN {

SSF::SSF(Scene* scene) : scene(scene) {}

//**********************************************************
//       SSF Serializer
//**********************************************************

void SSF::serializeScene(std::string filePath) {
    std::ofstream sceneFile;
    try {
        sceneFile.open(filePath); 
    } catch (std::ifstream::failure e) {
        std::cout << "Error opening SSF File " << filePath << std::endl;
    }

    for (Entity* entity : scene->getEntities()) {
        serializeEntity(sceneFile, entity);
    }

    sceneFile.close();
}

void SSF::serializeEntity(std::ofstream& sceneFile, Entity* entity) {
    if (dynamic_cast<Mesh*>(entity) != nullptr)
        serializeMesh(sceneFile, static_cast<Mesh*>(entity));        
}

void SSF::serializeMesh(std::ofstream& sceneFile, Mesh* entity) {
    sceneFile << "Mesh \n \n";
    sceneFile << "Position " << entity->getWorldPosition() << "\n";
    sceneFile << "Rotation " << entity->getWorldRotation() << "\n";
    sceneFile << "Scale " << entity->getWorldScale() << "\n";
    sceneFile << "Color " << entity->getColor() << "\n";
    if (entity->texture != nullptr && entity->texture->path != "")
        sceneFile << "Texture " << entity->texture->path << "\n";
    if (entity->shader != nullptr && entity->shader->vertexPath != "" 
            && entity->shader->fragmentPath != "")
        sceneFile << "Shader " << entity->shader->vertexPath
                  << " " << entity->shader->fragmentPath << "\n";
    if (entity->modelPath != "")
        sceneFile << "Model " << entity->modelPath << "\n";
    sceneFile << "Id " << entity->id << "\n";
    sceneFile << "Name " << entity->name << ";\n";
    sceneFile << "; \n";
}

void SSF::serializeLight(std::ofstream& sceneFile, Light* entity) {
    sceneFile << "Light \n \n";
    sceneFile << "Position " << entity->getWorldPosition() << "\n";
    sceneFile << "Rotation " << entity->getWorldRotation() << "\n";
    sceneFile << "Color " << entity->getColor() << "\n";
    sceneFile << "Strength " << entity->strength << "\n";
    sceneFile << "Id " << entity->id << "\n";
    sceneFile << "Name " << entity->name << "\n";
    sceneFile << "; \n";
}


//**********************************************************
//       SSF Loader
//**********************************************************

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
    std::string texturePath, modelPath, vertShaderPath, fragShaderPath, name, id;
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
        else if (property == "Name") {
            std::string in = "";
            while (in != ";") {
                data >> in;
                name += in + " ";
                if (in[in.size() - 1] == ';') {
                    name.pop_back();
                    break;
                }
            }
            name.pop_back();
        } else if (property == "Id")
            data >> id;
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
    mesh->modelPath = modelPath;
    mesh->id = id;
    mesh->name = name;

    scene->addEntity(mesh);
}

void SSF::loadLight(std::stringstream& data) {
    Vector3 position, rotation, color; 
    float strength;
    std::string name, id;
    while (true) {
        std::string property;
        data >> property;
        if (property == ";") break;

        if (property == "Position")
            data >> position.x >> position.y >> position.z;
        else if (property == "Rotation")
            data >> rotation.x >> rotation.y >> rotation.z;
        else if (property == "Color")
            data >> color.x >> color.y >> color.z;
        else if (property == "Strength")
            data >> strength;
        else if (property == "Name") {
            std::string in = "";
            while (in != ";") {
                data >> in;
                name += in + " ";
                if (in[in.size() - 1] == ';') {
                    name.pop_back();
                    break;
                }
            }
            name.pop_back();
        }
        else if (property == "Id")
            data >> id;
    }
    Light* light = new Light();
    light->setPosition(position);
    light->setRotation(rotation);
    light->setColor(color);
    light->strength = strength;
    light->name = name;
    light->id = id;

    scene->addEntity(light);
}

}
