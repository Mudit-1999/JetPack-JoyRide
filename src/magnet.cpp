#include "magnet.h"
#include "main.h"

Magnet::Magnet(float x, float y, float accx) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    
    GLfloat vertex_buffer_north[] = 
    {
        0.10f , 0.10f , 0.0f,
        0.00f , 0.10f , 0.0f,
        0.00f ,-0.10f , 0.0f,
        0.00f ,-0.10f , 0.0f,
        0.10f ,-0.10f , 0.0f,
        0.10f , 0.10f , 0.0f,
    };
    GLfloat vertex_buffer_south[] = 
    {
        -0.10f , 0.10f , 0.0f,
         0.00f , 0.10f , 0.0f,
         0.00f ,-0.10f , 0.0f,
         0.00f ,-0.10f , 0.0f,
        -0.10f ,-0.10f , 0.0f,
        -0.10f , 0.10f , 0.0f,
    };

    this->object_north = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_north, COLOR_RED, GL_FILL);
    this->object_south = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_south, COLOR_MID_NIGTH_BLUE, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_north);
    draw3DObject(this->object_south);
}


void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::tick(double speedx) {
    this->position += glm::vec3(speedx/60.0f,0,0);
}



