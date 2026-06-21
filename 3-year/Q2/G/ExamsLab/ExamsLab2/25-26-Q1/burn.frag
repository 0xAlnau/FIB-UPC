#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform float time;

uniform sampler2D pic;
uniform sampler2D foc1;

void main()
{
    float llindar = smoothstep(0, 1, time/20 + .2);

    vec4 col_foc = texture(foc1, vtexCoord);
    float r = col_foc.r;

    if (r < llindar) discard;
    else if (llindar < r && r < llindar + llindar*0.05) {
        fragColor = vec4(0.0);
    }
    else if (llindar + llindar*0.05 < r && r < llindar + llindar*0.15) {
        fragColor = vec4(vec3(1.0, 0.3, 0.0), 1.0);
    }
    else fragColor = texture(pic, vtexCoord);

}
