#version 120

uniform sampler2D texture;

void main() {
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    
	float oldRed = pixel.r;
	float newRed = (1.0 / (oldRed + 0.0001)) - 1.0;
	newRed = clamp(newRed, 0.0, 1.0);
	pixel.r = newRed;

    gl_FragColor = pixel;
}
