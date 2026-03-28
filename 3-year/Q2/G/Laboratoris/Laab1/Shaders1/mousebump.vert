#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

uniform int test = 0;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;
uniform vec2 mousePosition;
uniform float radius = 300;
uniform vec2 viewport;

vec2 getMousePositionWindowSpace() {
    if(test == 0) return mousePosition;
    if(test == 1) return vec2(400,520);
    if(test == 2) return vec2(600,225);
    if(test == 3) return vec2(200,375);
    return vec2(400,300);
}

void main()
{
    float t;
    //                     (4)                  (4)                (4)                  (3)                 (2)
    //object -- MT --> world space -- VT --> eye space -- PT --> Cliping -- dividir --> NDC -- formula --> window :)
    vec4 P_clip = modelViewProjectionMatrix * vec4(vertex, 1.0); //obtenim clipping
    vec3 P_ndc = P_clip.xyz / P_clip.w; //obtenim normalitzades de dispositiu
    vec2 P_win = ((P_ndc.xy + 1) / 2) * viewport; //obtenim window

    vec2 rat = getMousePositionWindowSpace();
    float d = distance(P_win, rat);

    t = smoothstep(0.8*radius, 0.05*radius, d); //smoothstep entre valors

    vec3 N = normalize(normalMatrix * normal);
    vec3 Peye = (modelViewMatrix * vec4(vertex,1)).xyz;

    vec3 vertexPprim = Peye + (N * 0.03 * distance(boundingBoxMax, boundingBoxMin));
    vec3 vertexFin = mix(Peye,vertexPprim,t);

    vec3 colorNou = mix(vec3(1,1,1), vec3(1,0,0), t);
    frontColor = vec4(colorNou,1.0) * N.z;
    vtexCoord = texCoord;
    gl_Position = projectionMatrix * vec4(vertexFin, 1.0);
}
