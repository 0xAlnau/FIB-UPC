#version 330 core

in vec4 gfrontColor;
in float sum;
out vec4 fragColor;

const float pi = 3.141592;

void main()
{
    vec4 col = gfrontColor;
    float factor = cos(sum * (pi / 2.0));
    fragColor = vec4(col.rgb * factor, col.a);
}
