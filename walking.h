#pragma once


extern bool flying;
extern bool vKeyPressed;
extern bool isDead;

extern GLFWwindow* window;
extern glm::vec3 position;
extern glm::vec3 orientation;
extern glm::vec3 up;

void walking();
void drunkMov();