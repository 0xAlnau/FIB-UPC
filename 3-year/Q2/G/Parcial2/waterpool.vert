#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;
out vec3 v;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform float time;

float getHeight(vec2 p)
{
	float s1 = sin(time + 10.0 * p.x) * cos(time + 10.0 * p.y);
	float s2 = sin(-2.4*time + 27.0 * p.x) * cos(2.7 * time + 35.0 * p.y);
	float s3 = sin(2.2 * time + 66.0 * p.x) * cos(2.0 * time + 60.0 * p.y);
	return 0.04 * (s1 + s2*0.3 + s3*0.05);
}

void main()
{
    vec3 vecWorld = (modelMatrix * vec4(vertex, 1.0)).xyz;
    v = vecWorld;
    vec2 p = vec2(vecWorld.x, vecWorld.z);
    float height = getHeight(p);

    vec3 vertDesp = vec3(vecWorld.x, vecWorld.y + height, vecWorld.z);

    gl_Position = projectionMatrix * viewMatrix * vec4(vertDesp, 1.0);
}
