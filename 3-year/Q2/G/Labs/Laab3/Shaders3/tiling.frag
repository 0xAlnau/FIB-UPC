#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

uniform sampler2D myMap;

void main()
{
    fragColor = texture(myMap, vtexCoord);
}
