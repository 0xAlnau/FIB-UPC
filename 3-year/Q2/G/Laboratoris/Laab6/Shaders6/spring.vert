#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform float time;

void main()
{
    vec3 posVertex;
    float time2 = mod(time, 3.5);
    if (time2 <= 0.5) {
        float t = (time2 / 0.5) * (time2 / 0.5) * (time2 / 0.5);
	posVertex = mix(vec3(0.0), vertex, t); //mix(origen, desti, factor[0,1])
    }
    else {
    	float t = (time2 - 0.5) / 3.0; //n
    	posVertex = mix(vertex, vec3(0.0), t);
    	
    }
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(N.z);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(posVertex, 1.0);
}
