#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
in vec3 norm;
out vec4 fragColor;

uniform sampler2D colormap;
uniform mat3 normalMatrix;

vec2 C1 = vec2(0.34, 0.65);
vec2 C2 = vec2(0.66, 0.65);
const float r = 0.05;

void main()
{
    vec3 N = normalize(normalMatrix * norm);
    C1 = C1 - vec2(0.1*N.xy);
    C2 = C2 - vec2(0.1*N.xy);
    float d1 = distance(vtexCoord, C1);
    float d2 = distance(vtexCoord, C2);

    vec4 colour;
    if (step(r, d1) == 0.0) colour = vec4(vec3(0.0), 1.0);
    else if (step(r, d2) == 0.0) colour = vec4(vec3(0.0), 1.0);
    else colour = texture(colormap, vtexCoord);
    fragColor = colour;
}
