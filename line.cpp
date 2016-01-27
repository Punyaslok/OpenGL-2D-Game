#include "structs.h"
#include "essentials.h"
#include <iostream>

class Line
{
public:
	// ax+by+c = 0;
	GLfloat a, b, c;
	void form(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
	{
		a = y1 - y2;
		b = x2 - x1;
		c = (x1*(y2-y1)) - (y1*(x2-x1));
	}

	int sign(GLfloat x, GLfloat y)
	{
		GLfloat ret = (a*x) + (b*y) + c;
		if (ret == 0)
			return 0;
		else if (ret < 0 )
			return -1;
		else if (ret>0)
			return 1;
	}
};