#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;
out vec3 v;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float time;

void main()
{
    v = vertex;
    vec3 nouV = vertex;
    if (vertex.z == -1.5) nouV.z = -1.5 - pow(sin(time), 2);

    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(nouV, 1.0);
}
