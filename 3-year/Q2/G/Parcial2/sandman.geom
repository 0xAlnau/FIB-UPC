#version 330 core
        
layout(triangles) in;
layout(points, max_vertices = 1) out;

in vec3 n[];
out float noise;

uniform float time;
uniform float speed = 1.0;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;

void main( void )
{
	vec3 v0 = gl_in[0].gl_Position.xyz;
	vec3 v1 = gl_in[1].gl_Position.xyz;
	vec3 v2 = gl_in[2].gl_Position.xyz;
	vec3 baricentre = (v0 + v1 + v2) / 3.0;

	vec3 n0 = n[0];
	vec3 n1 = n[1];
	vec3 n2 = n[2];
	vec3 normal = (n0 + n1 + n2) / 3.0;
	normal = normalize(normal);

	noise = fract(sin(dot(baricentre,normal)) * 100);

	float t = fract(time * 0.2 * speed + noise);
	float factor = smoothstep(0.1, 0.9, t);

	float y = mix(baricentre.y, boundingBoxMin.y, factor);

	float diagonal = distance(boundingBoxMin, boundingBoxMax);
	float x = mix(baricentre.x, baricentre.x + diagonal*0.05, factor);
	float z = mix(baricentre.z, baricentre.z + diagonal*0.05, factor);

	gl_Position = modelViewMatrix * vec4(x, y, z, 1.0);
	EmitVertex();

    EndPrimitive();
}
