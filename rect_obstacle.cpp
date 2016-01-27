#include "structs.h"
#include "essentials.h"
#include <iostream>

class RectObstacle
{
	
	public:
	VAO *rectangle;
	GLfloat x1, x2, x3, y1, y2, y3, x4, y4, angle, centre_x, centre_y, length, breadth, radius;
	void initialize (GLfloat cx, GLfloat cy, GLfloat l, GLfloat b, GLfloat ang, GLfloat col_R, GLfloat col_G, GLfloat col_B)
	{
		centre_x = cx;	centre_y = cy;		length = l; breadth = b;		angle = ang;
		GLfloat tx, ty;

		tx = length/2;
		ty = breadth/2;

		x1 = (-tx*cos(angle)) - (-ty*sin(angle));
		y1 = (-tx*sin(angle)) + (-ty*cos(angle));
		x1+=centre_x;
		y1+=centre_y;


		x2 = (-tx*cos(angle)) - (ty*sin(angle));
		y2 = (-tx*sin(angle)) + (ty*cos(angle));
		x2+=centre_x;
		y2+=centre_y;

		
		x3 = (tx*cos(angle)) - (ty*sin(angle));
		y3 = (tx*sin(angle)) + (ty*cos(angle));
		x3+=centre_x;
		y3+=centre_y;



		x4 = (tx*cos(angle)) - (-ty*sin(angle));
		y4 = (tx*sin(angle)) + (-ty*cos(angle));
		x4+=centre_x;
		y4+=centre_y;

		radius = (length+breadth)/2;

		createRectangle(x1, y1, x2, y2, x3, y3, x4, y4, col_R, col_G, col_B);
	}

	void createRectangle (GLfloat xa, GLfloat ya, GLfloat xb, GLfloat yb, GLfloat xc, GLfloat yc, GLfloat xd, GLfloat yd, GLfloat col_R, GLfloat col_G, GLfloat col_B)
	{
  		// GL3 accepts only Triangles. Quads are not supported
  		const GLfloat vertex_buffer_data [] = {
    		xa, ya, 0, // vertex 1
    		xb, yb, 0, // vertex 2
    		xc, yc, 0, // vertex 3

    		xc, yc, 0, // vertex 3
    		xd, yd, 0, // vertex 4
    		xa, ya, 0  // vertex 1
  		};

  		const GLfloat color_buffer_data [] = {
    		col_R, col_G, col_B, // color 1
    		col_R, col_G, col_B, // color 2
    		col_R, col_G, col_B, // color 3

    		col_R, col_G, col_B, // color 3
    		col_R, col_G, col_B, // color 4
    		col_R, col_G, col_B  // color 1
  		};
  		// create3DObject creates and returns a handle to a VAO that can be used later
		rectangle = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_buffer_data, GL_FILL);
	}

	void drawRectangle (glm::mat4 VP)
	{
		//GLfloat rect_centre_x = (x1+x3)/2, rect_centre_y = (y1+y3)/2;
		GLfloat rect_centre_x = centre_x, rect_centre_y = centre_y;

		glm::mat4 MVP;
		Matrices.model = glm::mat4(1.0f);

		//glm::mat4 translateRectangle = glm::translate (glm::vec3(-rect_centre_x, -rect_centre_y, 0));        // glTranslatef, Translates and brings to origin
		//glm::mat4 rotateRectangle = glm::rotate(deg2rad(angle), glm::vec3(0, 0, 1));  // rotate about vector (0,0,1) Rotating about z-axis
		//glm::mat4 translateRectangle2 = glm::translate (glm::vec3(rect_centre_x, rect_centre_y, 0));        // glTranslatef, Translates and takes back to its original position
		
		//Matrices.model*= (translateRectangle2*rotateRectangle*translateRectangle);			// Right to left , i.e. operation appearing on the right is executed first

		MVP = VP * Matrices.model; // MVP = p * V * M
		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
		draw3DObject(rectangle);
	}
};