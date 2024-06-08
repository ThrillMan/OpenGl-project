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
extern GLuint texCig;
extern GLuint texCigPack;
extern GLuint texCigPackNormal;
extern GLuint texCigPackHeight;

GLuint readTexture(const char* filename);
void texCube(glm::mat4 P, glm::mat4 V, glm::mat4 M, GLuint tex, float m, int type);
void beerBottleNeckGeneration(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void shelf(glm::mat4 P, glm::mat4 V, glm::vec3 coordinates, GLuint tex, float m);
void cigarettePackGeneration(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void cigarettePackAnimation(glm::mat4 P, glm::mat4 V, float packShift);
void cigaretteGeneration(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void cigaretteAnimation(glm::mat4 P, glm::mat4 V, float cigaretteShift);
void beerBottleGeneration(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void beerBottleAnimation(glm::mat4 P, glm::mat4 V, float bottleShift);
void death();
void drawScene(GLFWwindow* window, glm::vec3 position, glm::vec3 orientation, glm::vec3 up);
void initShaders();
void freeShaders();
