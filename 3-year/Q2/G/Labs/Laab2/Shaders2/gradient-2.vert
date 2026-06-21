#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main()
{
    vec4 P_clip = modelViewProjectionMatrix * vec4(vertex, 1.0);
    vec3 P_ndc = P_clip.xyz / P_clip.w;

    float y_win = (P_ndc.y + 1.0) / 2;
    float t = fract(y_win * 4.0); //s'ha de mult per n intervals!

    vec3 colorNou; //aqui va de [-1,1]
    if (P_ndc.y <= -1.0) colorNou = vec3(1.0,0.0,0.0);
    else if (P_ndc.y >= 1.0) colorNou = vec3(0.0,0.0,1.0);
    else if (P_ndc.y < -0.5) colorNou = mix(vec3(1.0,0.0,0.0),vec3(1.0,1.0,0.0),t);
    else if (P_ndc.y < 0.0) colorNou = mix(vec3(1.0,1.0,0.0),vec3(0.0,1.0,0.0),t);
    else if (P_ndc.y < 0.5) colorNou = mix(vec3(0.0,1.0,0.0),vec3(0.0,1.0,1.0),t);
    else colorNou = mix(vec3(0.0,1.0,1.0),vec3(0.0,0.0,1.0),t);

    frontColor = vec4(colorNou,1.0);
    vtexCoord = texCoord;
    gl_Position = P_clip;
}
