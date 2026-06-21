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
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * abs(N.z);

    vec4 P_clip = modelViewProjectionMatrix * vec4(vertex, 1.0);
    vec4 P_clip_zin = vec4(P_clip.xy, -1.0*P_clip.z, P_clip.w);

    vtexCoord = texCoord;
    gl_Position = P_clip_zin;
}
