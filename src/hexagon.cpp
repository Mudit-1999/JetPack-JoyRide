#include "hexagon.h"
#include "main.h"

Hexagon::Hexagon(glm::vec3 position)
{
    this->position = position;
    static const GLfloat vertex_buffer_data [] = {
        0    , 0, 0,
        0.5*1, 0, 0,
        0.5*cos(M_PI/3)  ,0.5* sin(M_PI/3), 0,
        0.5*cos(2*M_PI/3),0.5* sin(2*M_PI/3), 0,
        0.5*cos(3*M_PI/3),0.5* sin(3*M_PI/3), 0,
        0.5*cos(4*M_PI/3),0.5* sin(4*M_PI/3), 0,
        0.5*cos(5*M_PI/3),0.5* sin(5*M_PI/3), 0,
        0.5*1, 0, 0,
    };

    static const GLfloat colour_buffer_data [] = {
        1,1,1,
        0.4*0.95,0.95,0.95,
        0.4*0.97,0.97,0.95,
        0.4*0.97,0.95,0.97,
        0.4*0.95,0.97,0.97,
        0.4*0.97,1,0.97,
        0.4*1,0.97,0.97,
        0.4*0.97,1,0.97
    };

    this->object = create3DObject(GL_TRIANGLE_FAN, 8, vertex_buffer_data, colour_buffer_data, GL_FILL);
}

void Hexagon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    Matrices.model *=  glm::translate(position);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
