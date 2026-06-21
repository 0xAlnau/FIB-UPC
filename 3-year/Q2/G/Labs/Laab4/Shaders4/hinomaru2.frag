#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform bool classic;

const float pi = 3.141592;

void main()
{
    float d = distance(vtexCoord, vec2(0.5,0.5));
    
    if (step(0.2,d) == 0.0) fragColor = vec4(1.0, 0.0, 0.0, 0.0);
    
    else {
    	if (classic) fragColor = vec4(1.0);
    	else {
	    float psi = pi / 16.0;
	    
	    vec2 u = vtexCoord - vec2(0.5,0.5); //desti - origen
	    
	    float theta = atan(u.t, u.s);
	    if (mod(theta/psi +0.5, 2) < 1) fragColor = vec4(1.0, 0.0, 0.0, 0.0);
	    else fragColor = vec4(1.0);   
    	}
    }
}
