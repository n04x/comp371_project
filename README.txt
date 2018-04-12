//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
////////													//////
//////// 		THOMAS BACKS STUDENT ID: 27554524 			//////
//////// 		PROGRAMMING PROJECT 						//////
//////// 		COMP 371: COMPUTER GRAPHICS WINTER 			//////
//////// 		DUE: APRIL	12TH							//////
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
=				   such as Coordinate, Grid, and zebra.			 =
=	shaders\	-> contains the Shaders Class for vertex/fragment=
==================================================================

GENERAL FEATURES:
------------------------------------------------------------------
-		'h' or 'H'-> to make AI horses running in all direction	 -
-		'ESC' -> exit the game									 -
------------------------------------------------------------------

WORLD TRANSFORMATION:
------------------------------------------------------------------
-		'x' or 'X' -> enable or disable texture in the world:	 -
-			-> by default, texture is enabled					 -
-		'b' or 'B' -> enable or disable shadow in the world:	 -
-			-> by default, shadow is disabled					 -
------------------------------------------------------------------

HOW TO MOVE YOUR PLAYER ZEBRA:
------------------------------------------------------------------
-  LEFTSHIFT + 'W' -> move the zebra along the negative x axis.	 -
-  LEFTSHIFT + 'S' -> move the zebra along the positive x axis.	 -
-  LEFTSHIFT + 'D' -> move the zebra along the negative z axis.	 -
-  LEFTSHIFT + 'A' -> move the zebra along the positive z axis.	 -
==================================================================
-  		'w' -> rotate the zebra upwards of 5 degrees			 -
-  		's' -> rotate the zebra downward of 5 degrees			 -
-  		'd' -> rotate the zebra to the right about 5 degrees	 -
-  		'a' -> rotate the zebra to the left about 5 degrees		 -
-		'SPACEBAR' -> relocate the zebra at random positions	 -
-		'FN + HOME' -> reset initial position and orientation 	 -
-		'r' -> Make the zebra compete a run or walk cycle		 -
==================================================================
-		'1' -> rotate the zebra head CW							 -
-		'SHIFT' + '1' -> rotate the zebra head CCW				 -
-		'2' -> raise the zebra neck CW							 -
-		'SHIFT + 2' -> raise the zebra neck CCW	 				 -
-		'3' -> raise the zebra front right leg					 -
-		'SHIFT + 3' -> lower the zebra front right leg			 -
-		'4' -> rotate the zebra front right knee CW		 		 -
-		'SHIFT + 4' -> rotate the zebra front right knee CCW	 -
-		'5' -> raise the zebra hind right leg					 -
-		'SHIFT + 5' -> lower the zebra hind right leg			 -
-		'6' -> rotate the zebra hind right knee CW				 -
-		'SHIFT + 6' -> rotate the zebra hind right knee CCW		 -
-		'7' -> raise the zebra front left leg					 -
-		'SHIFT + 7' -> lower the zebra front left leg			 -
-		'8' -> rotate the zebra front left knee CW				 -
-		'SHIFT + 8' -> rotate the zebra front left knee CCW 	 -
-		'9' -> raise the zebra hind left leg					 -
-		'SHIFT + 9' -> lower the zebra hind left leg			 -
-		'0' -> rotate the zebra hind left knee CW				 -
-		'SHIFT + 0' -> rotate the zebra hind left knee CCW 		 -
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

zebra TRANSFORMATION:
------------------------------------------------------------------
-		'P' or 'p' -> change the rendering to points			 -
-		'L' or 'l' -> change the rendering to lines				 -
-		'T' or 't' -> change the rendering to fill				 -
-		'U' or 'u' -> scale-up the size of the zebra			 -
-		'J' or 'j' -> scale-down the size of the zebra			 -
------------------------------------------------------------------