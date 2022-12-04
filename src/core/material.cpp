#include "material.hpp"

namespace SHOGUN {

int Material::count = 0;

Material::Material(Texture* albedo, Texture* metallic, Texture* roughness, Texture* normal) :
albedo(albedo), metallic(metallic), roughness(roughness), normal(normal) {
    Id = count++;
}

Material::Material(std::string path, std::string ext) {
    Id = count++;
    if (path.back() != '/') path += '/';
    albedo = new Texture(path + "albedo." + ext);
    metallic = new Texture(path + "metallic." + ext);
    normal = new Texture(path + "normal." + ext);
    roughness = new Texture(path + "roughness." + ext);
}

void Material::use() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, albedo->getId());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, metallic->getId());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, roughness->getId());
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, normal->getId());
}

int Material::getId() { return Id; }
}
