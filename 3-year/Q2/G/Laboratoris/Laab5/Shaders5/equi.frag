#version 330 core

in vec4 frontColor;
in vec3 v;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D panorama;
const float PI = 3.141592;

void main()
{
    float phi   = asin(v.y);
    float theta = atan(v.z, v.x);
    float s = theta / (2.0*PI);
    float t = (phi / PI) + 0.5;

    fragColor = texture(panorama, vec2(s,t));
}
