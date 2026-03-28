#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D fons;
uniform sampler2D noise1;
uniform float time;

void main()
{
    vec2 vtexCoordNoise = vec2(vtexCoord.s + 0.08*time, vtexCoord.t + 0.07*time);
    vec4 colNoise = texture(noise1, vtexCoordNoise);

    vec2 vtexCoordFons = vtexCoord + colNoise.rg * vec2(.003, -.005);
    fragColor = texture(fons, vtexCoordFons);
}
