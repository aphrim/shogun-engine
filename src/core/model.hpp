#pragma once
#include "include.hpp"
#include "obj.hpp"

namespace SHOGUN {

class Model {
public:
    Model(float* vertV, int vertC);
    Model(std::string filePath);

    void updateModelData(float* vertV, int vertC);

    static int count;
    int Id;

    int getVertC();
    unsigned int getVAO();
    unsigned int getVBO();
private:
    unsigned int VAO, VBO;
    int vertC;
};
}
