#version 330 core
uniform mat4 modelViewProjectionMatrix;

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec3 normalO;

void main()
{
	normalO = normal;
	gl_Position = modelViewProjectionMatrix * vec4(vertex,1.0);
} 
