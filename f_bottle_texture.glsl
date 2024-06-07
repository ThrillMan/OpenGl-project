#version 330

uniform sampler2D textureMap0;

// Varying variables
in vec4 n;
in vec4 l;
in vec4 v;
in vec2 iTexCoord0;

// Output variable
out vec4 pixelColor;

void main(void) {
    // Normalized, interpolated vectors
    vec4 ml = normalize(l);
    vec4 mn = normalize(n);
    vec4 mv = normalize(v);
    // Reflected vector
    vec4 mr = reflect(-ml, mn);

    // Surface parameters
    vec4 kd = texture(textureMap0, iTexCoord0);
    vec4 ks = vec4(0.8, 0.6, 0.1, 0.0); // Slightly yellow specular color


    // Ambient light component
    vec4 ambientLight = vec4(0.1, 0.1, 0.1, 1.0)*4; // Adjust the intensity as needed

    // Lighting model computation
    float nl = clamp(dot(mn, ml), 0, 1);
    float rv = pow(clamp(dot(mr, mv), 0, 1), 25);
    vec4 diffuse = kd * nl;
    vec4 specular = ks * rv;

    // Combine ambient, diffuse, and specular components
    const float shineIntensity = 0.5f;
    pixelColor = ambientLight * kd + diffuse + vec4(specular.rgb, 0.0)*shineIntensity;
    pixelColor.a = kd.a; // Set alpha channel to the texture's alpha
}