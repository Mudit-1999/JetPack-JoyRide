#include "main.h"

#ifndef HEART_H
#define HEART_H


class Heart
{
public:
    Heart() {}
    Heart(double x, double y);
    float start;
    bool valid;
    glm::vec3 position;
    glm::vec3 speed;
    void draw(glm::mat4 VP);
    void tick(double accx,double accy);
    bounding_box_t bounding_box() ;
    void activate();
private:
    VAO* object;
};

#endif // HEART_H
