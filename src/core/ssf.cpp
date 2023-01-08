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
    if (entity->material != nullptr) {
        sceneFile << "Albedo " << entity->material->albedo->path << "\n";
        sceneFile << "Metallic " << entity->material->metallic->path << "\n";
        sceneFile << "Roughness " << entity->material->roughness->path << "\n";
        sceneFile << "Normal " << entity->material->normal->path << "\n";
    }
    if (entity->shader != nullptr && entity->shader->vertexPath != "" 
            && entity->shader->fragmentPath != "")
        sceneFile << "Shader " << entity->shader->vertexPath
                  << " " << entity->shader->fragmentPath << "\n";
    if (entity->model->path != "")
        sceneFile << "Model " << entity->model->path << "\n";
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
    std::string albedoPath, metallicPath, roughnessPath, normalPath, modelPath, vertShaderPath, fragShaderPath, name, id;
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
        else if (property == "Albedo")
            data >> albedoPath;
        else if (property == "Metallic")
            data >> metallicPath;
        else if (property == "Roughness")
            data >> roughnessPath;
        else if (property == "Normal")
            data >> normalPath;
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

    Mesh* mesh;
    Model* model = loadModel(modelPath);
    Shader* shader = loadShader(vertShaderPath, fragShaderPath);
    Material* material = loadMaterial(albedoPath, metallicPath, roughnessPath, normalPath);

    mesh = new Mesh(model, shader, material);

    mesh->setWorldPosition(position, false);
    mesh->setWorldRotation(rotation, false);
    mesh->setWorldScale(scale, false);
    mesh->setColor(color);
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

Texture* SSF::loadTexture(std::string path) {
    if (textureCache[path]) return textureCache[path];
    Texture* texture = new Texture(path, TEXTURE_2D);
    textureCache[path] = texture;
    return texture;
}

Material* SSF::loadMaterial(std::string albedoPath, std::string metallicPath,
                            std::string roughnessPath, std::string normalPath) {
    if (materialCache[albedoPath + "|" + metallicPath + "|"
                        + roughnessPath + "|" + normalPath] != nullptr) 
        return materialCache[albedoPath + "|" + metallicPath + "|"
                                + roughnessPath + "|" + normalPath];

    Material* material = new Material(loadTexture(albedoPath), loadTexture(metallicPath),
                                        loadTexture(roughnessPath), loadTexture(normalPath));
    materialCache[albedoPath + "|" + metallicPath + "|" 
        + roughnessPath + "|" + normalPath] = material;
    return material;
}

Model* SSF::loadModel(std::string path) {
    if (modelCache[path] != nullptr)
        return modelCache[path];
    Model* model = new Model(path);
    modelCache[path] = model;
    return model;
}

Shader* SSF::loadShader(std::string vertShaderPath, std::string fragShaderPath) {
    if (shaderCache[vertShaderPath + "|" + fragShaderPath] != nullptr)
        return shaderCache[vertShaderPath + "|" + fragShaderPath];

    Shader* shader = new Shader(vertShaderPath, fragShaderPath);
    shaderCache[vertShaderPath + "|" + fragShaderPath] = shader;
    return shader;
}

}
