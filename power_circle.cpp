#include "structs.h"
#include "essentials.h"
#include <cmath>
#include <iostream>

class PowerCircle
{
	
	public:
	VAO *circle;
	GLfloat centre_x, centre_y, radius, value;
	GLfloat R, G, B;
	GLfloat color_buffer_data [9];
	GLfloat vertex_buffer_data [9];
	void initialize (GLfloat x, GLfloat y, GLfloat r)
	{
		value = power;
		centre_x = x;	centre_y = y;	radius = r;
		R = 1.0;
		G = 0.0;
		//R = (power - min_power)/(max_power - min_power);
		//G = (power - max_power)/(max_power - min_power);
		B = 0.0;
		createCircle(centre_x, centre_y, radius, R, G, B);
	}

	void createCircle (GLfloat x, GLfloat y, GLfloat r, GLfloat col_R, GLfloat col_G, GLfloat col_B)
	{
  		// GL3 accepts only Triangles. Quads are not supported
  		vertex_buffer_data[0] = x;			vertex_buffer_data[1] = y;			vertex_buffer_data[2] = 0;
  		vertex_buffer_data[3] = x-r;		vertex_buffer_data[4] = y;			vertex_buffer_data[5] = 0;
  		vertex_buffer_data[6] = x-(r*cos(deg2rad(1.0)));			vertex_buffer_data[7] = y+(r*sin(deg2rad(1.0)));		vertex_buffer_data[8] = 0;

  		color_buffer_data [0] = color_buffer_data [3] = color_buffer_data [6] = col_R;
  		color_buffer_data [1] = color_buffer_data [4] = color_buffer_data [7] = col_G;
  		color_buffer_data [2] = color_buffer_data [5] = color_buffer_data [8] = col_B;

  		// create3DObject creates and returns a handle to a VAO that can be used later
		circle = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, color_buffer_data, GL_FILL);
	}

	void drawCircle (glm::mat4 VP)
	{
		  glm::mat4 MVP;
		  float max_angle = deg2rad((value*180)/max_power);
		  GLfloat col_R, col_G, col_B;

			col_R = max_angle/deg2rad(180.0f);
			col_G = (deg2rad(180.0f)-max_angle)/deg2rad(180.0f);
			col_B = 0.0f;

			//printf("%f\t%f\t%f\t%f\n",value, col_R, col_G, col_B);

		  	color_buffer_data [0] = color_buffer_data [3] = color_buffer_data [6] = col_R;
  			color_buffer_data [1] = color_buffer_data [4] = color_buffer_data [7] = col_G;
  			color_buffer_data [2] = color_buffer_data [5] = color_buffer_data [8] = col_B;
  			//color_buffer_data[0] = color_buffer_data[1] = color_buffer_data[2] = 1.0;
  			createCircle(centre_x, centre_y, radius, col_R, col_G, col_B);
  			//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_FILL);
			//circle = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, color_buffer_data, GL_FILL);
		  
		  for(float i=0; i>-max_angle; i-=0.01)
		  {
				Matrices.model = glm::mat4(1.0f);
      			GLfloat ang = (GLfloat)(i);
      			//printf("%f \t %f\n", value, ang);

      			glm::mat4 translateTriangle1 = glm::translate (glm::vec3(-centre_x, -centre_y, 0.0f)); // glTranslatef
      			glm::mat4 rotateTriangle = glm::rotate(ang, glm::vec3(0,0,1));  // rotate about vector (0,0,1) Rotating about z-axis
      			glm::mat4 translateTriangle2 = glm::translate (glm::vec3(centre_x, centre_y, 0.0f)); // glTranslatef

      			Matrices.model *= (translateTriangle2 * rotateTriangle * translateTriangle1);
      			MVP = VP * Matrices.model; // MVP = p * V * M
      			glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
      			draw3DObject(circle);
		}
		return;
	}
};