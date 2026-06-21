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
    mat3 rot = mat3(vec3(cos(angle),0,-sin(angle)), vec3(0,1,0), vec3(sin(angle),0,cos(angle)));
    vec3 P_prim = rot * vertex;
    
    float t = smoothstep(1.45, 1.55, vertex.y);
    vec3 posFinal = mix(vertex,P_prim,t);

    vec3 normRot = rot * normal;
    vec3 normFinal = mix(normal,normRot,t);
    
    vec3 N = normalize(normalMatrix * normFinal);
    frontColor = vec4(1.0) * N.z;
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(posFinal, 1.0);
}
