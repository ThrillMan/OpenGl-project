#pragma once
extern float drunkenness;
//how much voltage does one beer have
extern const float drinkingRate;
extern const float drinkingTolerance;
extern bool isDrinkingAnimation;

extern bool isBeerTexChosen;

extern float bottleShift;

//randomly chooses from set of textures
void beerTextureGenerate();
void beerBottleGeneration(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void beerBottleAnimation(glm::mat4 P, glm::mat4 V, float bottleShift);
//starts drinking animation and all the methods associated with it
void drinkingAnimation(glm::mat4 P, glm::mat4 V);