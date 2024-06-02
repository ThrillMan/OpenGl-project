#pragma once


extern GLuint texFloor;
extern GLuint tex;
extern GLuint texWall;
extern GLuint texShelf1;
extern GLuint texShelf2;
extern GLuint texShelf3;


GLuint readTexture(const char* filename);
void texCube(glm::mat4 P, glm::mat4 V, glm::mat4 M, GLuint tex, float m, int type);
void cube(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void shelf(glm::mat4 P, glm::mat4 V, glm::vec3 coordinates, GLuint tex, float m);
void drawScene(GLFWwindow* window, glm::vec3 position, glm::vec3 orientation, glm::vec3 up);
void initShaders();
void freeShaders();
