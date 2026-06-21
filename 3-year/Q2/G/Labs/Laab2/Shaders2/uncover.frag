#version 330 core

in vec4 frontColor;
in vec3 v;
out vec4 fragColor;

uniform float time;
uniform mat4 modelViewProjectionMatrix;

void main()
{
    vec4 P_clip = modelViewProjectionMatrix * vec4(v, 1.0); //obtenim clipping
    vec3 P_ndc = P_clip.xyz / P_clip.w; //obtenim normalitzades de dispositiu

    if (time == 0.0) discard;
    else if (time < 1.0) {
        if (P_ndc.x <= -0.5) {}
        else discard;
    }
    else if (time < 1.5) {
        if (P_ndc.x <= 0.0) {}
        else discard;
    }
    else if (time < 2.0) {
        if (P_ndc.x <= 0.5) {}
        else discard;
    }
    else {} //tot

    fragColor = frontColor;
}
