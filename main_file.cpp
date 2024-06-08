/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
//#include "shaderprogram.h"
#include "walking.h"
#include <drawing_objects.h>
#include "drinking.h"
GLFWwindow* window;


//Error processing callback procedure
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}


//Initialization code procedure
void initOpenGLProgram(GLFWwindow* window) {
	initShaders();
	//************Place any code here that needs to be executed once, at the program start************
	glClearColor(0, 0, 0, 1); //Set color buffer clear color
	glEnable(GL_DEPTH_TEST); //Turn on pixel depth test based on depth buffer
	//glfwSetKeyCallback(window, key_callback);
	texFloor = readTexture("floor.png");
	texWall = readTexture("wall.png");
	texShelf1 = readTexture("shelf1.png");
	texShelf2 = readTexture("shelf2.png");
	texShelf3 = readTexture("shelf3.png");
	texDeath = readTexture("death.png");
	texZubr = readTexture("zubr.png");
	texRomper = readTexture("romper.png");
	texCig = readTexture("cigarette.png");
	texCigPack = readTexture("camel.png");//tex0
	texCigPackNormal = readTexture("bricks2_normal.png");//tex1
	texCigPackHeight = readTexture("bricks2_height.png");//tex2
}

//Release resources allocated by the program
void freeOpenGLProgram(GLFWwindow* window) {
	//delete spBottleTexture;
	//delete spBottleColor;
	freeShaders();
	glDeleteTextures(1, &tex);
	//************Place any code here that needs to be executed once, after the main loop ends************
}



int main(void)
{

	glfwSetErrorCallback(error_callback);//Register error processing callback procedure

	if (!glfwInit()) { //Initialize GLFW library :3
		fprintf(stderr, "Can't initialize GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);  //Create a window 500pxx500px titled "OpenGL" and an OpenGL context associated with it. 

	if (!window) //If no window is opened then close the program
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Since this moment OpenGL context corresponding to the window is active and all OpenGL calls will refer to this context.
	glfwSwapInterval(1); //During vsync wait for the first refresh

	GLenum err;
	if ((err = glewInit()) != GLEW_OK) { //Initialize GLEW library
		fprintf(stderr, "Can't initialize GLEW: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Call initialization procedure

	//Main application loop

	glfwSetTime(0); //clear internal timer
	while (!glfwWindowShouldClose(window)) //As long as the window shouldnt be closed yet...
	{
		
		if (!isDead) {
			walking();
			if (drunkenness > 0.0f) {
				drunkMov();
			}
		}
		
		//angle += speed * glfwGetTime(); //Compute an angle by which the object was rotated during the previous frame		
		//glfwSetTime(0); //clear internal timer

		glfwSetTime(0); //clear internal timer
		drawScene(window, position,orientation,up); //Execute drawing procedure
		glfwPollEvents(); //Process callback procedures corresponding to the events that took place up to now
	}
	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Delete OpenGL context and the window.
	glfwTerminate(); //Free GLFW resources
	exit(EXIT_SUCCESS);
}
