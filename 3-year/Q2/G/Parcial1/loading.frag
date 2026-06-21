#version 330 core

in vec4 frontColor;
in vec3 vert;
in vec3 norm;
out vec4 fragColor;

uniform mat3 normalMatrix;

uniform float time;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;
uniform float period = 10.0;
uniform float cellSize = 0.2;
uniform float gridThreshold = 0.1;
uniform sampler2D noise;
const float PI = 3.1415;


void main()
{
    vec4 C;
    float time2 = mod(time, period);
    vec3 N = normalize(normalMatrix * norm);
    vec4 lcolor = vec4(0.75, 0.75, 0.99, 1.0) * (0.9 + 0.1 * N.z);

    vec4 pcolor = vec4(0.5,0.5,1.0,1.0);

    float t = time2 / period;
    float llindar = mix(boundingBoxMin.y, boundingBoxMax.y, t);

    vec2 uv = vec2(12.0 * (atan(vert.z, vert.x) + PI)/(2.0 * PI),
                   2.0 * (vert.y - boundingBoxMin.y) / (boundingBoxMax.y - boundingBoxMin.y));
    llindar += texture(noise, uv).r * 0.1 * (boundingBoxMax.y - boundingBoxMin.y);

    if (vert.y < llindar) C = lcolor;
    else C = pcolor;

    fragColor = C * N.z;
}
