#include "balloon.h"
#include "main.h"

Balloon::Balloon(float x, float y, float radius,bool eny,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius=radius;
    this->eny=eny;
    // speed = 0.05;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int n=1000;
    GLfloat vertex_buffer_data[9*(n)];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 3; ++j)
		{
			vertex_buffer_data[9*i+j]=0.0f;
		}
		vertex_buffer_data[9*i+3]=cos((i*2*3.14)/n)*radius;
		vertex_buffer_data[9*i+4]=sin((i*2*3.14)/n)*radius*1.7;
		vertex_buffer_data[9*i+5]=0.0f;
	    
        vertex_buffer_data[9*i+6]=cos((((i+1)%n)*2*3.14)/n)*radius;
		vertex_buffer_data[9*i+7]=sin((((i+1)%n)*2*3.14)/n)*radius*1.7;
		vertex_buffer_data[9*i+8]=0.0f;

	}

    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
}

void Balloon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Balloon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Balloon::tick(double speedx) {
    
    this->position += glm::vec3(speedx/60.0f,-2/60.0f,0);
}

bounding_box_t Balloon::bounding_box() 
{
    float x = this->position.x, y = this->position.y;
    bounding_box_t bd_box = { x , y, 0.0f, 2.0f*this->radius, 2*this->radius*1.7f ,0.0f};
    return bd_box;
}

