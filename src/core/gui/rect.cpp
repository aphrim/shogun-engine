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
    Vector3 adjustedPosition = Vector3(toGLPosition(Vector2(worldPosition.x, worldPosition.y), Vector2(worldScale.x, worldScale.y)), 0);
    Vector3 adjustedScale = Vector3(1 / window->size.x, 1 / window->size.y, 0.1);
    updateTransformMatrix(adjustedPosition, Vector3(0, 0, worldRotation.x), worldScale, adjustedScale);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    shader->use();

    shader->setMat4("transform", transformMatrix);
    shader->setVec3("color", color);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Rect::setColor(Vector3 c) {
    color = c;
}

Vector3 Rect::getColor() {
    return color;
}

bool Rect::collides(Vector2 pos) {
    Vector2 wP = toCenterDock(Vector2(worldPosition.x, worldPosition.y), Vector2(worldScale.x, worldScale.y));
    
    
    float angle = worldRotation.x * 3.14 / 180;
    Vector2 os = pos - wP;
    Vector2 ros = Vector2(cos(angle) * os.x - sin(angle) * os.y, sin(angle) * os.x + cos(angle) * os.y);
    Vector2 rpos = ros + wP;

    Vector2 tr = Vector2(worldScale.x, -worldScale.y) / 2 + wP, bl = Vector2(-worldScale.x, worldScale.y) / 2 + wP;
    std::cout << tr << " " << bl << std::endl;

    return (rpos.x >= bl.x && rpos.x <= tr.x) && (rpos.y >= tr.y && rpos.y <= bl.y);
}

}
