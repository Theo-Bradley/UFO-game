shader_type spatial;
render_mode shadows_disabled;

uniform float scale = 1.0;
uniform vec3 tint : source_color = vec3(1.0);

float checker(vec2 pos)
{
	float x = step(0.5, sin(pos.x) + 0.5);
	float y = step(0.5, sin(pos.y + x * PI) + 0.5);
	return y;
}

void vertex() {
	// Called for every vertex the material is visible on.
}

void fragment() {
	// Called for every pixel the material is visible on.
	vec3 col = vec3(checker(UV * scale));
	ALBEDO = col * tint;
}

//void light() {
//	// Called for every pixel for every light affecting the material.
//	// Uncomment to replace the default light processing function with this one.
//}
