#version 330

out vec4 pixelColor; //Output variable. Almost final pixel color.

uniform sampler2D textureMap0;
uniform sampler2D textureMap1;
uniform sampler2D textureMap2;

//Varying variables
in vec4 l;
in vec4 v;
in vec2 iTexCoord0;

vec2 parallaxTexCoords(vec4 v, vec2 t, float h, float s) {
	vec2 ti = -v.xy / s;
	float hi = -v.z / s;

	vec2 tc = t;
	float hc = h;
	float ht = h * texture(textureMap2, tc).r;

	if (v.z <= 0) discard;

	while (hc > ht) {
		tc = tc + ti;
		if (tc.x < 0 || tc.x>1 || tc.y < 0 || tc.y>1) discard;
		hc = hc + hi;
		ht = h * texture(textureMap2, tc).r;
	}


	return tc;
}


void main(void) {
	vec4 mv = normalize(v);
	vec2 tc = parallaxTexCoords(mv, iTexCoord0, 0.1, 500);

	//Normalized, interpolated vectors
	vec4 ml = normalize(l);		
	vec4 mn = normalize(vec4(2*texture(textureMap1, tc).xyz-1,0));
	//Reflected vector
	vec4 mr = reflect(-ml, mn);

		 // Ambient light component
    vec4 ambientLight = vec4(0.1, 0.1, 0.1, 1.0)*40; // Adjust the intensity as needed
	//Surface parameters
	vec4 kd = texture(textureMap0, tc)*ambientLight;
	vec4 ks = vec4(1, 1, 1, 1);// texture(textureMap1, iTexCoord0);

	//Lighting model computation
	float nl = clamp(dot(mn, ml), 0, 1);
	float rv = pow(clamp(dot(mr, mv), 0, 1), 50);
	pixelColor = vec4(kd.rgb * nl, kd.a) + vec4(ks.rgb * rv, 0);
}
