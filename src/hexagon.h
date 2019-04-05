#ifndef HEXAGON_H
#define HEXAGON_H

#include "main.h"

class Hexagon
{
public:
    Hexagon() {}
    Hexagon(glm::vec3 position);
    void draw(glm::mat4 VP);
private:
    VAO* object;
    glm::vec3 position;
};

#endif // HEXAGON_H
