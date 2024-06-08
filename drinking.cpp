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
float drunkenness = 0.0f;
const float drinkingRate = 0.005f;
const float drinkingTolerance = 0.04f;
bool isDrinkingAnimation = false;
bool isBeerTexChosen = false;
float bottleShift = 0.0f;

void beerTextureGenerate() {
	isBeerTexChosen = true;
	//generate whether romper or zubr will be displayed
	std::random_device rd;  // Seed generator
	std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_real_distribution<> dis(0, 10); // Range [1.0, 2.0)
	int random_value = dis(gen);
	if (random_value % 2 == 0) {
		texBeer = texZubr;
	}
	else {
		texBeer = texRomper;
	}
}

void drinkingAnimation(glm::mat4 P, glm::mat4 V) {
	if (!isBeerTexChosen) {
		beerTextureGenerate();
	}
	bottleShift -= 0.01f;
	beerBottleAnimation(P, V, bottleShift);

	if (bottleShift < -3.5f) {
		isDrinkingAnimation = false;
		isBeerTexChosen = false;
		bottleShift = 0.0f;
	}
}