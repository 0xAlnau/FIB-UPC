#version 330 core

in vec4 gfrontColor;
in vec4 isAmunt;
in vec2 gtexCoord;
out vec4 fragColor;

uniform sampler2D lego;

void main()
{
    if (isAmunt.x <= 1.0) { //cal fer això per error com flotant
        fragColor = gfrontColor * texture(lego, gtexCoord);
    }
    else fragColor = gfrontColor;
}
