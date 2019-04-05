#include "main.h"

#ifndef DUSHMAN_H
#define DUSHMAN_H


class Dushman {
public:
    Dushman() {}
    Dushman(float x, float y, float length, float radius,float roation,color_t color);
    glm::vec3 position;
    float rotation,length,radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(double speedx);
    bounding_box_t bounding_box();
    // double speed;
private:
    VAO *object_circle1,*object_circle2,*object_rod;
};

#endif // DUSHMAN_H
