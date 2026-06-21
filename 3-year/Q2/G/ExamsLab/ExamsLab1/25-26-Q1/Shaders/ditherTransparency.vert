#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;
out float dCam;
out float dDia;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

void main()
{
    vec3 Peye = (modelViewMatrix * vec4(vertex, 1.0)).xyz;
    dCam = distance(vec3(0.0), Peye);
    dDia = distance(modelViewMatrix * vec4(boundingBoxMin, 1.0), modelViewMatrix * vec4(boundingBoxMax, 1.0));

    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
