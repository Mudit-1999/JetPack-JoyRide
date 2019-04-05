#include "sevensegment.h"
#include "main.h"

Sevensegment::Sevensegment(float x, float y, char c,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation=0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    bool led[8];
    for(size_t i = 0; i < 8; i++)
        led[i] = false;
    switch (c) 
    {
        case '0':
            led[1] = led[2] = led[3] = led[4] = led[5] = led[6] = true;
            break;
        case '1':
            led[2] = led[3] = true;
            break;
        case '2':
            led[1] = led[2] = led[7] = led[5] = led[4] = true;
            break;
        case '3':
            led[1] = led[2] = led[7] = led[3] = led[4] = true;
            break;
        case '4':
            led[6] = led[7] = led[2] = led[3] = true;
            break;
        case '5':
            led[1] = led[6] = led[7] = led[3] = led[4] = true;
            break;
        case '6':
            led[1] = led[6] = led[7] = led[3] = led[4] = led[5] = true;
            break;
        case '7':
            led[1] = led[2] = led[3] = true;
            break;
        case '8':
            led[1] = led[2] = led[7] = led[5] = led[4] = led[3] = led[6] = true;
            break;
        case '9':
            led[1] = led[2] = led[7] = led[4] = led[3] = led[6] = true;
            break;
        case '-':
            led[7] = true;
    }
    const GLfloat vertex_buffer[6] =
    {
        0.0, 0.0, 0, 
        0.0, 0.0, 0,
    }; 
    const GLfloat vertex_buffer_led[][6] = 
    {
        {-0.10/2, 0.21/2, 0, 0.10/2, 0.21/2, 0},
        { 0.11/2, 0.21/2, 0, 0.11/2, 0.01/2, 0},
        { 0.11/2, 0.00/2, 0, 0.11/2,-0.20/2, 0},
        {-0.10/2,-0.21/2, 0, 0.10/2,-0.21/2, 0},
        {-0.11/2, 0.00/2, 0,-0.11/2,-0.20/2, 0},
        {-0.11/2, 0.21/2, 0,-0.11/2, 0.01/2, 0},
        { 0.10/2, 0.00/2, 0,-0.10/2, 0.00/2, 0},
    };
    
    for(size_t i = 0; i < 7; i++)
    {
        if (led[i+1]==false)
            this->object_line[i] = create3DObject(GL_LINES, 2, vertex_buffer, color, GL_FILL);
        else
            this->object_line[i] = create3DObject(GL_LINES, 2, vertex_buffer_led[i], color, GL_FILL);
    }
}

void Sevensegment::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(size_t i = 0; i < 7; i++)
       draw3DObject(this->object_line[i]);
    
}

void Sevensegment::set_position(float x, float y) 
{
    this->position = glm::vec3(x, y, 0);
}


