#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform vec2 mousePosition;
uniform float mouseOverrideX = -1.0;
uniform vec2 viewport = vec2(800,600); // width & height


void main()
{
    float cordXmouse;
    if (mouseOverrideX < 0.0) cordXmouse = mousePosition.x;
    else cordXmouse = mouseOverrideX;

    float angle = (cordXmouse / viewport.x) * 2.0 - 1.0;
    mat4 rotY = mat4(vec4(cos(angle), 0.0, -sin(angle), 0.0), vec4(0.0,1.0,0.0,0.0), vec4(sin(angle), 0.0, cos(angle), 0.0), vec4(0.0,0.0,0.0,1.0));
    vec3 vertRot = (rotY * vec4(vertex, 1.0)).xyz;

    float t = smoothstep(1.45, 1.55, vertex.y);
    vec3 posFin = mix(vertex, vertRot, t);

    vec3 normRot = (rotY * vec4(normal, 1.0)).xyz;
    vec3 normFin = mix(normal, normRot, t);

    vec3 N = normalize(normalMatrix * normFin);
    frontColor = vec4(vec3(N.z), 1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(posFin, 1.0);
}
