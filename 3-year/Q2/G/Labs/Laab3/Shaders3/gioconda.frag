#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

uniform float time;
uniform sampler2D sampler;

void main()
{
    vec2 textureCoord;
    if (fract(time) <= 0.5) textureCoord = vtexCoord;
    else {
        vec2 offset = vec2(0.057, -0.172);
        if ((vtexCoord.s >= 0.393 - 0.025 && vtexCoord.s <= 0.393 + 0.025) && (vtexCoord.t >= 0.652 - 0.025 && vtexCoord.t <= 0.652 + 0.025)) {
            textureCoord = vtexCoord + offset;
        }
        else textureCoord = vtexCoord;
    }
    fragColor = texture(sampler, textureCoord);
}
