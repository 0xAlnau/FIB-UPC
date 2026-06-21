#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;
out vec3 P;
out vec3 nEye;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

void main()
{
    float a = radians(90.0);
    mat4 rotX = mat4(vec4(1.0,0.0,0.0,0.0), vec4(0.0,cos(a),sin(a),0.0), vec4(0.0,-sin(a),cos(a),0.0), vec4(0.0,0.0,0.0,1.0));

    P = (modelViewMatrix * rotX * vec4(vertex, 1.0)).xyz;
    nEye = normalMatrix * (rotX * vec4(normal, 1.0)).xyz;

    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * rotX * vec4(vertex, 1.0);
}
