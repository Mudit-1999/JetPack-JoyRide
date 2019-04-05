#include "main.h"

#ifndef MDUSHMAN_H
#define MDUSHMAN_H


class Mdushman {
public:
    Mdushman() {}
    Mdushman(float x, float y, float length, float radius,float u_limit ,float l_limit, color_t color );
    glm::vec3 position;
    float rotation,length,radius,u_limit,l_limit,flag;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(double speedx,double speedy);
    bounding_box_t bounding_box();
    // double speed;
private:
    VAO *object_circle1,*object_circle2,*object_rod;
};

#endif // MDUSHMAN_H
