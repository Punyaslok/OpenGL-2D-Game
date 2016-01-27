#include <bits/stdc++.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "structs.h"
#include "essentials.h"
#include "triangle.cpp"
#include "rectangle.cpp"
//#include "circle.cpp"
#include "projectile.cpp"
#include "power_circle.cpp"
#include "rect_obstacle.cpp"
#include "line.cpp"
//#include "score.cpp"
#include "life.cpp"
#include "coins.cpp"


using namespace std;

GLuint programID;

/* Function to load Shaders - Use it as it is */
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path) {

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open())
	{
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

	// Link the program
	fprintf(stdout, "Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void quit(GLFWwindow *window)
{
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}


/**************************
 * Customizable functions *
 **************************/
//Score sc_dis;

//Circle2 whoa;

Triangle first_tri;


Life life[10];

// Ground Details
Rectangle ground;



//Canon Details
Circle canon_base;
Rectangle canon;
pair <float, float> canon_base_point;
float canon_len, canon_wid, canon_ang, canon_rot_status;



// Ball Details
Projectile ball;


Circle test_cir;

Rectangle score[7];

PowerCircle meter;

Rectangle r_obs[10];

Coin c_obs[20];

void make_c_obs()
{
  GLfloat R=255.0/255.0,G=179.0/255.0,B=0.0,r=30;
  c_obs[0].initialize(0, (-scr_height/2)+ground_height+30, 30, 0.0, 0.0, R, G, B);
  c_obs[1].initialize(160, (-scr_height/2)+ground_height+30, 30, 0.0, 0.0, R, G, B);
  c_obs[2].initialize(180, (-scr_height/2)+ground_height+160, 30, 0.0, 0.0, R, G, B);
  c_obs[3].initialize(200, 50, 30, 0.0, 0.0, R, G, B);
  c_obs[4].initialize(400, 50, 30, 0.0, 0.0, R, G, B);
  c_obs[5].initialize(-75, 170, 30, 0.0, 0.0, R, G, B);
  c_obs[6].initialize(-75, -80, 30, 0.0, 0.0, R, G, B);
  c_obs[7].initialize(300, 240, 30, 0.0, 0.0, R, G, B);
  c_obs[8].initialize(460, -200, 30, 0.0, 0.0, R, G, B);

  return;
}

void make_r_obs()
{
  GLfloat R = 111.0/255.0,G=78.0/255.0,B=55.0/255.0;
  r_obs[0].initialize(-100, -230, -100, -150, -50, -150, -50, -230, R, G, B);
  r_obs[1].initialize(-100, 260, -100, 360, -50, 360, -50, 260, R, G, B);
  r_obs[2].initialize(200, -100, 200, -50, 350, -50, 350, -100, R, G, B);
  r_obs[3].initialize(480, 0, 480, 50, 640, 50, 640, 0, R, G, B);
  r_obs[4].initialize(-100, -10, -100, 75, -50, 75, -50, -10, R, G, B);
  return;
}

void initialize_score(GLfloat x, GLfloat y, GLfloat t, GLfloat h, GLfloat b)
{
  GLfloat R=0, G=0, B=0;
  GLfloat x1, y1, x2, y2, x3, y3, x4, y4;
  for (int i=0;i<7;i++)
  {
    if (i==0)
    {
      x1 = x2 = x;    x3 = x4 = x+t;
      y1 = y4 = y;    y2 = y3 = y+(h/2)+(t/2);
    }
    else if (i==1)
    {
      x1 = x2 = x;    x3 = x4 = x+t;
      y1 = y4 = y+(h/2)-(t/2);    y2 = y3 = y+(h);
    }
    else if (i==2)
    {
      x1 = x2 = x;    x3 = x4 = x+b;
      y1 = y4 = y+h-t;  y2 = y3 = y+h;
    }
    else if (i==3)
    {
      x1 = x2 = x+b-t;    x3 = x4 = x+b;
      y1 = y4 = y+(h/2)-(t/2);    y2 = y3 = y+(h);
    }
    else if (i==4)
    {
      x1 = x2 = x+b-t;    x3 = x4 = x+b;
      y1 = y4 = y;    y2 = y3 = y+(h/2)+(t/2);
    }
    else if (i==5)
    {
      x1 = x2 = x;    x3 = x4 = x+b;
      y1 = y4 = y;      y2 = y3 = y+t;
    }
    else if (i==6)
    {
      x1 = x2 = x+t;    x3 = x4 = x+b-t;
      y1 = y4 = y+(h/2)-(t/2);  y2 = y3 = y+(h/2)+(t/2);
    }
    score[i].initialize(x1, y1, x2, y2, x3, y3, x4, y4, R, G, B);
  }
  return;
}

void draw_score(int zzz, glm::mat4 VP)
{
  int arr[7];
  for (int i=0;i<7;i++)arr[i]=1;
  if (zzz==0)arr[6]=0;
  else if (zzz==1)arr[0]=arr[1]=arr[2]=arr[5]=arr[6]=0;
  else if (zzz==2)arr[1]=arr[4]=0;
  else if (zzz==3)arr[0]=arr[1]=0;
  else if (zzz==4)arr[2]=arr[0]=arr[5]=0;
  else if (zzz==5)arr[0]=arr[3]=0;
  else if (zzz==6)arr[3]=0;
  else if (zzz==7)arr[0]=arr[1]=arr[5]=arr[6]=0;
  else if (zzz==9)arr[0]=0;
  for (int i=0;i<7;i++)
    if (arr[i]==1)
      score[i].drawRectangle(VP);
}
void initialize_all()
{
  
  //whoa.initialize(-400,0,70,0,0,1,1,0);

  //sc_dis.initialize(0, 0, 50, 100, 1.0, 0.0, 0.0);

  initialize_score((scr_width/2)-100, (scr_height/2)-150, 20, 100, 70);

  air_drag = 0.01;


  right_click_flag = 0;
  points = 0; balls_left = 8;




  //first_tri.initialize(0,0,100,100,100,-100);

  ground_x = scr_width/2; ground_y = scr_height/2; ground_color_R=0.0/255.0; ground_color_G=82.0/255.0; ground_color_B=0.0/255.0;
  ground_height = 50;
  ground.initialize(-ground_x, -ground_y, -ground_x, -ground_y+ground_height, ground_x, -ground_y+ground_height, ground_x, -ground_y, ground_color_R, ground_color_G, ground_color_B);



  canon_rot_status = 0;
  canon_len = 150;  canon_wid = 40;   canon_ang = 45;
  canon_base_point = make_pair(-(scr_width/2)+50, -ground_y+ground_height+(canon_wid/2));
  canon.initialize(
    canon_base_point.first, canon_base_point.second-(canon_wid/2), 
    canon_base_point.first, canon_base_point.second+(canon_wid/2), 
    canon_base_point.first+canon_len, canon_base_point.second+(canon_wid/2), 
    canon_base_point.first+canon_len, canon_base_point.second-(canon_wid/2), 
    0/255.0, 33.0/255.0, 71.0/255.0 );
  canon_base.initialize(-(scr_width/2)+50, -ground_y+ground_height, canon_wid*1.25, 0.0, 0.0, 0/255.0, 33/255.0, 71.0/255.0);


  min_power = 1.0;  max_power = 25.0;
  initial_power = power = 10.0;

  fric_acc = 0.2;
  ball.initialize(-100, 0, 20, 0.0, 0.0, 0/255.0, 0.0, 0.0);
  ball.in_motion = 0; ball.friction = 0;
  
  meter.initialize(0.0, -scr_height/2, ground_height);
  //test_cir.initialize(40-(scr_width/2), -40+(scr_height/2), 20, 0.0, 0.0, 1.0, 1.0, 1.0);

  //c_obs.initialize(100, 0, 20, 0.0, 0.0, 1.0, 1.0, 0.0);
  
  num_c_obs = 9;
  make_c_obs();

  num_r_obs = 5;
  make_r_obs();

  //r_obs.initialize(100, 150, 100, 200, 200, 200, 200, 150, 1.0, 1.0, 1.0);
 for (int i=0;i<balls_left;i++)
  {
    life[i].initialize((canon_base_point.first)+(i*50), -(scr_height/2)+(ground_height/2), 20, 0.0, 0.0, 217.0/255.0, 96.0/255.0, 59.0/255.0);
  }


  return;
}


void collisions_with_circ_obstacles()
{
  //printf("%f \t %f \t %f\n", dist(cx, cy, ball.cent_x(), ball.cent_y()) , cr, ball.cir_radius());
  for (int i=0;i<num_c_obs;i++)
  {
    GLfloat cx=c_obs[i].centre_x, cy=c_obs[i].centre_y, cr=c_obs[i].radius;
    if (dist(cx, cy, ball.cent_x(), ball.cent_y()) <= cr+ball.cir_radius())
    {
      //printf("collision\n");
      GLfloat ang = atan2(cy-ball.cent_y(), cx-ball.cent_x());
      //printf("%f\n", ang);
      points++;
      //printf("Points = %d\n", points);
      for (int j=i;j<num_c_obs-1;j++)c_obs[j]=c_obs[j+1];
      num_c_obs--;
    }
  }
  return;
}


void collisions_with_rect_obstacles()
{
  for (int ii=0;ii<num_r_obs;ii++)
  {
    GLfloat cx = ball.cent_x(), cy = ball.cent_y(), cr = ball.cir_radius();
    GLfloat px, py, pang;
    int flag=0;
    for (int i=0;i<360;i++)
      {
        pang = deg2rad(i);
        px = cx + cr*cos(pang);
        py = cy + cr*sin(pang);

        //printf("%f %f\n", cx, cy);

        if (r_obs[ii].is_in_rectangle(px, py) == true)
        {
          flag=1;
          break;
        }
      }
    if (flag==1)
    {
      //printf("collision with rectangle\n");
      if (r_obs[ii].hor_collision(px, py))
        ball.invert_vel_x();
      if (r_obs[ii].ver_collision(px, py))
        ball.invert_vel_y();
    }
  }
  return;
}

void pan_left(){   if ((-(zoom_factor*scr_width)/2)+pan>-scr_width/2)pan-=pan_increment;  }
void pan_right(){  if (((zoom_factor*scr_width)/2)+pan<scr_width/2)pan+=pan_increment;    }

void zoom_out()
{
  zoom_factor = min(max_zoom_factor, zoom_factor+zoom_factor_increment);
  if (((zoom_factor*scr_width)/2)+pan >= scr_width/2)
    pan = (scr_width/2)-((zoom_factor*scr_width)/2);
  else if (((-(zoom_factor*scr_width)/2)+pan)<=(-scr_width/2))
    pan = (-scr_width/2) - ((-(zoom_factor*scr_width)/2));
}
void zoom_in()
{
  zoom_factor = max(min_zoom_factor, zoom_factor-zoom_factor_increment);
}


float camera_rotation_angle = 90;

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE) {
        switch (key) {
            case GLFW_KEY_C:
                break;
            case GLFW_KEY_P:
                break;
            case GLFW_KEY_X:
                // do something ..
                break;
            case GLFW_KEY_A:
                canon_ang+=1;
                canon_ang = min(95.0f, canon_ang);
                if (canon_ang>=361)
                  canon_ang = 0.0f;
                break;
            case GLFW_KEY_B:
                canon_ang-=1;
                canon_ang = max(0.0f, canon_ang);
                if (canon_ang<=-361)
                  canon_ang = 0.0f;
                break;
            case GLFW_KEY_SPACE:
                if (ball.in_motion==0)
                {
                  ball.in_motion = 1;
                  
                  ball.vel = power;
                  ball.circle.vel_x = ball.vel*cos(deg2rad(canon_ang));   ball.circle.vel_y = ball.vel*sin(deg2rad(canon_ang));
                  balls_left--;
                }
                break;
            case GLFW_KEY_F:
                power = min(100.0f, power+1.0f);
                meter.value = power;
                break;
            case GLFW_KEY_S:
                power = max(1.0f, power-1.0f);
                meter.value = power;
                break;
            case GLFW_KEY_DOWN:
                zoom_out();
                break;
            case GLFW_KEY_UP:
                zoom_in();
                break;
            case GLFW_KEY_LEFT:
                pan_left();
                break;
            case GLFW_KEY_RIGHT:               
                pan_right();
                break;
            default:
                break;
        }
    }
    else if (action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_A:
                canon_ang+=1;
                canon_ang = min(95.0f, canon_ang);
                if (canon_ang>=361)
                  canon_ang = 0.0f;
                break;
            case GLFW_KEY_B:
                canon_ang-=1;
                canon_ang = max(0.0f, canon_ang);
                if (canon_ang<=-361)
                  canon_ang = 0.0f;
                break;
            case GLFW_KEY_F:
                power = min(max_power, power+1);
                meter.value = power;
                break;
            case GLFW_KEY_S:
                power = max(min_power, power-1);
                meter.value = power;
                break;
            case GLFW_KEY_DOWN:
                zoom_out();
                break;
            case GLFW_KEY_UP:
                zoom_in();
                break;
            case GLFW_KEY_LEFT:
                pan_left();
                break;
            case GLFW_KEY_RIGHT:
                pan_right();
                break;
            default:
                break;
        }
    }
    else if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                quit(window);
                break;
            default:
                break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar (GLFWwindow* window, unsigned int key){
	switch (key) {
		case 'Q':
		case 'q':
            quit(window);
            break;
		default:
			break;
	}
}

/* Executed when a mouse button is pressed/released */
void mouseButton (GLFWwindow* window, int button, int action, int mods){
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            if (action == GLFW_RELEASE)
            {
              if (ball.in_motion==0)
                {
                  ball.in_motion = 1;
                  
                  ball.vel = power;
                  ball.circle.vel_x = ball.vel*cos(deg2rad(canon_ang));   ball.circle.vel_y = ball.vel*sin(deg2rad(canon_ang));
                  balls_left--;
                }
            }
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            if (action == GLFW_PRESS)
              right_click_flag = 1;
            if (action == GLFW_RELEASE) {
                right_click_flag = 0;
            }
            break;
        default:
            break;
    }
}


/* Executed when window is resized to 'width' and 'height' */
/* Modify the bounds of the screen here in glm::ortho or Field of View in glm::Perspective */
void reshapeWindow (GLFWwindow* window, int width, int height)
{
  int fbwidth=width, fbheight=height;
  /* With Retina display on Mac OS X, GLFW's FramebufferSize
  is different from WindowSize */
  glfwGetFramebufferSize(window, &fbwidth, &fbheight);

	GLfloat fov = 90.0f;

	// sets the viewport of openGL renderer
	glViewport (0, 0, (GLsizei) fbwidth, (GLsizei) fbheight);

	// set the projection matrix as perspective
	/* glMatrixMode (GL_PROJECTION);
	   glLoadIdentity ();
	   gluPerspective (fov, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1, 500.0); */
	// Store the projection matrix in a variable for future use
    // Perspective projection for 3D views
    // Matrices.projection = glm::perspective (fov, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1f, 500.0f);

    // Ortho projection for 2D views

    Matrices.projection = glm::ortho((-(zoom_factor*scr_width)/2)+pan, ((zoom_factor*scr_width)/2)+pan, -(zoom_factor*scr_height)/2, (zoom_factor*scr_height)/2, 0.1f, 500.0f);
}

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw ()
{
  // clear the color and depth in the frame buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // use the loaded shader program
  // Don't change unless you know what you are doing
  glUseProgram (programID);

  // Eye - Location of camera. Don't change unless you are sure!!
  glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
  // Target - Where is the camera looking at.  Don't change unless you are sure!!
  glm::vec3 target (0, 0, 0);
  // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
  glm::vec3 up (0, 1, 0);

  // Compute Camera matrix (view)
  // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
  //  Don't change unless you are sure!!
  Matrices.view = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane

  // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
  //  Don't change unless you are sure!!
  glm::mat4 VP = Matrices.projection * Matrices.view;

  // Send our transformation to the currently bound shader, in the "MVP" uniform
  // For each model you render, since the MVP will be different (at least the M part)
  //  Don't change unless you are sure!!
  glm::mat4 MVP;	// MVP = Projection * View * Model

  // Load identity to model matrix
  Matrices.model = glm::mat4(1.0f);

  /* Render your scene */

  //first_tri.drawTriangle(VP);

  // Pop matrix to undo transformations till last push matrix instead of recomputing model matrix
  // glPopMatrix ();
  
  canon.drawRectangle(VP, canon_ang, canon_base_point.first, canon_base_point.second);
  canon_base.drawCircle(VP);    // draw this BEFORE ground
  ground.drawRectangle(VP);
  
  if (abs(ball.cir_vel_x())<1 && abs(ball.cir_vel_y())<1 && ball.in_motion!=0 && abs(canon_base_point.second-ball.cent_y())<=ball.cir_radius())
  {
    ball.initialize(-100, 0, 20, 0.0, 0.0, 0/255.0, 0.0, 0.0);
    ball.in_motion = 0; ball.friction = 0;
    power = initial_power;
    meter.value = power;
  }
  //cout<<balls_left<<endl;
  if (ball.in_motion==0 && balls_left>0)
  {
    ball.angle = canon_ang;
    ball.circle.centre_x = canon_base_point.first + ((canon_len-ball.cir_radius())*cos(deg2rad(canon_ang)));    ball.circle.centre_y = canon_base_point.second + ((canon_len-ball.cir_radius())*sin(deg2rad(canon_ang)));
  }
  if (balls_left>=0)
    ball.drawProjectile(VP);

  //printf("Balls left = %d\n", balls_left);


  meter.drawCircle(VP);

  for (int i=0;i<num_r_obs;i++)
    r_obs[i].drawRectangle(VP);

  for (int i=0;i<num_c_obs;i++)
    c_obs[i].drawCircle(VP);

  //sc_dis.drawRectangle(points, VP);

  for (int i=0;i<balls_left;i++)
    life[i].drawCircle(VP);

  draw_score(points, VP);

}
void CursorPosition(GLFWwindow *window, double x_positiona,double y_positiona)
{
    float x_position = (float)x_positiona;
    float y_position = (float)y_positiona;
    
    //cout<<last_x<<" "<<x_position<<endl;

    if (right_click_flag == 1)
    {
      if (x_position<last_x)
        pan_left();   
      else if (x_position>last_x)
          pan_right();
    }

    last_x = x_position;  last_y = y_position;
    x_position-=(canon_base_point.first+(scr_width/2));    y_position-=(scr_height-ground_height);   y_position*=(-1);
    //printf("base point = %f\t%f\n", canon_base_point.first, canon_base_point.second);
    //printf("%lf\t%lf\t%f\t%f\n", x_position, y_position, scr_height, scr_width);
    canon_ang = rad2deg(atan2(y_position, x_position));
    //printf("%f\n",canon_ang);
    if (canon_ang>95)
      canon_ang = 95.0;
    if (canon_ang<0)
      canon_ang = 0;
    ptr_dist = dist(x_position, y_position, 0.0, 0.0);
    power = (max_power*ptr_dist)/(dist(canon_base_point.first, canon_base_point.second, scr_height/2, scr_width/2));
    meter.value = power;

    
    return;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  //printf("%lf\t%lf\n", xoffset, yoffset);

  if (yoffset<0)
    zoom_out();

  else if (yoffset>0)
    zoom_in();
  return;
}

/* Initialise glfw window, I/O callbacks and the renderer to use */
/* Nothing to Edit here */
GLFWwindow* initGLFW (int width, int height)
{
    GLFWwindow* window; // window desciptor/handle

    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Sample OpenGL 3.3 Application", NULL, NULL);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval( 1 );

    /* --- register callbacks with GLFW --- */

    /* Register function to handle window resizes */
    /* With Retina display on Mac OS X GLFW's FramebufferSize
     is different from WindowSize */
    glfwSetFramebufferSizeCallback(window, reshapeWindow);
    glfwSetWindowSizeCallback(window, reshapeWindow);

    /* Register function to handle window close */
    glfwSetWindowCloseCallback(window, quit);

    /* Register function to handle keyboard input */
    glfwSetKeyCallback(window, keyboard);      // general keyboard input
    glfwSetCharCallback(window, keyboardChar);  // simpler specific character handling

    /* Register function to handle mouse click */
    glfwSetMouseButtonCallback(window, mouseButton);  // mouse button clicks

    return window;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL (GLFWwindow* window, int width, int height)
{
  /* Objects should be created before any other gl function and shaders */
	// Create the models
	//createTriangle (); // Generate the VAO, VBOs, vertices data & copy into the array buffer
	//createRectangle ();
	
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "Sample_GL.vert", "Sample_GL.frag" );
	// Get a handle for our "MVP" uniform
	Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

	
	reshapeWindow (window, width, height);

    // Background color of the scene
	glClearColor (135.0/255.0, 206.0/255.0, 235.0/255.0, 0.0f); // R, G, B, A
	glClearDepth (1.0f);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);

  glfwSetCursorPosCallback(window, CursorPosition);
  glfwSetScrollCallback(window, scroll_callback);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}




int main (int argc, char** argv)
{

  zoom_factor = 1.0;    zoom_factor_increment = 0.02;
  min_zoom_factor = 0.7;    max_zoom_factor = 1.0;

  pan = 0.0;    pan_increment = 5.0;

	int width = 1280;
	int height = 720;

	scr_height = height;
	scr_width = width;

  curr_level = 1;

    GLFWwindow* window = initGLFW(width, height);

	initGL (window, width, height);

    double last_update_time = glfwGetTime(), current_time;

    initialize_all();
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        reshapeWindow (window, width, height);

        // mouse operations
        
        //glfwGetCursorPos(window, &mouse_x, &mouse_y);
        //mouse_x-=(scr_width/2);   mouse_y-=(scr_height/2);



        // OpenGL Draw commands
        draw();

        // Swap Frame Buffer in double buffering
        glfwSwapBuffers(window);

        // Poll for Keyboard and mouse events
        glfwPollEvents();
        // Control based on time (Time based transformation like 5 degrees rotation every 0.5s)
        current_time = glfwGetTime(); // Time in seconds
        if ((current_time - last_update_time) >= 0.01) { // atleast 0.5s elapsed since last frame
            // do something every 0.5 seconds ..
            //cout<<time(NULL)<<endl;
            collisions_with_rect_obstacles();
            collisions_with_circ_obstacles();
            last_update_time = current_time;
        }
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
