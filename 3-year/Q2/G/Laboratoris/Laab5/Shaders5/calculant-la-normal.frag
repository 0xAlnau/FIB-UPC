#version 330 core

in vec4 frontColor;
in vec3 v;
out vec4 fragColor;

uniform mat3 normalMatrix;

void main()
{
    vec3 fromX = dFdx(v);
    vec3 fromY = dFdy(v);
    vec3 normal = cross(fromX, fromY); //producte ESCALAR
    vec3 N = normalize(normalMatrix * normal);
    fragColor = vec4(frontColor.xyz, 1.0) * N.z;
}
