#pragma once
#include "include.hpp"

namespace SHOGUN {
class Texture {
public:
    Texture(const char* texturePath);
    Texture(int width, int height);

    unsigned int getId();
    void use();
private:
    unsigned int ID;
};
}
