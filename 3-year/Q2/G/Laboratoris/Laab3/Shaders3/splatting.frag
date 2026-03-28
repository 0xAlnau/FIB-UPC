#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D noise0;
uniform sampler2D rock1;
uniform sampler2D grass2;

void main()
{
    vec4 color_noise = texture(noise0, vtexCoord);
    vec4 color_rock = texture(rock1, vtexCoord);
    vec4 color_grass = texture(grass2, vtexCoord);

    vec4 color_final = mix(color_rock, color_grass, color_noise.r);

    fragColor = color_final;
}
