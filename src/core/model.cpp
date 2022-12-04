#include "model.hpp"

namespace SHOGUN {

int Model::count = 0;

Model::Model(float* vertV, int vertC): vertC(vertC) {
    Id = count++;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertC, vertV, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6*sizeof(float)));
    glEnableVertexAttribArray(2);
}

Model::Model(std::string filePath) : path(filePath) {
    Id = count++;

    OBJParser objParser;
    std::vector<float> verts = objParser.parseObj(filePath.c_str());
    float* vertV = &verts[0];
    int vertC = verts.size() * sizeof(float);
    this->vertC = vertC;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertC, vertV, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6*sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Model::updateModelData(float* vertV, int vertC) {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertC, vertV, GL_DYNAMIC_DRAW);
}

int Model::getId() { return Id; }
unsigned int Model::getVAO() { return VAO; }
unsigned int Model::getVBO() { return VBO; }
int Model::getVertC() { return vertC; }
}
