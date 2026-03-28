#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D foot0;
uniform sampler2D foot1;
uniform sampler2D foot2;
uniform sampler2D foot3;

const float R = 80.0;

uniform int layer = 1;

uniform vec2 mousePosition;
uniform bool virtualMouse = false;
uniform float mouseX, mouseY; 



vec2 mouse()
{
	if (virtualMouse) return vec2(mouseX, mouseY);
	else return mousePosition;
}

void main()
{
	// a completar. Recorda usar mouse() per obtenir les coords del mouse, en window space
	float d = distance(gl_FragCoord.xy, mouse());
	vec4 C = texture(foot0, vtexCoord);
	if (d >= R) gl_FragColor = C;
	else {
		vec4 D;
		if (layer == 0) D = C;
		else if (layer == 1) D = texture(foot1, vtexCoord);
		else if (layer == 2) D = texture(foot2, vtexCoord);
		else D = texture(foot3, vtexCoord);
		gl_FragColor = mix(D,C, (d/R));
	}

}
