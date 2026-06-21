#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 boundingBoxMin; // cantonada de la capsa englobant
uniform vec3 boundingBoxMax; // cantonada de la capsa englobant

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;

    vec3 colorNou;
    vec3 r = vec3(1.0, 0.0, 0.0);
    vec3 y = vec3(1.0, 1.0, 0.0);
    vec3 g = vec3(0.0, 1.0, 0.0);
    vec3 c = vec3(0.0, 1.0, 1.0);
    vec3 b = vec3(0.0, 0.0, 1.0);

    float y_norm = (vertex.y - boundingBoxMin.y) / (boundingBoxMax.y - boundingBoxMin.y); //entre 0 i 1
    float pos = y_norm * 4.0;
    float t = fract(pos);

    if (vertex.y == boundingBoxMin.y) colorNou = r;
    else if (pos < 1.0) colorNou = mix(r,y,t);
    else if (pos < 2.0) colorNou = mix(y,g,t);
    else if (pos < 3.0) colorNou = mix(g,c,t);
    else if (pos < 4.0) colorNou = mix(c,b,t);
    else if (vertex.y == boundingBoxMax.y) colorNou = b;

    frontColor = vec4(colorNou,1.0);
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
