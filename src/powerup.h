#include "main.h"

#ifndef POWERUP_H
#define POWERUP_H


class Powerup {
public:
    Powerup() {}
    Powerup(float x, float y, color_t color);
    float start;
    bool valid;
    glm::vec3 position;
    glm::vec3 speed;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(double accx,double accy);
    void activate();
    bounding_box_t bounding_box() ;

private:
    VAO *object;
};

#endif // POWERUP_H
