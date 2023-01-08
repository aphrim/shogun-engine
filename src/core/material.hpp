#pragma once
#include "include.hpp"
#include "texture.hpp"

namespace SHOGUN {
class Material {
public:
    Material(Texture* albedo, Texture* metallic, Texture* roughness, Texture* normal);
    Material(std::string materialPath, std::string ext); //If albedo.[ext], metallic.[ext], normal.[ext] and roughness.[ext] in folder, will auto load them.


    int getId();
    void use();
    static int count;

    Texture* albedo;
    Texture* metallic;
    Texture* roughness;
    Texture* normal;
    Texture* ao;

private:
    int Id;
};
}
