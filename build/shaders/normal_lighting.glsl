#version 130

uniform float time;
uniform sampler2D texture;
uniform sampler2D normalmap;

void main() {
    vec2 uv = gl_TexCoord[0].xy;

    vec3 albedo = texture2D(texture, uv).rgb;
    vec3 normal = texture2D(normalmap, uv).rgb;

    vec3 light_dir = vec3(sin(time), 0, cos(time));

    float diff = max(dot(normal, light_dir), 0.3);

    gl_FragColor = vec4(albedo * diff, 1.0);
}
