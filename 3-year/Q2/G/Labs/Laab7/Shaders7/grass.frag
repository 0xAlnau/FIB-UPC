#version 330 core

in vec3 gnormal;
in vec4 gPos;
in vec2 gtexCoord;
out vec4 fragColor;

uniform mat3 normalMatrix;
uniform sampler2D grass_top0;
uniform sampler2D grass_side1;

void main()
{
    vec4 C;
    if (gnormal.z == 0.0) { //cara vertial
        C = texture(grass_side1, gtexCoord);
        if (C.a < 0.1) discard;
    }
    else {
        C = texture(grass_top0, 4.0*gPos.xy);
    }

    fragColor = C;
}
