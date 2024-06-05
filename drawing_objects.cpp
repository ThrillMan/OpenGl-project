#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <random>
#include "constants.h"
#include "allmodels.h"
#include "lodepng.h"
#include "myCube.h"
#include "shaderprogram.h"
#include "walking.h"
#include "drawing_objects.h"
#include "drinking.h"
GLuint tex, texFloor, texWall, texShelf1, texShelf2, texShelf3, texDeath,texZubr,texRomper;
GLuint readTexture(const char* filename) {
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);

	//Read into computers memory
	std::vector<unsigned char> image;   //Allocate memory 
	unsigned width, height;   //Variables for image size
	//Read the image
	unsigned error = lodepng::decode(image, width, height, filename);

	//Import to graphics card memory
	glGenTextures(1, &tex); //Initialize one handle
	glBindTexture(GL_TEXTURE_2D, tex); //Activate handle
	//Copy image to graphics cards memory reprezented by the active handle
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return tex;
}
void texCube(glm::mat4 P, glm::mat4 V, glm::mat4 M, GLuint tex, float m, int type) {
	//This array should rather be placed in the myCube.h file, but I placed it here so that the full solution of the exercise is placed in a single procedure	
	float myCubeTexCoords[] = {
		m, 0.0f,	  0.0f, m,    0.0f, 0.0f,
		m, 0.0f,   m, m,    0.0f, m,

		m, 0.0f,	  0.0f, m,    0.0f, 0.0f,
		m, 0.0f,   m, m,    0.0f, m,

		m, 0.0f,	  0.0f, m,    0.0f, 0.0f,
		m, 0.0f,   m, m,    0.0f, m,

		m, 0.0f,	  0.0f, m,    0.0f, 0.0f,
		m, 0.0f,   m, m,    0.0f, m,

		m, 0.0f,	  0.0f, m,    0.0f, 0.0f,
		m, 0.0f,   m, m,    0.0f, m,

		m, 0.0f,	  0.0f, m,    0.0f, 0.0f,
		m, 0.0f,   m, m,    0.0f, m,
	};
	spTextured->use(); //Aktywuj program cieniujący

	glUniformMatrix4fv(spTextured->u("P"), 1, false, glm::value_ptr(P)); //Copy projection matrix into shader program uniform variable
	glUniformMatrix4fv(spTextured->u("V"), 1, false, glm::value_ptr(V)); //Copy view matrix into shader program uniform variable
	glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M)); //Copy model matrix into shader program uniform variable


	glEnableVertexAttribArray(spTextured->a("vertex"));
	glVertexAttribPointer(spTextured->a("vertex"), 4, GL_FLOAT, false, 0, myCubeVertices); //Use vertex coordinates stored in myCubeVertices array

	glEnableVertexAttribArray(spTextured->a("texCoord"));
	glVertexAttribPointer(spTextured->a("texCoord"), 2, GL_FLOAT, false, 0, myCubeTexCoords); //Use texture coordinates stored in myCubeTexCoords array

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(spTextured->u("tex"), 0);

	//if type == 1 build floor
	//if type == 2 build walls
	//if type == 3 build cube
	if (type == 1)glDrawArrays(GL_TRIANGLES, 18, 6);
	if (type == 2)glDrawArrays(GL_TRIANGLES, 12, 30);
	if (type == 3)glDrawArrays(GL_TRIANGLES, 0, 36);

	//glDrawArrays(GL_TRIANGLES, 18, 12);

	glDisableVertexAttribArray(spTextured->a("vertex"));
	glDisableVertexAttribArray(spTextured->a("texCoord"));
}
void colorCube(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
	spColored->use();

	glUniformMatrix4fv(spColored->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spColored->u("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(spColored->u("M"), 1, false, glm::value_ptr(M));


	glEnableVertexAttribArray(spColored->a("vertex"));
	glVertexAttribPointer(spColored->a("vertex"), 4, GL_FLOAT, false, 0, myCubeVertices);

	glEnableVertexAttribArray(spColored->a("color"));
	glVertexAttribPointer(spColored->a("color"), 4, GL_FLOAT, false, 0, myCubeColors);

	glDrawArrays(GL_TRIANGLES, 0, myCubeVertexCount);

	glDisableVertexAttribArray(spColored->a("vertex"));
	glDisableVertexAttribArray(spColored->a("color"));
}
void beerBottle(glm::mat4 P, glm::mat4 V, glm::mat4 M,GLuint tex) {
	float myCubeColors[] = {
		//Wall 1
		0.4f, 0.2f, 0.1f, 1.0f,
		0.4f, 0.2f, 0.1f, 1.0f,
		0.4f, 0.2f, 0.1f, 1.0f,

		0.4f, 0.2f, 0.1f, 1.0f,
		0.4f, 0.2f, 0.1f, 1.0f,
		0.4f, 0.2f, 0.1f, 1.0f,

		//Wall 2
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		//Wall 3
		0.4f, 0.2f, 0.1f, 1.0f,
		0.4f, 0.2f, 0.1f, 1.0f,
		0.4f, 0.2f, 0.1f, 1.0f,

		0.4f, 0.2f, 0.1f, 1.0f,
		0.4f, 0.2f, 0.1f, 1.0f,
		0.4f, 0.2f, 0.1f, 1.0f,

			//Wall 4
		0.2f, 0.1f, 0.05f, 1.0f,
		0.2f, 0.1f, 0.05f, 1.0f,
		0.2f, 0.1f, 0.05f, 1.0f,

		0.2f, 0.1f, 0.05f, 1.0f,
		0.2f, 0.1f, 0.05f, 1.0f,
		0.2f, 0.1f, 0.05f, 1.0f,

		//Wall 5
		0.2f, 0.1f, 0.05f, 1.0f,
		0.2f, 0.1f, 0.05f, 1.0f,
		0.2f, 0.1f, 0.05f, 1.0f,

		0.2f, 0.1f, 0.05f, 1.0f,
		0.2f, 0.1f, 0.05f, 1.0f,
		0.2f, 0.1f, 0.05f, 1.0f,

		//Wall 6
		0.4f, 0.2f, 0.1f, 1.0f,
		0.4f, 0.2f, 0.1f, 1.0f,
		0.4f, 0.2f, 0.1f, 1.0f,

		0.4f, 0.2f, 0.1f, 1.0f,
		0.4f, 0.2f, 0.1f, 1.0f,
		0.4f, 0.2f, 0.1f, 1.0f,
	};
	float myCubeTexCoords[] = {
		// Wall 1
		0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f,
		0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f,

		// Wall 2 (textured wall)
		1.0f, 0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
		1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,

		// Wall 3
		0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f,
		0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f,

		// Wall 4
		0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f,
		0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f,

		// Wall 5
		0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f,
		0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f,

		// Wall 6
		0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f,
		0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f,
	};

	// Use the colored shader program
	spColored->use();
	glUniformMatrix4fv(spColored->u("P"), 1, GL_FALSE, glm::value_ptr(P));
	glUniformMatrix4fv(spColored->u("V"), 1, GL_FALSE, glm::value_ptr(V));
	glUniformMatrix4fv(spColored->u("M"), 1, GL_FALSE, glm::value_ptr(M));

	// Enable vertex and color attributes
	glEnableVertexAttribArray(spColored->a("vertex"));
	glVertexAttribPointer(spColored->a("vertex"), 4, GL_FLOAT, GL_FALSE, 0, myCubeVertices);

	glEnableVertexAttribArray(spColored->a("color"));
	glVertexAttribPointer(spColored->a("color"), 4, GL_FLOAT, GL_FALSE, 0, myCubeColors);

	// Draw the colored walls (walls 1, 3, 4, 5, 6)
	glDrawArrays(GL_TRIANGLES, 0, 6); // Wall 1 (6 vertices)
	glDrawArrays(GL_TRIANGLES, 12, 24); // Wall 3, Wall 4, Wall 5, and Wall 6 (6 vertices each)

	// Disable color attribute for the textured wall
	glDisableVertexAttribArray(spColored->a("color"));
	glDisableVertexAttribArray(spColored->a("vertex"));

	// Use the textured shader program
	spTextured->use();
	glUniformMatrix4fv(spTextured->u("P"), 1, GL_FALSE, glm::value_ptr(P));
	glUniformMatrix4fv(spTextured->u("V"), 1, GL_FALSE, glm::value_ptr(V));
	glUniformMatrix4fv(spTextured->u("M"), 1, GL_FALSE, glm::value_ptr(M));

	// Enable vertex attribute again
	glEnableVertexAttribArray(spTextured->a("vertex"));
	glVertexAttribPointer(spTextured->a("vertex"), 4, GL_FLOAT, GL_FALSE, 0, myCubeVertices + 24); // Offset to wall 2's vertices

	// Enable texture coordinate attribute
	glEnableVertexAttribArray(spTextured->a("texCoord"));
	glVertexAttribPointer(spTextured->a("texCoord"), 2, GL_FLOAT, GL_FALSE, 0, myCubeTexCoords + 12); // Offset to wall 2's texture coordinates

	// Bind the texture

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(spTextured->u("tex"), 0);

	// Draw the textured wall (wall 2)
	glDrawArrays(GL_TRIANGLES, 0, 36); // Wall 2 (6 vertices)

	// Disable texture coordinate and vertex attributes
	glDisableVertexAttribArray(spTextured->a("texCoord"));
	glDisableVertexAttribArray(spTextured->a("vertex"));
}

void shelf(glm::mat4 P, glm::mat4 V, glm::vec3 coordinates, GLuint tex, float m) {
	glm::mat4 shelf = glm::mat4(1.0f);
	shelf = glm::translate(shelf, coordinates);
	shelf = glm::scale(shelf, glm::vec3(0.5f, 1.0f, 1.0f));
	float myCubeTexCoords[] = {
		0.0f, 0.0f,	  0.0f, 0.0f,    0.0f, 0.0f,
		0.0f, 0.0f,   0.0f, 0.0f,    0.0f, 0.0f,

		0.0f, 0.0f,	  0.0f, 0.0f,    0.0f, 0.0f,
		0.0f, 0.0f,   0.0f, 0.0f,    0.0f, 0.0f,

		0.0f, 0.0f,	  0.0f, 0.0f,    0.0f, 0.0f,
		0.0f, 0.0f,   0.0f, 0.0f,    0.0f, 0.0f,

		0.0f, 0.0f,	  0.0f, 0.0f,    0.0f, 0.0f,
		0.0f, 0.0f,   0.0f, 0.0f,    0.0f, 0.0f,

		m, 0.0f,	  0.0f, m,    0.0f, 0.0f,
		m, 0.0f,   m, m,    0.0f, m,

		m, 0.0f,	  0.0f, m,    0.0f, 0.0f,
		m, 0.0f,   m, m,    0.0f, m,
	};

	spTextured->use(); //Aktywuj program cieniujący

	glUniformMatrix4fv(spTextured->u("P"), 1, false, glm::value_ptr(P)); //Copy projection matrix into shader program uniform variable
	glUniformMatrix4fv(spTextured->u("V"), 1, false, glm::value_ptr(V)); //Copy view matrix into shader program uniform variable
	glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(shelf)); //Copy model matrix into shader program uniform variable


	glEnableVertexAttribArray(spTextured->a("vertex"));
	glVertexAttribPointer(spTextured->a("vertex"), 4, GL_FLOAT, false, 0, myCubeVertices); //Use vertex coordinates stored in myCubeVertices array

	glEnableVertexAttribArray(spTextured->a("texCoord"));
	glVertexAttribPointer(spTextured->a("texCoord"), 2, GL_FLOAT, false, 0, myCubeTexCoords); //Use texture coordinates stored in myCubeTexCoords array

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(spTextured->u("tex"), 0);

	glDrawArrays(GL_TRIANGLES, 0, myCubeVertexCount);

	glDisableVertexAttribArray(spTextured->a("vertex"));
	glDisableVertexAttribArray(spTextured->a("texCoord"));
}
void bottle(glm::mat4 P, glm::mat4 V, float bottleShift,GLuint tex) {
	glm::mat4 bottleMain = glm::mat4(1.0f);
	bottleMain = glm::inverse(V) * bottleMain;
	bottleMain = glm::translate(bottleMain, glm::vec3(0.3f, -0.4f, -1.1f));
	bottleMain = glm::scale(bottleMain, glm::vec3(0.1f, 0.2f, 0.1f));
	glm::mat4 bottleNeck = glm::mat4(1.0f);
	bottleNeck = glm::translate(bottleMain, glm::vec3(0.0f, 1.0f, 0.0f));
	bottleNeck = glm::scale(bottleNeck, glm::vec3(0.5f, 1.0f, 0.5f));

	//centre the bottle
	
	bottleMain = glm::translate(bottleMain, glm::vec3(bottleShift*0.8, 0.0f, 0.0f));
	bottleMain = glm::rotate(bottleMain, glm::radians(-bottleShift*20), glm::vec3(1.0, 0.0f, 0.0f));
	bottleMain = glm::translate(bottleMain, glm::vec3(0.0f, -bottleShift, 0.0f));

	bottleNeck = glm::translate(bottleMain, glm::vec3(0.0f, 1.0f, 0.0f));
	bottleNeck = glm::scale(bottleNeck, glm::vec3(0.5f, 1.0f, 0.5f));
	colorCube(P, V, bottleNeck);
	beerBottle(P, V, bottleMain,tex);
}
void death() {
	drunkenness = 0.0f;
	//glm::mat4 V = glm::lookAt(glm::vec3(20.0f, 20.0f, 20.0f), glm::vec3(200.0f, 20.0f, 200.0f), glm::vec3(0.0f, 0.0f, 0.0f)); //Compute view matrix
	//glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 0.0001f, 500.0f); //Compute projection matrix
	position = glm::vec3(0.0f, -30.0f, 0.0f);
	orientation = glm::vec3(0.0f, 0.0f, 5.0f);
	glm::mat4 V = glm::lookAt(position, position + orientation, up); //Compute view matrix
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 0.0001f, 500.0f); //Compute projection matrix

	glm::mat4 deathScreen = glm::mat4(1.0f);
	deathScreen = glm::translate(deathScreen, position + glm::vec3(0.0f, 0.0f, 5.0f));
	deathScreen = glm::scale(deathScreen, glm::vec3(2.0f, 2.0f, 3.0f));;
	texCube(P, V, deathScreen, texDeath, 1, 3);
}
//Drawing procedure
void drawScene(GLFWwindow* window, glm::vec3 position, glm::vec3 orientation, glm::vec3 up) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear color and depth buffers

	glm::mat4 floor = glm::mat4(1.0f);
	floor = glm::scale(floor, glm::vec3(20.0f, 1.0f, 20.0f));

	//generating basic shelf i can use for generating more of them
	glm::mat4 wall1 = glm::mat4(1.0f);
	wall1 = glm::rotate(wall1, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	wall1 = glm::translate(wall1, glm::vec3(0.0f, 0.0f, -13.0f));
	wall1 = glm::scale(wall1, glm::vec3(20.0f, 20.0f, 30.0f));

	glm::mat4 V = glm::lookAt(position, position + orientation, up); //Compute view matrix
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 0.0001f, 500.0f); //Compute projection matrix

	for (int row = -4; row < 5; row++) {
		if (row == 0) continue;
		for (int number = -4; number < 4; number++) {
			glm::vec3 coordinates = glm::vec3(4.0f * row, 0.0f, 5.0f * number + 3.0f);
			GLuint whatShelfTex;
			if ((number + 4) % 3 == 0) whatShelfTex = texShelf1;
			if ((number + 4) % 3 == 1) whatShelfTex = texShelf2;
			if ((number + 4) % 3 == 2) whatShelfTex = texShelf3;
			shelf(P, V, coordinates, whatShelfTex, 1);
		}
	}

	if (isDead)death();

	texCube(P, V, floor, texFloor, 40, 1);
	//cube(P, V, shelf1);
	//cube(P, V, shelf2);
	texCube(P, V, wall1, texWall, 10, 2);
	if (drinkingAnimation) {
		GLuint beerTex;
		if (!beerTexChosen) {
			beerTexChosen = true;
			//generate whether romper or zubr will be displayed
			std::random_device rd;  // Seed generator
			std::mt19937 gen(rd()); // Mersenne Twister engine
			std::uniform_real_distribution<> dis(0, 10); // Range [1.0, 2.0)
			int random_value = dis(gen);
			if (random_value % 2 == 0) {
				beerTex = texZubr;
			}
			else {
				beerTex = texRomper;
			}
		}
		bottleShift -=0.01f;
		//for (int xAnimation = 0; xAnimation < 20; xAnimation++) {
		//	bottleShift -= 0.1f;
		//	bottle(P, V, -0.1f);
		//}
		bottle(P, V, bottleShift, beerTex);

		if (bottleShift < -3.5f) {
			drinkingAnimation = false;
			beerTexChosen = false;
			bottleShift = 0.0f;
		}
		
	}
	glfwSwapBuffers(window); //Copy back buffer to the front buffer
}
