#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform mat3 normalMatrix;

uniform sampler2D heightMap;
uniform float smoothness = 25.0;
const float epsilon = 1.0/128.0;

//DIFERENCIES FINITES
//amb les diferencies finites volem aproximar una derivada en punt x
//ho fem amb dos punts propers a x, que poden ser a i b
//delta de x = b -a
//derivada = f(x + b) - f(x + a) / (b - a)
//en coord (s,t) hem de tractar els punts per separat, i així obtenim el gradient!

void main()
{
    vec4 colorTex = texture(heightMap, vtexCoord);
    float Gx = (texture(heightMap, vec2(vtexCoord.s + epsilon, vtexCoord.t)).r - colorTex.r) / epsilon;
    float Gy = (texture(heightMap, vec2(vtexCoord.s, vtexCoord.t + epsilon)).r - colorTex.r) / epsilon;
    vec3 normal = normalize(vec3(-Gx, -Gy, smoothness));
    vec3 N = normalize(normalMatrix * normal);
    fragColor = vec4(N.z);
}
