#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

const mat4 sca = mat4(vec4(1.0,0.0,0.0,0.0), vec4(0.0,0.75,0.0,0.0), vec4(0.0,0.0,1.0,0.0), vec4(0.0,0.0,0.0,1.0));

void main()
{
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * sca * vec4(vertex, 1.0);
}
