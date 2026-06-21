#version 330 core

in vec4 frontColor;
in vec3 P;
in vec3 N;
out vec4 fragColor;

uniform float edge0 = 0.35;
uniform float edge1 = 0.4;

void main()
{
    vec3 V = normalize(-P);
    float c = dot(normalize(N), V);

    float t = smoothstep(edge0, edge1, c);
    fragColor = vec4(vec3(t), 1.0);
}
