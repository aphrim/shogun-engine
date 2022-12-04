#pragma once
#include "include.hpp"

namespace SHOGUN {
class Texture {
public:
    Texture(std::string texturePath);
    Texture(int width, int height);

    unsigned int getId();
    
    std::string path;
private:
    unsigned int ID;
};
}
