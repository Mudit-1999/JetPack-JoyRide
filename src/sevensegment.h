#include "main.h"

#ifndef SEVENSEGMENT_H
#define SEVENSEGMENT_H


class Sevensegment {
public:
    Sevensegment() {}
    Sevensegment(float x, float y, char d, color_t color);
    float rotation;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();

private:
    VAO *object_line[7];

};

#endif // SEVENSEGMENT_H
