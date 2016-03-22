Punyaslok Pattnaik
201464054

1. The compiled executable is sample2D.
	To run, type ./sample2D, then enter.

2. Makefile is "Makefile.linux"

3. 	Souce Code is in "Sample_GL3_2D.cpp".
	To compile, run "g++ -o sample2D Sample_GL3_2D.cpp glad.c -lGL -lglfw -ldl"

4. Controls:

	2.1	Keyboard
		a : rotate turret upwards
		b : rotate turret downwards
		UP : zoom in
		DOWN : zoom out
		LEFT : pan left
		RIGHT : pan right
		f : increase speed of projectile
		s : decrease speed of projectile
		SPACE : fire/shoot

	2.2 Mouse
		LEFT_BUTTON : fire/shoot
		RIGHT_BUTTON : PRESS AND DRAG to pan left or right
		SCROLL_UP : zoom in
		SCROLL_DOWN : zoom out

5. Speed of projectile increases as distance from mouse pointer from canon increases.

6. Gameplay
	Fire balls from the canon by adjusting angle and speed.
	Collect as many gold coins as possible.
