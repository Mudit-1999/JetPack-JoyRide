#include "main.h"

#ifndef RING_H
#define RING_H


class Ring {
public:
    Ring() {}
    Ring(float x, float y,color_t color);
    glm::vec3 position;
    float rotation,radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(double speedr,double speedx);
    bounding_box_t bounding_box();
private:
    VAO *object, *object2;
};

#endif // RING_H
