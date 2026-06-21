#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

uniform int test = 0;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;
uniform vec2 mousePosition;
uniform float radius = 300;
uniform vec2 viewport;

vec2 getMousePositionWindowSpace() {
    if (test == 0) return mousePosition;
    if (test == 1) return vec2(400,520);
    if (test == 2) return vec2(600,225);
    if (test == 3) return vec2(200,375);
    return vec2(400,300);
}

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    
    vec4 P_clipp = modelViewProjectionMatrix * vec4(vertex, 1.0);		
    vec3 P_ndc = P_clipp.xyz / P_clipp.w;
    vec2 P_wind = ((P_ndc.xy + 1) / 2) * viewport;
    vec2 Pos_rat = getMousePositionWindowSpace();
    
    float d = distance(P_wind, Pos_rat);
    float t = smoothstep(0.8*radius, 0.05*radius, d);
    
    vec3 P_obs = (modelViewMatrix * vec4(vertex,1.0)).xyz;
    vec3 P_obs_prim = P_obs + (N * 0.03 * distance(boundingBoxMax,boundingBoxMin));
    vec3 P_nou_obs = mix(P_obs,P_obs_prim,t);
    
    vec3 colorNou = mix(vec3(1.0,1.0,1.0), vec3(1.0,0.0,0.0), t);
    
    frontColor = vec4(colorNou,1.0) * N.z;
    vtexCoord = texCoord;
    gl_Position = projectionMatrix * vec4(P_nou_obs, 1.0);
}
