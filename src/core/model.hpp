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

    int getId();
    int getVertC();
    unsigned int getVAO();
    unsigned int getVBO();

    std::string path;
private:
    unsigned int VAO, VBO;
    int vertC;
    int Id;
};
}
