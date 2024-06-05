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
const float drinkingRate = 0.00005f;
const float drinkingTolerance = 0.1f;
bool drinkingAnimation = false;
bool beerTexChosen = false;
float bottleShift = 0.0f;