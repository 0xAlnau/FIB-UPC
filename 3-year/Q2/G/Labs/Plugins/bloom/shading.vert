#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 3) in vec2 texCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform sampler2D colorTexture;
uniform bool useLight;

out vec4 vFragColor;

void main()
{
	vec3 N = normalize(normalMatrix * normal);
	vFragColor = texture(colorTexture, texCoord);
	if(useLight)
	{
		vec3 L = normalize(vec3(1,1,1));
		vFragColor = vFragColor * (0.3 + max(dot(N, L), 0));
	}
	gl_Position = modelViewProjectionMatrix * vec4(vertex,1.0);
}

