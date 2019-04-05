#include "main.h"
#include "timer.h"
#include "ball.h"
#include "heart.h"
#include "platform.h"
#include "character.h"
#include "coin.h"
#include "dushman.h"
#include "mdushman.h"
#include "boomerrang.h"
#include "magnet.h"
#include "sevensegment.h"
#include "ring.h"
#include "balloon.h"
#include "powerup.h"
#include "hexagon.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
int flag_jet_on, flag_ball=1;
double gold_coin_pdis=1.50,acc_mag=0;
int points_multplier=2;
int Final_Score=0;
int deduct_score=1;
float start_time=glfwGetTime();
bool circle=false;

/**************************
* Customizable functions *
**************************/

vector<Heart> heart1;
Platform platform_below,platform_below2;
Character hero;
vector<Dushman> enemy_one;
vector<Mdushman> enemy_two;
vector<Coin> gold_coin; 
vector<Boomerang> enemy_three;
Magnet magnet_pole;
vector<Sevensegment> digit;
Ring s_ring;
vector<Balloon> water_ball;
vector<Powerup> twox_s;
vector<Hexagon> dragon;
float ring_angle=-60;
int sign_multi =1;


int level=1;
float stage_multiplier=1.0f;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;  //  for panning ( i think so ) 
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);


void square_coin(float x,float y)
{
    int num=rand()%4;
    for(int i = 0; i < 5; i++)
      for(int j = 0; j < 4; j++)
      {
        if(num==1)
            gold_coin.push_back(Coin(x+i*2*0.09 ,y+2*0.09*j,0.05,1,COLOR_DEEP_PINK));
        else if(num==2)
            gold_coin.push_back(Coin(x+i*2*0.09 ,y+2*0.09*j,0.05,3,COLOR_GOLD));
        else
            gold_coin.push_back(Coin(x+i*2*0.09 ,y+2*0.09*j,0.05,2,COLOR_GREEN_YELLOW));
      }
        
}

void triangle_coin(float x,float y)
{
	int j=0,flag=1;
	for(int i = 0; i < 15; i++)
	{
      gold_coin.push_back(Coin(x+j*1*0.07 ,y+3*0.07*i,0.05,1,COLOR_GOLD));
		if(j>=7)
			flag=-1;
		j+=flag;
	}
}

bool slant_collision(bounding_box_t bd_box,float x, float y, float angle, float offset)
{
	float d_product1,d_product2[10],cosine,sine;
    float maxi,mini;
	cosine=cos(angle * M_PI / 180.0f);
	sine=sin(angle * M_PI / 180.0f);
	d_product1=cosine*x+sine*y;
	d_product2[0] = (bd_box.x + (bd_box.width/2)) * cosine + (bd_box.y + (bd_box.height/2) )* sine;
	d_product2[1] = (bd_box.x + (bd_box.width/2)) * cosine + (bd_box.y - (bd_box.height/2) )* sine;
	d_product2[2] = (bd_box.x - (bd_box.width/2)) * cosine + (bd_box.y + (bd_box.height/2) )* sine;
	d_product2[3] = (bd_box.x - (bd_box.width/2)) * cosine + (bd_box.y - (bd_box.height/2) )* sine;
    
    mini=d_product2[0];
	maxi=d_product2[0];
	
    for(int i=1;i<4;i++)
	{
        maxi=max(maxi,d_product2[i]);
        mini=min(mini,d_product2[i]);
	}
	
    if( maxi >= (d_product1-offset) && mini<=(d_product1+offset) )
		return true;    
    else
	    return false;
}

void display(string s)
{
    digit.clear();
    for(int i = s.length()-1; i>=0 ; i--)
       digit.push_back( Sevensegment((3.9/screen_zoom) -((s.length()- i -1)*0.15),3.8/screen_zoom,s[i],COLOR_BLACK));
    string stage=to_string(level);
    for(int i = stage.length()-1; i>=0 ; i--)
    {
       digit.push_back( Sevensegment(3.85/screen_zoom-((stage.length()- i -1)*0.15),-3.8/max(screen_zoom,1.0f),stage[i],COLOR_WHITE));
    }
}

void check_mag()
{
    if(abs(hero.position.x-magnet_pole.position.x) <=2.5 && abs(hero.position.y -magnet_pole.position.y) <=1 )
    {
        if(hero.position.x <magnet_pole.position.x)
            acc_mag=100;
        else
            acc_mag=-100;
    }
    else
        acc_mag=0;
}



void check_collision_overall()
{
    int count=0,count_h=0;
    for (auto it =twox_s.begin(); it != twox_s.end(); it++) 
    {
        bounding_box_t a=(*it).bounding_box(),b=hero.bounding_box();
        if (detect_collision(a,b) )
        {
            (*it).activate();
        }
        if((*it).valid)
            count++;
    }
    if(count>0)
        points_multplier=3;
    else
        points_multplier=1.5;
    
    for (auto it =heart1.begin(); it != heart1.end(); it++) 
    {
        bounding_box_t a=(*it).bounding_box(),b=hero.bounding_box();
        if (detect_collision(a,b) )
        {
            (*it).activate();
        }
        if((*it).valid)
            count_h++;
    }
    if(count_h>0)
        deduct_score=0;
    else
        deduct_score=1;
        
    for (auto it = gold_coin.begin(); it != gold_coin.end(); it++) 
    {
        if((*it).position.x < -4)
        {
            gold_coin.erase(it);
            it--;
            continue;
        }
        bounding_box_t a=(*it).bounding_box(),b=hero.bounding_box();
        if (detect_collision(a,b) )
        {
            Final_Score+= (((*it).mult )*points_multplier);
            gold_coin.erase(it);
            it--;
        }
    }

    for (auto it = enemy_three.begin(); it != enemy_three.end(); it++) 
    {
        if( (*it).position.y > 4 || (*it).position.y < -3.0 ) 
        {
            enemy_three.erase(it);
            it--;
            continue;
        }
        bounding_box_t a=(*it).bounding_box(),b=hero.bounding_box();
        if (detect_collision(a,b) )
        {
            Final_Score-=(1*deduct_score);
            enemy_three.erase(it);
            it--;
        }
    }
        
    for (auto it = enemy_two.begin(); it != enemy_two.end(); it++) 
    {
        if( (*it).position.x < -4) 
        {
            enemy_two.erase(it);
            it--;
            continue;
        }
        bounding_box_t a=(*it).bounding_box(),b=hero.bounding_box();
        if (detect_collision(a,b) )
            Final_Score-=(2*deduct_score);
    }
    for (auto it = enemy_one.begin(); it != enemy_one.end(); it++) 
    {
        if( (*it).position.x < -4) 
        {
            enemy_one.erase(it);
            it--;
            continue;
        }
        bounding_box_t b=hero.bounding_box();
        if (slant_collision(b,(*it).position.x,(*it).position.y, (*it).rotation, (*it).length/2) )
        {
            if (slant_collision(b,(*it).position.x,(*it).position.y, (*it).rotation+90, 0.05/2) )
                Final_Score-=(6*deduct_score);
        }
    }
    for (auto it2 = enemy_one.begin(); it2 != enemy_one.end(); it2++)
    {
        
        for (auto it = water_ball.begin(); it != water_ball.end(); it++)
        {
            if( (*it).position.y < -2.8) 
            {
                water_ball.erase(it);
                it--;
                continue;
            } 
            if((*it).eny==true)
                continue;
            bounding_box_t a=(*it).bounding_box();
            if (slant_collision(a,(*it2).position.x,(*it2).position.y, (*it2).rotation, (*it2).length/2) )
            {
                if (slant_collision(a,(*it2).position.x,(*it2).position.y, (*it2).rotation+90, 0.05/2) )
                {
                    enemy_one.erase(it2);
                    water_ball.erase(it);
                    it--;
                    it2--;
                    break;
                }
            }   
        } 
    }
    for (auto it = water_ball.begin(); it != water_ball.end(); it++)
    {
        if((*it).eny==true)
        {
            bounding_box_t a=(*it).bounding_box(), b=hero.bounding_box();
            if(detect_collision(a,b))
            {
                Final_Score-=(2*deduct_score);
                water_ball.erase(it);
                it--;
            }

        }
    }
    
}


/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 0,0,1 );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);
    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane
    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model
    // Scene render
    
    platform_below.draw(VP);
    platform_below2.draw(VP);

    magnet_pole.draw(VP);
    s_ring.draw(VP);
    for(auto&& i : gold_coin)
        i.draw(VP);
    if(flag_jet_on)
        hero.draw_on(VP);
    else
        hero.draw(VP);
    for(auto&& i : twox_s)
        i.draw(VP);
    for(auto&& i : heart1)
        i.draw(VP);
    for(auto&& i : water_ball)
        i.draw(VP);
    for(auto&& i : enemy_one)
        i.draw(VP);
    for(auto&& i : enemy_two)
        i.draw(VP);
    for(auto&& i : enemy_three)
       i.draw(VP);
    for(auto&& i : digit)  
        i.draw(VP);
    for(auto&& i : dragon)
    {
        i.draw(VP);
    }
    
}

void tick_input(GLFWwindow *window) 
{
	int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int left = glfwGetKey(window, GLFW_KEY_LEFT);
    int fire = glfwGetKey(window, GLFW_KEY_B);
    flag_jet_on=space;
    
    if(fire)
    {
        if(flag_ball==1)
        {
            water_ball.push_back(Balloon(hero.position.x + 0.12, hero.position.y,0.05,false,COLOR_MID_NIGTH_BLUE));
            flag_ball=-4;
        }
        flag_ball++;
    }

    
    if(start_time + 7.0f < glfwGetTime())
    {
        water_ball.push_back(Balloon(3 - 0.12, 3,0.05,true,COLOR_YELLOWISH_ORANGE));
        start_time=glfwGetTime();
    }
    

    for(auto&& i : enemy_three)
        i.tick();
    for(auto&& i : water_ball)
    {
        if(i.eny==false)
        i.tick(4);
        else
        i.tick(-4);
        
    }
    for(auto&& i : twox_s)
    {
        i.tick(0,-0.1/60);
        // cout << i.speed.y << endl;
    } 
    for(auto&& i : heart1)
    {
        i.tick(0,-0.09/60);
        // cout << i.speed.y <<" " << endl;
    } 
    if(circle==true)
    {
        if(ring_angle < 80)
        {
            hero.speedx=0;
            hero.speedy=0;
            hero.position.x= s_ring.position.x+ 2.0* cos(ring_angle * M_PI / 180.0f);
            hero.position.y= s_ring.position.y+ 2.0* sin(ring_angle * M_PI / 180.0f);
            ring_angle+=2;
            deduct_score=0;
        }
        else
        {
            ring_angle =-60;
            circle=false;
            hero.speedx=0.10;
            hero.speedy=2;
            hero.tick(-10000,0);
            deduct_score=1;
        }
    }
    else
    {
    
    
        if(hero.position.x < 1.0)
        {
            for(auto&& i : gold_coin)
                i.tick(1.5*stage_multiplier,0);
            for(auto&& i : enemy_two)
                i.tick(0,1*stage_multiplier);
            if(max(right,left))
                hero.tick( ((right==1?1:-1)*5.0)+ acc_mag , space==1?6:-1*9.8);
            else
            {
                if(int( 10* hero.speedx)<=2)
                {
                    hero.speedx=0;
                    hero.tick(0 + acc_mag, space==1?6:-1*9.8);
                }
                else
                    hero.tick( ( (hero.speedx>0?-1:1) * 15.0) +acc_mag , space==1?6:-1*9.8);
            }

        }
        else
        {
            hero.speedx=0;
            if(left)
            {
                hero.tick( -5.0 + acc_mag, space==1?6:-1*9.8);
                for(auto&& i : enemy_two)
                    i.tick(0,1*stage_multiplier);
                for(auto&& i : gold_coin)
                    i.tick(1.5*stage_multiplier,0);
            }
            else if(right)
            {

                gold_coin_pdis-=1.0/60.0;
                if(gold_coin_pdis < .01)
                {
                    srand(time(0));
                    int rnumber=rand();
                    int snumber=rnumber%15;
                    if(snumber < 5) 
                    {
                        double y=rand()%20;
                        square_coin(4,y/10.0f);
                    }
                    else if(snumber < 10)
                    {
                        double y=rand()%10;
                        triangle_coin(4,-y/10.0);
                    }
                    else if(snumber<13)
                    {
                        double y=rand()%10;
                        double angle=rand()%360;
                        enemy_one.push_back(Dushman(5,y/10.0,2,0.03,angle,COLOR_DARK_GREY));
                    }
                    else
                    {
                        double y=(rand()%10)/10;
                        double u=(rand()%15)/10.0;
                        double l=(rand()%15)/10.0;
                        enemy_two.push_back(Mdushman(5,  y  ,2,0.04,u,-l,COLOR_BLACK));    
                        enemy_two.push_back(Mdushman(5,y+0.2,2,0.04,u,-l,COLOR_BLACK));    
                    }
                    rnumber=(rnumber+1202039)%17;  
                    double y=(rand()%14)/10;
                    if(rnumber < 4 && magnet_pole.position.x < -4)
                    {
                        magnet_pole = Magnet(-1,-1.5,10);
                    }
                    else if(rnumber < 8 && s_ring.position.x < -4)
                    {
                        s_ring=Ring(0,0,COLOR_BLACK);
                    }
                    else if( rnumber >= 8 && rnumber < 11)
                    {
                        twox_s.push_back(Powerup(-1,y*sign_multi,COLOR_GREEN));
                        sign_multi*=-1;

                    }
                    else if (rnumber >= 11 && rnumber < 14)
                    {
                        heart1.push_back(Heart(-1,y*sign_multi));
                        sign_multi*=-1;
                    }
                    else
                    {
                        enemy_three.push_back(Boomerang(3,3,-6.0/60,-1.4/60.0,0.05,0,COLOR_BOOM));  
                    }
                    
                    gold_coin_pdis=3;
                }
                for(auto&& i : gold_coin)
                    i.tick(1.5*stage_multiplier,-1*stage_multiplier);
                for(auto&& i : enemy_one)
                    i.tick(-1*stage_multiplier);
                for(auto&& i : enemy_two)
                    i.tick(-1*stage_multiplier,1*stage_multiplier);
                magnet_pole.tick(-1*stage_multiplier);
                s_ring.tick(0,-1*stage_multiplier);
                hero.tick(0+acc_mag,space==1?6:-1*9.8);
            }   
            else
            {
                for(auto&& i : gold_coin)
                    i.tick(1.5*stage_multiplier,0);
                for(auto&& i : enemy_two)
                    i.tick(0,1*stage_multiplier);
                hero.tick(0+acc_mag,space==1?6:-1*9.8);
            }
        }
    }
}

void tick_elements() 
{
   
    // camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    heart1.push_back(Heart(-1,1));
    platform_below  = Platform(-7,-4,0.9,COLOR_BLACK);
    platform_below2 = Platform(-7,-3.5,0.25,COLOR_GREY);
    hero            = Character(0,0,0.10,COLOR_GREEN);
    triangle_coin(-2,0);
    square_coin(2,0); 
    // enemy_one.push_back(Dushman(0,0,2,0.03,20,COLOR_DARK_GREY));
    dragon.push_back(Hexagon(glm::vec3(3,3,0)));
    enemy_two.push_back(Mdushman(4,0,2,0.04,1.0,-1.0,COLOR_BLACK));    
    enemy_two.push_back(Mdushman(4,0.2,2,0.04,1.0,-1.0,COLOR_BLACK));    
    enemy_three.push_back(Boomerang(3,3,-6.0/60,-1.4/60.0,0.05,0,COLOR_BOOM));  
    magnet_pole = Magnet(-1,-7.5,10);
    s_ring = Ring(0,0,COLOR_BLACK);
    twox_s.push_back(Powerup(-1,-1,COLOR_GREEN));
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    reshapeWindow (window, width, height);

    // Background color of the scene
    // glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    // glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) 
{
    srand(time(0));
    int width  = 1600;
    int height = 1400;
    flag_jet_on=0;
    window = initGLFW(width, height);

    initGL (window, width, height);
     
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            
            bounding_box_t a=s_ring.bounding_box(),b=hero.bounding_box();
            if (detect_collision(a,b) && s_ring.position.x + 2.5 >  b.x)
            {
                circle=true;
            }
            
            check_collision_overall();
            check_mag();
            display(to_string(Final_Score));
            // tick_elements();
            tick_input(window);
            if(Final_Score > 300* level)
            {
                Final_Score=0;
                level++;
                stage_multiplier+=0.2;
            }
        }
        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() 
{
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}



void scroll(int xoffset, int yoffset) {
		if (yoffset == 1)
				screen_zoom = min(screen_zoom + 0.02, 1.1);
		else if (yoffset == -1)
				screen_zoom = max(screen_zoom - 0.02, 0.7);
		// if (xoffset == 1)
		// 	setScreenX(max((float)screen_center_x - 0.02f, hero.position.x - 2));
		// else if (xoffset == -1)
		// 	setScreenX(min((float)screen_center_x + 0.02f, hero.position.x + 2));

		reset_screen();
                    
}