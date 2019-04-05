#include "character.h"
#include "main.h"


Character::Character(float x, float y, float radius, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->speedx = this->speedy=0;
    this->rotation = 0;
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
		vertex_buffer_data[9*i+4]=sin((i*2*3.14)/n)*radius*1.5;
		vertex_buffer_data[9*i+5]=0.0f;
	    
        vertex_buffer_data[9*i+6]=cos((((i+1)%n)*2*3.14)/n)*radius;
		vertex_buffer_data[9*i+7]=sin((((i+1)%n)*2*3.14)/n)*radius*1.5;
		vertex_buffer_data[9*i+8]=0.0f;

	}
    
    GLfloat vertex_buffer_data_body[] = {
         0.10f,       -radius*1.5f, 0.0f,
        -0.10f,       -radius*1.5f, 0.0f,
        -0.11f, -0.5f -radius*1.5f, 0.0f,
        -0.10f,       -radius*1.5f, 0.0f,
        -0.11f, -0.5f -radius*1.5f, 0.0f,
         0.11f, -0.5f -radius*1.5f, 0.0f,
    };
    

    GLfloat vertex_buffer_data_leg[] = {
        -0.11f,   -0.5f -radius*1.5f, 0.0f,
         0.0f,    -0.5f -radius*1.5f, 0.0f,
        -0.055f,  -0.7f -radius*1.5f, 0.0f,
         0.11f,   -0.5f -radius*1.5f, 0.0f,
         0.0f,    -0.5f -radius*1.5f, 0.0f,
         0.055f,  -0.7f -radius*1.5f, 0.0f,
    };

    GLfloat vertex_buffer_data_foot[] = {
        -0.055f -0.055/2.0f,    -0.7f -radius*1.5f, 0.0f,
        -0.055/2.0f,  -0.7f -radius*1.5f, 0.0f,
         +0.055f +0.055/2.0f,   -0.7f -radius*1.5f, 0.0f,
         0.055/2.0f,  -0.7f -radius*1.5f, 0.0f,
        //  0.0f,    -0.7f -radius*1.5f, 0.0f,
        // -0.055f,  -0.7f -radius*1.5f, 0.0f,
        //  0.00f,   -0.8f -radius*1.5f, 0.0f,
        // -0.055f,  -0.8f -radius*1.5f, 0.0f,
    };

    GLfloat vertex_buffer_data_jet_off[] = {
        -0.20f,       -radius*1.5f, 0.0f,
        -0.10f,       -radius*1.5f, 0.0f,
        -0.10f, -0.3f -radius*1.5f, 0.0f,
        -0.10f,       -radius*1.5f, 0.0f,
        -0.20f, -0.3f -radius*1.5f, 0.0f,
        -0.10f, -0.3f -radius*1.5f, 0.0f,
    };

    GLfloat vertex_buffer_data_jet_on[] = {
        -0.20f, -0.3f -radius*1.5f, 0.0f,
        -0.10f, -0.3f -radius*1.5f, 0.0f,
        -0.15f, -0.5f -radius*1.5f, 0.0f,
    };

    GLfloat vertex_buffer_data_jet_on1[] = {
        -0.175f, -0.4f -radius*1.5f, 0.0f,
        -0.125f, -0.4f -radius*1.5f, 0.0f,
        -0.15f, -0.5f -radius*1.5f, 0.0f,
    };



    this->object = create3DObject(GL_TRIANGLES, (n)*3, vertex_buffer_data, COLOR_FACE, GL_FILL);
    this->object_body = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_body, color, GL_FILL);
    this->object_leg = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_leg, COLOR_BLACK, GL_FILL);
    this->object_foot = create3DObject(GL_LINES, 4, vertex_buffer_data_foot, COLOR_RED, GL_FILL);
    this->object_jet_off=create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_jet_off, COLOR_JET_PACK, GL_FILL);
    this->object_jet_on=create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data_jet_on, COLOR_YELLOW, GL_FILL);
    this->object_jet_on1=create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data_jet_on1, COLOR_YELLOWISH_ORANGE, GL_FILL);
}

void Character::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object_body);
    draw3DObject(this->object_leg);
    draw3DObject(this->object_foot);
    draw3DObject(this->object_jet_off);
}

void Character::draw_on(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object_body);
    draw3DObject(this->object_leg);
    draw3DObject(this->object_foot);
    draw3DObject(this->object_jet_off);
    draw3DObject(this->object_jet_on);
    draw3DObject(this->object_jet_on1);
}

void Character::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Character::tick(double accx, double accy) {
    // this->rotation += speed;
    double  time = 1.0/60;
    // accx= accx +this->speed.x >=0? -1:1 * this->speed.x*this->speed.x;
        if(this->speedx >= 1*stage_multiplier  && accx>0)
        {
            this->speedx=1*stage_multiplier;
        }
        else if( this->speedx <= -1*stage_multiplier && accx < 0)
        {
            this->speedx=-1*stage_multiplier;
        }
        else
        {
            this->speedx+= accx*time;
        }
        if(this->speedy >= 5*stage_multiplier  && accy>0)
        {
            this->speedy=5*stage_multiplier;
        }
        else if (accy>0 && this->speedy < -1*stage_multiplier )
        {
            this->speedy=-1*stage_multiplier;
            this->speedy+= accy*time;
        }
        else
        {
            this->speedy+= accy*time;
        }
        this->position += glm::vec3(time*this->speedx,time*this->speedy,0);
        if(this->position.y<=-2.24)
        {
            this->position.y=-2.24;
            this->speedy=0;
        }
        if(this->position.x < -( 3.8/screen_zoom) )
        {
            this->position.x=-3.8/screen_zoom;
            this->speedx=0;
        }
        if(this->position.y > (3.8/screen_zoom) )
        {
            this->position.y=3.8/screen_zoom;
            this->speedy=0;
        }

}   

bounding_box_t Character::bounding_box() 
{
    float x = this->position.x, y = this->position.y;
    bounding_box_t bd_box = { x , y -0.35f, 0.0f, 0.2f, 1.0f,0};
    return bd_box;
}


