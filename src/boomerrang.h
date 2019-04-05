#include "main.h"

#ifndef BOOMERANG_H
#define BOOMERANG_H


class Boomerang {
public:
    Boomerang() {}
    Boomerang(float x, float y, float speedx, float speedy,float accx,float accy,color_t color);
    double accx,accy,rotation;
    glm::vec3 position,speed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
    // double speed;
private:
    VAO *object;
};

#endif // BOOMERANG_H
