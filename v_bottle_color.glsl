#version 330

//Uniform variables
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

uniform vec4 lp; //Light position in world space

//Attributes
in vec4 vertex; //Vertex coordinates in model space
in vec4 color;  //Vertex color
in vec4 normal; //Normal coordinates in model space

//Varying variables
out vec4 ic;

void main(void) {

    vec4 l = normalize(V * lp - V * M * vertex);//Light vector, eye space
    vec4 n = normalize(V * M * normal);//Normal vector, eye space
    vec4 v = normalize(vec4(0, 0, 0, 1) - V * M * vertex);
    vec4 r = reflect(-l, n);

    float nl = clamp(dot(n, l), 0, 1); //Cosine of the angle between n and l
    float rv = pow(clamp(dot(r, v), 0, 1), 25);

    ic = vec4(color.rgb * nl*2.5f, color.a)+vec4(rv,rv,rv,0); //Lambertian term + Phong term for white reflection color

    gl_Position=P*V*M*vertex;
}
