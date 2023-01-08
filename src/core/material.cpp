#include "material.hpp"

namespace SHOGUN {

int Material::count = 0;

Material::Material(Texture* albedo, Texture* metallic, Texture* roughness, Texture* normal) :
albedo(albedo), metallic(metallic), roughness(roughness), normal(normal), ao(ao) {
    Id = count++;
}

Material::Material(std::string path, std::string ext) {
    Id = count++;
    if (path.back() != '/') path += '/';
    albedo = new Texture(path + "albedo." + ext, TEXTURE_2D);
    metallic = new Texture(path + "metallic." + ext, TEXTURE_2D);
    normal = new Texture(path + "normal." + ext, TEXTURE_2D);
    roughness = new Texture(path + "roughness." + ext, TEXTURE_2D);
    ao = new Texture(path + "ao." + ext, TEXTURE_2D);
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
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, ao->getId());
}

int Material::getId() { return Id; }
}
