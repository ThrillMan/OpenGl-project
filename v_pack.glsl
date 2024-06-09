#version 330

//Uniform variables
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

//Attributes
in vec4 vertex; //Vertex coordinates in model space
in vec2 texCoord0;
in vec4 c1;
in vec4 c2;
in vec4 c3;

//Varying variables
out vec4 l;
out vec4 v;
out vec2 iTexCoord0;

void main(void) {
    mat4 invTBN = mat4(c1, c2, c3, vec4(0, 0, 0, 1));
    vec4 lp = vec4(0, 50, -6, 1); //light position, world space

    l = normalize(invTBN * inverse(M) * lp - invTBN* vertex); //vector towards the light in tbn space
    v = normalize(invTBN * inverse(V*M)*vec4(0, 0, 0, 1) - invTBN * vertex); //vector towards the viewer in tbn space    

    iTexCoord0 = texCoord0;

    gl_Position = P * V * M * vertex;
}
