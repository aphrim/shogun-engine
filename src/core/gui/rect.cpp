#include "rect.hpp"

namespace SHOGUN {

Rect::Rect() {
    float verts[] = {
        -1, 1, 0, 0, //TL
        -1, -1, 0, 1, //BL
        1, -1, 1, 1, //BR
                     //Second Triangle
        -1, 1, 0, 0, //TL
        1, 1, 0, 1, //TR
        1, -1, 1, 1, //BR
    };

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    shader = new Shader("shaders/2dshader.vert", "shaders/2dshader.frag");
}

void Rect::render() {
    std::cout << "Rendering GUI Rect" << std::endl;
    calcTransformMatrix();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    shader->use();

    shader->setMat4("transform", transformMatrix);
    shader->setVec3("color", Vector3(0.5, 0.5, 0.5));

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

}
