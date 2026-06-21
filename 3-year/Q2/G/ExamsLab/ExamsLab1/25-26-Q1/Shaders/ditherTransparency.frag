#version 330 core

in vec4 frontColor;
in float dCam;
in float dDia;
out vec4 fragColor;

uniform float thresholdDistanceRatio = 0.25;
uniform int mode = 0;
uniform int n = 4;
uniform sampler2D ditherTexture;
uniform vec2 viewport;


void main()
{
    if (dCam <= dDia * thresholdDistanceRatio) {
        if (mode == 0) { //blocs de 2n x 2n
            if (mod(gl_FragCoord.x, n*2.0) < n && mod(gl_FragCoord.y, n*2.0) < n) discard;
            else fragColor = frontColor;
        }
        else { //dividim cada component per mida texture i multipliquem per factor
            vec2 cordText = (gl_FragCoord.xy / 256.0) * n;
            vec4 C = texture(ditherTexture, cordText);
            if (C.r <= 0.6) discard;
            else fragColor = frontColor;

        }
    }
    else fragColor = frontColor;
}
