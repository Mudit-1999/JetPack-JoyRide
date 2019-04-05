#include "heart.h"
#include "main.h"

Heart::Heart(double x, double y) {
    this->position = glm::vec3(x, y, 0);
    this->speed = glm::vec3(0.5/60,2.0/60, 0);
    static const GLfloat vertex_buffer_data [] = {
         0.00f, 0.05f, 0.0f,
         0.05f, 0.10f, 0.0f,
         0.10f, 0.05f, 0.0f,
         0.00f,-0.05f, 0.0f,
        -0.10f, 0.05f, 0.0f,
        -0.05f, 0.10f, 0.0f,
    };
    this->object = create3DObject(GL_LINE_LOOP, 6, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Heart::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    Matrices.model *=  glm::translate(position);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Heart::tick(double accx,double accy) {
    this->speed += glm::vec3(accx,accy,0);
    if(this->speed.y <= -2.0/60.0)
        this->speed.y=2.0/60.0;

    this->position += this->speed;

    if(this->valid== true && this->start + 7.0f < glfwGetTime())
    {
        this->valid=false;
        this->position.y =-1000;
    }

}

void Heart::activate()
{
    if(this->valid == false)
    {
        this->start=glfwGetTime();
        this->valid=true;
    }
    this->position.y =-1000;

    
}

bounding_box_t Heart::bounding_box() 
{
    float x = this->position.x, y = this->position.y;
    bounding_box_t bd_box = { x  , y, 0.0f, 0.1f , 0.1f,0.0f};
    return bd_box;
}

