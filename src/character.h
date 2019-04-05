#include "main.h"

#ifndef CHARACTER_H
#define CHARACTER_H

class Character 
{
public:
    Character() {}
    Character(float x, float y, float height, color_t color);
    glm::vec3 position;
    double speedx,speedy;
    float rotation;
    void draw(glm::mat4 VP);
    void draw_on(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(double accx, double accy);
    bounding_box_t bounding_box();
private:
    VAO *object,*object_body, *object_leg;
    VAO *object_foot,*object_jet_off,*object_jet_on;
    VAO *object_jet_on1;
};

#endif // CHARACTER_H


