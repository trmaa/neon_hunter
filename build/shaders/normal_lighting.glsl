#version 130

uniform sampler2D texture;
uniform sampler2D normalmap;

uniform vec3 entity_position;
const int LIGHTS_AMOUNT = 100;
uniform vec3 lightspots_pos[LIGHTS_AMOUNT];
uniform vec3 lightspots_col[LIGHTS_AMOUNT];
uniform float lightspots_int[LIGHTS_AMOUNT];

vec3 toneshift(vec3 color, vec3 light_color) {
	float brightness = length(color);

    vec3 sky_color = vec3(0.0, 0.1, 0.3);

    vec3 shift = mix(sky_color, light_color, brightness);

    return mix(color, shift, 0.6);
}

void main() {
    vec2 uv = gl_TexCoord[0].xy;

    vec3 albedo = texture2D(texture, uv).rgb;
    vec3 normal = texture2D(normalmap, uv).rgb * 2 - 1;

	float total_diff = 0;
	vec3 total_lcol = vec3(0);
	int iters = 0;
	for (int i = 0; i < LIGHTS_AMOUNT; i++) {
		if (lightspots_pos[i] == vec3(7389)) { // undefined
            iters = i;
            break;
        }

		vec3 distance = lightspots_pos[i] - entity_position;
        vec3 light_dir = normalize(distance);
		float light_int = lightspots_int[i];
		if (lightspots_int[i] > length(distance)) {
    		light_int = length(distance);
		}
		float dotp = clamp(dot(normal, light_dir), 0.0, 1.0);
		float diff = max(dotp, 0.2) * light_int / length(distance);
        total_diff += diff;
		total_lcol += lightspots_col[i]*diff;
	}
    float avg_diff = total_diff / iters;
	vec3 avg_lcol = total_lcol / iters;

    vec3 lit_color = albedo * avg_diff;

    vec3 shifted = toneshift(lit_color, avg_lcol);
	float pixel_alfa = texture2D(texture, uv).a;
    gl_FragColor = vec4(shifted, pixel_alfa);
}
