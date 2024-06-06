#pragma once


extern bool flying;
extern bool vKeyPressed;
extern bool isDead;

extern float speed;
extern float rotSpeed;
extern float currentPitch;

extern GLFWwindow* window;
extern glm::vec3 position;
extern glm::vec3 orientation;
extern glm::vec3 up;

void walking();
void drunkMov();