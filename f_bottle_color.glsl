#version 330


out vec4 pixelColor; //Output variable. Almost final pixel color.

in vec4 ic;

void main(void) {
	pixelColor = ic;
}
