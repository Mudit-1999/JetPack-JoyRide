#include "powerup.h"
#include "main.h"

Powerup::Powerup(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->speed = glm::vec3(0.5/60,1.0/60, 0);
    this->rotation = 0;
    this->valid=false;
    static const GLfloat vertex_buffer_data[] = 
    {
        0.0f, 0.0f, 0.0f,
        0.2f,0.0f,0.0f,
        0.0f, 0.2f,0.0f,
        0.2f, 0.2f, 0.0f,
        0.2f,0.0f,0.0f,
        0.0f, 0.2f,0.0f,    
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Powerup::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);    
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Powerup::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Powerup::tick(double accx , double accy) {
    this->rotation += 1.5;
    this->speed += glm::vec3(accx,accy,0);
    if(this->speed.y <= -1.0/60.0)
        this->speed.y=1.0/60.0;

    this->position += this->speed;

    if(this->valid== true && this->start + 7.0f < glfwGetTime())
    {
        this->valid=false;
        this->position.y =-1000;
    }
    
}

void Powerup::activate()
{
    if(this->valid == false)
    {
        this->start=glfwGetTime();
        this->valid=true;
    }
    this->position.y =-1000;
    
}

bounding_box_t Powerup::bounding_box() 
{
    float x = this->position.x, y = this->position.y;
    bounding_box_t bd_box = { x+0.1f  , y+0.1f , 0.0f, 0.2f , 0.2f,0.0f};
    return bd_box;
}



