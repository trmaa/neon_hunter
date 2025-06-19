#version 130

uniform float time;
uniform sampler2D texture;
uniform sampler2D normalmap;

vec3 toneshift(vec3 color) {
	float brightness = dot(color, vec3(0.299, 0.587, 0.114));

    vec3 yellow = vec3(1.0, 1.0, 0.0);
    vec3 blue = vec3(0.0, 0.0, 1.0);

    vec3 shift = mix(blue, yellow, brightness);

    return mix(color, shift, 0.2);
}

void main() {
    vec2 uv = gl_TexCoord[0].xy;

    vec3 albedo = texture2D(texture, uv).rgb;
    vec3 normal = texture2D(normalmap, uv).rgb;

    vec3 light_dir = vec3(sin(time), 0, cos(time));

    float diff = max(dot(normal, light_dir), 0.3);

    vec3 lit_color = albedo * diff;

    vec3 shifted = toneshift(lit_color);
	float pixel_alfa = texture2D(texture, uv).a;
    gl_FragColor = vec4(shifted, pixel_alfa);
}
