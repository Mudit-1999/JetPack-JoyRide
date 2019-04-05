#include "main.h"

#ifndef PLATFORM_H
#define PLATFORM_H

class Platform 
{
public:
    Platform() {}
    Platform(float x, float y, float height, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(double speed);
private:
    VAO *object;
};

#endif // PLATFORM_H
