#pragma once
#include "include.hpp"

namespace SHOGUN {

typedef enum {
    TEXTURE_2D, TEXTURE_HDR, 
} TextureType;

class Texture {
public:
    Texture(std::string texturePath, TextureType type);
    Texture(int width, int height);

    unsigned int getId();
    
    std::string path;
private:
    unsigned int ID;
};
}
