#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float time;

void main()
{
    float A;
    if (vertex.y >= 0.5) A = (vertex.y - 0.5) * sin(time);
    else A = 0;
    mat4 rot = mat4(vec4(1,0,0,0), vec4(0,cos(A),sin(A),0), vec4(0,-sin(A),cos(A),0), vec4(0,0,0,1));
    mat4 trans1 = mat4(vec4(1,0,0,0),vec4(0,1,0,0),vec4(0,0,1,0),vec4(0,-1,0,1)); //inici
    mat4 trans2 = mat4(vec4(1,0,0,0),vec4(0,1,0,0),vec4(0,0,1,0),vec4(0,1,0,1)); //el fem tornar al lloc

    //ve bc3 N = normalize(normalMatrix * mat3(trans) * mat3(rot) * mat3(trans) * normal);
    frontColor = vec4(color,1.0); // no iluminació!!! * N.z;
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * trans2 * rot * trans1 * vec4(vertex, 1.0);
}
