#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float angle = 0.5;

void main()
{
    mat4 rotY = mat4(vec4(cos(angle), 0.0, -sin(angle), 0.0), vec4(0.0,1.0,0.0,0.0), vec4(sin(angle), 0.0, cos(angle), 0.0), vec4(0.0,0.0,0.0,1.0));
    vec3 vRot = (rotY * vec4(vertex, 1.0)).xyz;

    float t = smoothstep(1.45, 1.55, vertex.y);
    vec3 v = mix(vertex, vRot, t);

    vec3 nRot = (rotY * vec4(normal, 1.0)).xyz;
    vec3 N = mix(normal, nRot, t);

    N = normalize(normalMatrix * N);
    frontColor = vec4(vec3(N.z),1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(v, 1.0);
}
