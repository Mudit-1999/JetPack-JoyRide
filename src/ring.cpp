#include "ring.h"
#include "main.h"

Ring::Ring(float x, float y,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = -60;
    this->radius=2.5;
    // speed = 0.05;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int n=1002;
    GLfloat vertex_buffer_data[9*(n/3)];

	for (int i = 0; i < n/3; i++)
	{
		vertex_buffer_data[6*i+0]=cos((i*2*3.14)/n)*radius;
		vertex_buffer_data[6*i+1]=sin((i*2*3.14)/n)*radius;
		vertex_buffer_data[6*i+2]=0.0f;
	    
        vertex_buffer_data[6*i+3]=cos((((i+1)%n)*2*3.14)/n)*radius;
		vertex_buffer_data[6*i+4]=sin((((i+1)%n)*2*3.14)/n)*radius;
		vertex_buffer_data[6*i+5]=0.0f;

	}

    GLfloat vertex_buffer_data2[9*(n/3)];

	for (int i = 0; i < n/3; i++)
	{
		vertex_buffer_data2[6*i+0]=cos((i*2*3.14)/n)*(radius-0.5);
		vertex_buffer_data2[6*i+1]=sin((i*2*3.14)/n)*(radius-0.5);
		vertex_buffer_data2[6*i+2]=0.0f;
	    
        vertex_buffer_data2[6*i+3]=cos((((i+1)%n)*2*3.14)/n)*(radius-0.5);
		vertex_buffer_data2[6*i+4]=sin((((i+1)%n)*2*3.14)/n)*(radius-0.5);
		vertex_buffer_data2[6*i+5]=0.0f;

	}

    this->object = create3DObject(GL_LINES, (2*n)/3, vertex_buffer_data, color, GL_FILL);
    this->object2 = create3DObject(GL_LINES, (2*n)/3, vertex_buffer_data2, color, GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
}

void Ring::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ring::tick(double speedr,double speedx) {
    
    this->rotation += speedr;
    this->position += glm::vec3(speedx/60.0f,0,0);
}

bounding_box_t Ring::bounding_box() 
{
    float x = this->position.x, y = this->position.y;
    bounding_box_t bd_box = { x + 2.25f/2.0f , y - 2.25f*0.866f , 0.0f, 0.5f, 0.5f ,0.0f};
    return bd_box;
}

