#include "main.h"

#ifndef SCORE_H
#define SCORE_H

class Score {
public:
    Score() {}
    Score(float x, float y, float cscore, color_t color);
    glm::vec3 position;
    float rotation;
    float radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(double speedr,double speedx);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // SCORE_H
