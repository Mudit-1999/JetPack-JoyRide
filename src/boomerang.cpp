#include "boomerrang.h"
#include "main.h"

Boomerang::Boomerang(float x, float y, float speedx, float speedy, float accx,float accy,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->speed=glm::vec3(speedx,speedy,0);
    this->accx=accx;
    this->accy=accy;
    this->rotation=0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    
    GLfloat vertex_buffer_data[] = 
    {
         0.05f , 0.05f , 0.0f,
        -0.05f , 0.05f , 0.0f,
        -0.05f , 0.05f , 0.0f,
        -0.05f ,-0.05f , 0.0f,
        -0.05f ,-0.05f , 0.0f,
         0.05f ,-0.05f , 0.0f,
    };

    this->object     = create3DObject(GL_LINES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
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



void Boomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boomerang::tick() 
{
    this->rotation += 2;
    this->speed +=glm::vec3(accx/60.0f,accy/60.0f,0) ;
    if(this->speed.x >= 1.0/10)
        this->speed.x =1.0/10;
    this->position += this->speed;
}

bounding_box_t Boomerang::bounding_box() 
{
    float x = this->position.x, y = this->position.y;
    bounding_box_t bd_box = { x , y , 0.0f, 0.10f,0.10f ,0};
    return bd_box;
}


