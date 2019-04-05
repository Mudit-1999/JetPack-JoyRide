#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet{
public:
    Magnet() {}
    Magnet(float x, float y, float accx);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(double speedx);
private:
    VAO *object_north,*object_south;
};

#endif // MAGNET_H
