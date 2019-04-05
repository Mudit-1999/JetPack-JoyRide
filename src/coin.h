#include "main.h"

#ifndef COIN_H
#define COIN_H


class Coin {
public:
    Coin() {}
    Coin(float x, float y, float height,float mult,color_t color);
    glm::vec3 position;
    float rotation,mult;
    float radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(double speedr,double speedx);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // COIN_H
