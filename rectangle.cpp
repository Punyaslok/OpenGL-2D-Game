#include "structs.h"
#include "essentials.h"
#include <iostream>

class Rectangle
{
	VAO *rectangle;
	GLfloat x1, x2, x3, y1, y2, y3, x4, y4;
	public:
	void initialize (GLfloat xa, GLfloat ya, GLfloat xb, GLfloat yb, GLfloat xc, GLfloat yc, GLfloat xd, GLfloat yd, GLfloat col_R, GLfloat col_G, GLfloat col_B)
	{
		x1 = xa;	x2 = xb;	x3 = xc;	x4 = xd;
		y1 = ya;	y2 = yb;	y3 = yc;	y4 = yd;
		//printf ("%f \t %f \t %f \t %f \t %f \t %f \t %f \t %f\n",x1, y1, x2, y2, x3, y3, x4, y4);
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

  		GLfloat color_buffer_data [] = {
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

	bool is_in_rectangle (GLfloat x, GLfloat y)			// Only for straight rectangles
	{
		if (x>=x1 && x<=x4 && y>=y1 && y<=y2)
			return true;
		return false;
	}

	bool hor_collision(GLfloat x, GLfloat y)			// Only for straight rectangles
	{
		GLfloat range = 10;
		//printf("%f \t %f \t %f\n", x, x1-range, x1+range);
		if ((x<=x1+range && x>=x1-range) || (x<=x4+range && x>=x4-range))
			return true;
		return false;
	}

	bool ver_collision(GLfloat x, GLfloat y)			// Only for straight rectangles
	{
		GLfloat range = 10;
		//printf("%f \t %f \t %f\n", y, y1-range, y1+range);
		if ((y<=y1+range && y>=y1-range) || (y<=y2+range && y>=y2-range))
			return true;
		return false;
	}



	void drawRectangle (glm::mat4 VP, GLfloat Angle = 0.0f, GLfloat rect_centre_x = 0.0f, GLfloat rect_centre_y = 0.0f)
	{
		glm::mat4 MVP;
		Matrices.model = glm::mat4(1.0f);

		glm::mat4 translateRectangle = glm::translate (glm::vec3(-rect_centre_x, -rect_centre_y, 0));        // glTranslatef, Translates and brings to origin
		glm::mat4 rotateRectangle = glm::rotate(deg2rad(Angle), glm::vec3(0, 0, 1));  // rotate about vector (0,0,1) Rotating about z-axis
		glm::mat4 translateRectangle2 = glm::translate (glm::vec3(rect_centre_x, rect_centre_y, 0));        // glTranslatef, Translates and takes back to its original position
		
		Matrices.model*= (translateRectangle2*rotateRectangle*translateRectangle);			// Right to left , i.e. operation appearing on the right is executed first

		MVP = VP * Matrices.model; // MVP = p * V * M
		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
		draw3DObject(rectangle);
	}
};