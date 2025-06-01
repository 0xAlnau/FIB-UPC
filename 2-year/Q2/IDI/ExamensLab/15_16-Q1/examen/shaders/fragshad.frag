#version 330 core

in vec3 fcolor;
out vec4 FragColor;

uniform float varFranges;

void main()
{	
	if (varFranges == 0.0) FragColor = vec4(fcolor,1);
	else {
		if (mod(gl_FragCoord.y, 10) < 5) FragColor = vec4(vec3(1,1,1),1);
		else FragColor = vec4(vec3(0,0,0),1);
	}
}
