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
#include "smoking.h"
float cigaretteShift = 0.0f;
float packShift = 0.0f;
bool isSmokingAnimation = false;
bool isPackAnimation = false;
void smokingAnimation(glm::mat4 P, glm::mat4 V) {
	float durationOfPack = -1.7f;
	float durationOfCig = -1.5f;
	if (isPackAnimation) {
		packShift -= 0.01f;
		cigarettePackAnimation(P, V, packShift);

		if (packShift < durationOfPack) {
			isPackAnimation = false;
			packShift = 0.0f;
		}
	
	}
	else {
		cigaretteShift -= 0.01f;
		cigaretteAnimation(P, V, cigaretteShift);

		if (cigaretteShift < durationOfCig) {
			isSmokingAnimation = false;
			cigaretteShift = 0.0f;
		}
	}
	
}