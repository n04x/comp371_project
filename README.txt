//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
////////													//////
//////// 		THOMAS BACKS STUDENT ID: 27554524 			//////
//////// 		PROGRAMMING ASSIGNMENT #1					//////
//////// 		COMP 371: COMPUTER GRAPHICS WINTER 			//////
//////// 		DUE: SESSION 5 BY 5 PM						//////
////////													//////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

NOTE:
******************************************************************
*	The assignment has been compiled and run					**
*	in Visual Studio 2017. Don't forget to change it to your	**
*	version of Visual Studio.									**
------------------------------------------------------------------
*	Copyright													**
*	stb_image.h source from https://github.com/nothings/stb		**
*	public domain libraries for C/C++							**
******************************************************************

FOLDER PATHING:
==================================================================
=	camera\ 	-> contains the class for Camera view			 =
=	objects\	-> Contains class to create object in space		 =
=				   such as Coordinate, Grid, and Horse.			 =
=	shaders\	-> contains the Shaders Class for vertex/fragment=
==================================================================

WORLD TRANSFORMATION:
------------------------------------------------------------------
-		'x' -> enable or disable texture in the world:			 -
-			-> by default, texture is enabled					 -
-		'b' -> enable or disable shadow in the world:			 -
-			-> by default, shadow is disabled					 -
------------------------------------------------------------------

HOW TO MOVE YOUR HORSE:
------------------------------------------------------------------
-  LEFTSHIFT + 'W' -> move the horse along the negative x axis.	 -
-  LEFTSHIFT + 'S' -> move the horse along the positive x axis.	 -
-  LEFTSHIFT + 'D' -> move the horse along the negative z axis.	 -
-  LEFTSHIFT + 'A' -> move the horse along the positive z axis.	 -
==================================================================
-  		'w' -> rotate the horse upwards of 5 degrees			 -
-  		's' -> rotate the horse downward of 5 degrees			 -
-  		'd' -> rotate the horse to the right about 5 degrees	 -
-  		'a' -> rotate the horse to the left about 5 degrees		 -
-		'SPACEBAR' -> relocate the horse at random positions	 -
-		'FN + HOME' -> reset initial position and orientation 	 -
-		'r' -> Make the horse compete a run or walk cycle		 -
==================================================================
-		'2' -> raise the horse neck CW							 -
-		'SHIFT + 2' -> raise the horse neck CCW	 				 -
-		'3' -> raise the horse front right leg					 -
-		'SHIFT + 3' -> lower the horse front right leg			 -
-		'4' -> rotate the horse front right knee CW		 		 -
-		'SHIFT + 4' -> rotate the horse front right knee CCW	 -
-		'5' -> raise the horse hind right leg					 -
-		'SHIFT + 5' -> lower the horse hind right leg			 -
-		'6' -> rotate the horse hind right knee CW				 -
-		'SHIFT + 6' -> rotate the horse hind right knee CCW		 -
-		'7' -> raise the horse front left leg					 -
-		'SHIFT + 7' -> lower the horse front left leg			 -
-		'8' -> rotate the horse front left knee CW				 -
-		'SHIFT + 8' -> rotate the horse front left knee CCW 	 -
-		'9' -> raise the horse hind left leg					 -
-		'SHIFT + 9' -> lower the horse hind left leg			 -
-		'0' -> rotate the horse hind left knee CW				 -
-		'SHIFT + 0' -> rotate the horse hind left knee CCW 		 -
------------------------------------------------------------------

HOW TO MOVE YOUR CAMERA:
------------------------------------------------------------------
- UPARROW -> move the camera upwards the y-axis.			 	 -
- DOWNARROW -> move the camera downwards the y-axis.			 -
- LEFTARROW -> move camera to the left along x-axis.			 -
- RIGHTARROW -> move camera to the right along x-axis.		 	 -
- LEFTMOUSE -> zoom-in and out camera along the z-axis.			 -
- RIGHTMOUSE -> hold right click and change angle along x-axis.	 -
- MIDMOUSE -> hold left click and change angle along y-axis.	 -													 -
------------------------------------------------------------------

HORSE TRANSFORMATION:
------------------------------------------------------------------
-		'P' or 'p' -> change the rendering to points			 -
-		'L' or 'l' -> change the rendering to lines				 -
-		'T' or 't' -> change the rendering to fill				 -
-		'U' or 'u' -> scale-up the size of the horse			 -
-		'J' or 'j' -> scale-down the size of the horse			 -
------------------------------------------------------------------