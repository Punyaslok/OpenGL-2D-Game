#include "circle.cpp"
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

class Projectile
{
  public:
  	Circle circle;
  	GLfloat angle, vel;
  	int in_motion, friction;
  	void initialize(GLfloat x, GLfloat y, GLfloat r, GLfloat v, GLfloat ang, GLfloat col_R, GLfloat col_G, GLfloat col_B)
  	{
  		circle.centre_x = x;	circle.centre_y = y;   circle.radius = r;     angle = ang;
  		vel = v;
    		circle.vel_x = v*cos(deg2rad(angle));		circle.vel_y = v*sin(deg2rad(angle));
    		circle.R=col_R; circle.G = col_G; circle.B=col_B;
    		circle.initialize(
    			x, y, 
    			circle.radius, 
    			circle.vel_x, circle.vel_y,
    			col_R, col_G, col_B);
    }

    GLfloat cent_x(){return circle.centre_x;}
    GLfloat cent_y(){return circle.centre_y;}
    GLfloat cir_radius(){return circle.radius;}
    GLfloat cir_vel_x(){return circle.vel_x;}
    GLfloat cir_vel_y(){return circle.vel_y;}

    int check_ground_collision()
  	{
  		if (in_motion==-1)
  			return 1;
  		if (-ground_y + ground_height + circle.radius >= circle.centre_y)
  		{
  			circle.vel_y*=(-0.7);
  			if (abs(circle.vel_y) <= 2)
  			{
  				circle.vel_y=0;
  				circle.centre_y = -ground_y + ground_height + circle.radius;
  				in_motion = -1;     friction = 1;
  			}
  			else
  			{
  				circle.centre_y = max(-ground_y + ground_height + circle.radius + 5, circle.centre_y + circle.vel_y);
  			}
  			return 1;
  		}
  		return 0;
  	}

    int check_roof_collision()
    {
      if (in_motion==-1)
        return 1;
      if ((scr_height/2) - circle.radius <= circle.centre_y)
      {
        circle.vel_y*=(-1);
        
      circle.centre_y = max((scr_height/2) - circle.radius - 5, circle.centre_y + circle.vel_y);
      
        return 1;
      }
      return 0;
    }
    void invert_vel_x(){circle.vel_x*=(-1);}
    void invert_vel_y(){circle.vel_y*=(-1);}

    void check_sidewall_collision()
    {
        if (circle.centre_x + circle.radius >= scr_width/2)
        {
          invert_vel_x();
          circle.centre_x = (scr_width/2) - circle.radius - 1;
        }

        if (circle.centre_x - circle.radius <= -(scr_width/2))
        {
          invert_vel_x();
          circle.centre_x = -(scr_width/2) + circle.radius + 1;
        }

    }

    void drawProjectile(glm::mat4 VP)
    {
    		
        //printf("in_motion = %d \t friction = %d \t vel_x = %f\n",in_motion, friction, circle.vel_x);

    		if (in_motion == 1)
    		{
          if (friction==1)
          {
            if (circle.vel_x<=1 && circle.vel_x>=-1)
              circle.vel_x = 0;
            else if (circle.vel_x > 0 )
              circle.vel_x-=fric_acc;
            else if (circle.vel_x < 0 )
              circle.vel_x+=fric_acc;
          }
          else if (friction==0)
          {
            circle.vel_x-=(air_drag*circle.vel_x);
          }
    			if (check_ground_collision()==0)
    				circle.centre_y = max(-ground_y + ground_height + circle.radius, circle.centre_y + circle.vel_y);

          if (check_roof_collision()==0)
            circle.centre_y = min((scr_height/2) - circle.radius, circle.centre_y + circle.vel_y);

          check_sidewall_collision();
          circle.centre_x += circle.vel_x;

    			circle.vel_y += gravity;
          circle.vel_y -= (air_drag*circle.vel_y);
    			
    		}
    		else if (in_motion == -1)
    		{
          if (friction==1)
          {
            if (circle.vel_x<=1 && circle.vel_x>=-1)
              circle.vel_x = 0;
            else if (circle.vel_x > 0 )
              circle.vel_x-=fric_acc;
            else if (circle.vel_x < 0 )
              circle.vel_x+=fric_acc;
          }
          check_sidewall_collision();
    			circle.centre_x += circle.vel_x;
    		}

    		circle.createCircle(circle.centre_x, circle.centre_y, circle.radius, circle.R, circle.G, circle.B);
    		circle.drawCircle(VP);

    	}
};