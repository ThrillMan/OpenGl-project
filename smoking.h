#pragma once
extern float cigaretteShift;
extern float packShift;
extern bool isSmokingAnimation;
//first the camel pack then normal cig
extern bool isPackAnimation;
//starts smoking animation and all the methods associated with it
void smokingAnimation(glm::mat4 P, glm::mat4 V);