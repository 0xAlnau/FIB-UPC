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
    float f_sca = 0.5 + abs( sin(time) );
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;

    vec4 P_clip = modelViewProjectionMatrix * vec4(vertex, 1.0);
    vec3 P_ndc = P_clip.xyz / P_clip.w;

    mat4 sca = mat4(vec4(f_sca,0,0,0),vec4(0,f_sca,0,0),vec4(0,0,1,0),vec4(0,0,0,1));

    gl_Position = sca * vec4(P_ndc, 1.0);
}
