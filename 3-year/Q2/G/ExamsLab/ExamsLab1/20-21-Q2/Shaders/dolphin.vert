#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float time;
uniform vec3 boundingBoxMax;
uniform vec3 boundingBoxMin;

const float PI = 3.1416;
const float f = 1.0; // en Hz
const float Ad = PI / 32.0;
const float Ar = PI / 4.0;

void main()
{
    float angleR = Ar * sin(2*PI*f*time);
    if (angleR > 0) angleR = 0.0;
    float angleD = -Ad * sin(2*PI*f*(time + 0.25));

    mat4 rotRT = mat4(vec4(1.0, 0.0, 0.0, 0.0), vec4(0.0, cos(angleR), sin(angleR), 0.0), vec4(0.0, -sin(angleR), cos(angleR), 0.0), vec4(0.0,0.0,0.0,1.0));
    mat4 rotRD = mat4(vec4(1.0, 0.0, 0.0, 0.0), vec4(0.0, cos(angleD), sin(angleD), 0.0), vec4(0.0, -sin(angleD), cos(angleD), 0.0), vec4(0.0,0.0,0.0,1.0));

    vec3 v = vertex;

    // cálculo correcto de la longitud y el porcentaje vY
    float lengthY = boundingBoxMax.y - boundingBoxMin.y;
    float vY = (v.y - boundingBoxMin.y) / lengthY;

    //pivots
    float pivotRT = boundingBoxMin.y + 0.35 * lengthY;
    float pivotRD = boundingBoxMin.y + 0.65 * lengthY;

    if (vY <= 0.5) {
        v.y -= pivotRT;
        v = (rotRT * vec4(v, 1.0)).xyz;
        v.y += pivotRT;

        // 3. Smoothstep ordenado e invertido
        float pes = 1.0 - smoothstep(0.05, 0.5, vY);
        v = mix(vertex, v, pes);
    }
    else {
        v.y -= pivotRD;
        v = (rotRD * vec4(v, 1.0)).xyz;
        v.y += pivotRD;

        // El delantero ya estaba en el orden correcto
        float pes = smoothstep(0.55, 0.75, vY);
        v = mix(vertex, v, pes);
    }

    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(vec3(0.8) * N.z, 1.0);
    gl_Position = modelViewProjectionMatrix * vec4(v, 1.0);
}
