#include "dushman.h"
#include "main.h"

Dushman::Dushman(float x, float y, float length, float radius,float rotation,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = rotation;
    this->radius=radius;
    this->length=length;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    
    int n=1000;
    GLfloat vertex_buffer_circle1[9*(n)];
    GLfloat vertex_buffer_circle2[9*(n)];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 3; ++j)
		{
			vertex_buffer_circle1[9*i+j]=0.0f;
            if(j%3==0)
			    vertex_buffer_circle1[9*i+j]=length/2+ 0.0f;
		}
		vertex_buffer_circle1 [9*i+3]=length/2 + cos((i*2*3.14)/n)*radius;
		vertex_buffer_circle1[9*i+4]= sin((i*2*3.14)/n)*radius*1.5;
		vertex_buffer_circle1[9*i+5]=0.0f;
	    
        vertex_buffer_circle1[9*i+6]=length/2 + cos((((i+1)%n)*2*3.14)/n)*radius;
		vertex_buffer_circle1[9*i+7]=sin((((i+1)%n)*2*3.14)/n)*radius*1.5;
		vertex_buffer_circle1[9*i+8]= 0.0f;

	}


	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 3; ++j)
		{
			vertex_buffer_circle2[9*i+j]=0.0f;
            if(j==0)
	    		vertex_buffer_circle2[9*i+j]=-length/2+ 0.0f;
		}
		vertex_buffer_circle2[9*i+3]=-length/2 + cos((i*2*3.14)/n)*radius;
		vertex_buffer_circle2[9*i+4]= sin((i*2*3.14)/n)*radius*1.5;
		vertex_buffer_circle2[9*i+5]= 0.0f;
	    
        vertex_buffer_circle2[9*i+6]=-length/2 + cos((((i+1)%n)*2*3.14)/n)*radius;
		vertex_buffer_circle2[9*i+7]= sin((((i+1)%n)*2*3.14)/n)*radius*1.5;
		vertex_buffer_circle2[9*i+8]= 0.0f;

	}
    
    GLfloat vertex_buffer_data_rod[] = {
         length/2 -radius, 0.025 , 0.0f,
         length/2 -radius,-0.025 , 0.0f,
        -length/2 +radius,-0.025 , 0.0f,
        -length/2 +radius,-0.025 , 0.0f,
        -length/2 +radius, 0.025 , 0.0f,
         length/2 -radius, 0.025 , 0.0f,
    };
    

    this->object_circle1 = create3DObject(GL_TRIANGLES, (n)*3, vertex_buffer_circle1, color, GL_FILL);
    this->object_circle2 = create3DObject(GL_TRIANGLES, (n)*3, vertex_buffer_circle2, color, GL_FILL);
    this->object_rod     = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_rod, COLOR_YELLOWISH_ORANGE, GL_FILL);
}

void Dushman::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_circle1);
    draw3DObject(this->object_circle2);
    draw3DObject(this->object_rod);
}



void Dushman::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Dushman::tick(double speedx) {
    // this->rotation += 1; 
    this->position += glm::vec3(speedx/60.0f,0,0);

}

bounding_box_t Dushman::bounding_box() 
{
    float x = this->position.x, y = this->position.y;
    bounding_box_t bd_box = { x , y , 0.0f, 0.05f, this->length, this->rotation};
    return bd_box;
}


