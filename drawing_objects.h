#pragma once

extern GLuint texFloor;
extern GLuint tex;
extern GLuint texWall;
extern GLuint texShelf1;
extern GLuint texShelf2;
extern GLuint texShelf3;
extern GLuint texDeath;
extern GLuint texBeer;
extern GLuint texZubr;
extern GLuint texRomper;


GLuint readTexture(const char* filename);
void texCube(glm::mat4 P, glm::mat4 V, glm::mat4 M, GLuint tex, float m, int type);
void colorCube(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void shelf(glm::mat4 P, glm::mat4 V, glm::vec3 coordinates, GLuint tex, float m);
void beerBottleGeneration(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void beerBottleAnimation(glm::mat4 P, glm::mat4 V, float bottleShift);
void death();
void drawScene(GLFWwindow* window, glm::vec3 position, glm::vec3 orientation, glm::vec3 up);
void initShaders();
void freeShaders();
