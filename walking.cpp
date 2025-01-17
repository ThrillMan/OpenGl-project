#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <random>

#include "walking.h"
#include "drawing_objects.h"
#include "drinking.h"
#include "smoking.h"
bool flying = false;
bool vKeyPressed = false;
bool isDead = false;

float speed = 0.01f;
float rotSpeed = 0.9f;
float currentPitch = 0;

glm::vec3 position = glm::vec3(0.0f, 0.0f, -5.0f);
glm::vec3 orientation = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 up = glm::vec3(0.0f, -1.0f, 0.0f);


void walking() {

	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
		// If the V key is pressed and wasn't pressed in the previous frame, toggle the flying state
		if (!vKeyPressed) {
			flying = !flying;
			vKeyPressed = true; // Mark the key as pressed
		}
	}
	else {
		// If the V key is not pressed, reset the flag
		vKeyPressed = false;
	}

	//drinking beer
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		if (!isDrinkingAnimation && !isSmokingAnimation)
		{
			drunkenness += drinkingRate;
			isDrinkingAnimation = true;
		}
		
	}
	//smoking
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		if (!isDrinkingAnimation&& !isSmokingAnimation)
		{
			//drunkenness += drinkingRate;
			isPackAnimation = true;
			isSmokingAnimation = true;
		}

	}

	//character movement

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if (flying)
		{
			position += speed * orientation;
		}
		else {
			position += speed * glm::vec3(orientation.x, 0.0f, orientation.z);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		if (flying)
		{
			position -= speed * orientation;
		}
		else {
			position -= speed * glm::vec3(orientation.x, 0.0f, orientation.z);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position -= speed * glm::normalize(glm::cross(orientation, up));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += speed * glm::normalize(glm::cross(orientation, up));
	}

	//sprinting
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.04f;
	}
	else speed = 0.01f;


	//flying movement like in mc
	if (flying) {
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			position += speed * up;

		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			position -= speed * up;
		}
	}

	//camera movement
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		orientation = glm::rotate(orientation, glm::radians(rotSpeed), up);

	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		orientation = glm::rotate(orientation, glm::radians(-rotSpeed), up);

	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(rotSpeed), glm::normalize(glm::cross(orientation, up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (currentPitch + rotSpeed < 89.0f)
		{
			orientation = newOrientation;
			currentPitch += rotSpeed;

		}

	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotSpeed), glm::normalize(glm::cross(orientation, up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (currentPitch-rotSpeed>-89.0f)
		{
			orientation = newOrientation;
			currentPitch -= rotSpeed;

		}
	}
}
void drunkMov() {
	std::random_device rd;  // Seed generator
	std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_real_distribution<> dis(drunkenness*-1, drunkenness); // Range [1.0, 2.0)
	float random_value = dis(gen);
	//character position
	position.x += random_value;
	random_value = dis(gen);
	position.z += random_value;
	//camera postion
	random_value = dis(gen);
	orientation= glm::rotate(orientation, glm::radians(random_value*20), up);

	if (drunkenness > drinkingTolerance) {
		isDead = true;
	}
}