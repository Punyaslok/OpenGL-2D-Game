#include "structs.h"
#include "essentials.h"
#include <iostream>

class Triangle
{
	VAO *triangle;
	GLfloat x1, x2, x3, y1, y2, y3;
	public:
	void initialize (GLfloat xa, GLfloat ya, GLfloat xb, GLfloat yb, GLfloat xc, GLfloat yc)
	{
		x1 = xa;	x2 = xb;	x3 = xc;
		y1 = ya;	y2 = yb;	y3 = yc;
		createTriangle(x1, y1, x2, y2, x3, y3);
	}

	void createTriangle (GLfloat xa, GLfloat ya, GLfloat xb, GLfloat yb, GLfloat xc, GLfloat yc)
	{
  		// ONLY vertices between the bounds specified in glm::ortho will be visible on screen 

  		// Define vertex array as used in glBegin (GL_TRIANGLES)
  		const GLfloat vertex_buffer_data [] = {
    		xa, ya,0, // vertex 0
		    xb, yb,0, // vertex 1
		    xc, yc,0, // vertex 2
  		};

  		const GLfloat color_buffer_data [] = {
    		1,0,0, // color 0
		    0,1,0, // color 1
    		0,0,1, // color 2
  		};

  		// create3DObject creates and returns a handle to a VAO that can be used later
  		triangle = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, color_buffer_data, GL_FILL);
	}

	void drawTriangle (glm::mat4 VP)
	{
		glm::mat4 MVP;
		Matrices.model = glm::mat4(1.0f);
		MVP = VP * Matrices.model; // MVP = p * V * M
		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
		draw3DObject(triangle);
	}
};