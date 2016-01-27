#include "structs.h"
#include "essentials.h"
#include <iostream>

class Circle2
{
	
	public:
	VAO *circle;
	GLfloat centre_x, centre_y, radius, vel_x, vel_y;
	GLfloat R, G, B;
	GLfloat vertex_buffer_data [1200];
	GLfloat color_buffer_data [1200];
	void initialize (GLfloat x, GLfloat y, GLfloat r, GLfloat vel_x=0.0, GLfloat vel_y=0.0, GLfloat col_R=0.0, GLfloat col_G=0.0, GLfloat col_B=0.0)
	{
		centre_x = x;	centre_y = y;	radius = r;
		R = col_R;	G = col_G; B = col_B;
		createCircle(centre_x, centre_y, radius, col_R, col_G, col_B);
	}

	void createCircle (GLfloat x, GLfloat y, GLfloat r, GLfloat col_R, GLfloat col_G, GLfloat col_B)
	{
  		
    		vertex_buffer_data[0] = x;	vertex_buffer_data[1] = y;	vertex_buffer_data[2] = 0; // centre
    		color_buffer_data[0] = col_R; color_buffer_data [1] = col_G; color_buffer_data[2] = col_B;

    		int xx=3;
    		for (int i=0;i<361;i++)
    		{
    			vertex_buffer_data[xx] = x + (radius*cos(deg2rad(i)));
    			color_buffer_data[xx] = col_R;
    			xx++;

    			vertex_buffer_data[xx] = y + (radius*sin(deg2rad(i)));
    			color_buffer_data[xx] = col_G;
    			xx++;

    			vertex_buffer_data[xx] = 0;
    			color_buffer_data[xx] = col_B;
    			xx++;

    		}
  		// create3DObject creates and returns a handle to a VAO that can be used later
		circle = create3DObject(GL_TRIANGLE_FAN, 362, vertex_buffer_data, color_buffer_data, GL_FILL);
	}

	void drawCircle (glm::mat4 VP)
	{
		  glm::mat4 MVP;
		 
				Matrices.model = glm::mat4(1.0f);
      			//GLfloat ang = (GLfloat)(i * M_PI/360);
      			//printf("%f\n", ang);
      			//glm::mat4 translateTriangle1 = glm::translate (glm::vec3(-centre_x, -centre_y, 0.0f)); // glTranslatef
      			//glm::mat4 rotateTriangle = glm::rotate(ang, glm::vec3(0,0,1));  // rotate about vector (0,0,1) Rotating about z-axis
      			//glm::mat4 translateTriangle2 = glm::translate (glm::vec3(centre_x, centre_y, 0.0f)); // glTranslatef

      			//Matrices.model *= (translateTriangle2 * rotateTriangle * translateTriangle1);
      			MVP = VP * Matrices.model; // MVP = p * V * M
      			glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
      			draw3DObject(circle);
		return;
	}

	
};