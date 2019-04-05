#include "main.h"

#ifndef BALLOON_H
#define BALLOON_H


class Balloon {
public:
    Balloon() {}
    Balloon(float x, float y, float height,bool eny,color_t color);
    glm::vec3 position;
    float rotation,mult;
    float radius;
    bool eny;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(double speedx);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALLOON_H
