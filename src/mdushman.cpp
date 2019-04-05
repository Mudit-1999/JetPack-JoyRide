#include "mdushman.h"
#include "main.h"

Mdushman::Mdushman(float x, float y, float length, float radius , float u_limit, float l_limit ,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->radius=radius;
    this->length=length;
    this->rotation=0;
    this->flag=1; 
    this->u_limit=u_limit;
    this->l_limit=l_limit;

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
		vertex_buffer_circle1[9*i+3]=length/2 + cos((i*2*3.14)/n)*radius;
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
         length/2 , 0.05 , 0.0f,
         length/2 ,-0.05 , 0.0f,
        -length/2 ,-0.05 , 0.0f,
        -length/2 ,-0.05 , 0.0f,
        -length/2 , 0.05 , 0.0f,
         length/2 , 0.05 , 0.0f,
    };
    

    this->object_circle1 = create3DObject(GL_TRIANGLES, (n)*3, vertex_buffer_circle1, color, GL_FILL);
    this->object_circle2 = create3DObject(GL_TRIANGLES, (n)*3, vertex_buffer_circle2, color, GL_FILL);
    this->object_rod     = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_rod, COLOR_YELLOWISH_ORANGE, GL_FILL);
}

void Mdushman::draw(glm::mat4 VP) {
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



void Mdushman::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Mdushman::tick(double speedx,double speedy) 
{
    // this->rotation += 1;
    // double  time = 1.0/60;
    if(this->position.y > this->u_limit && this->flag==1)
        this->flag=-1;
    else if(this->position.y < this->l_limit && this->flag==-1)
        this->flag=1;
    this->position += glm::vec3(speedx/60.0f,this->flag*speedy/60.0f,0);
    
}

bounding_box_t Mdushman::bounding_box() 
{
    float x = this->position.x, y = this->position.y;
    bounding_box_t bd_box = { x , y , 0.0f, this->length, 0.10f, this->rotation};
    return bd_box;
}


