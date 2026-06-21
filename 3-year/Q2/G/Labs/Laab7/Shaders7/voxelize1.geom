#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform float step = 0.1;

void main( void )
{
	vec3 v0 = gl_in[0].gl_Position.xyz;
	vec3 v1 = gl_in[1].gl_Position.xyz;
	vec3 v2 = gl_in[2].gl_Position.xyz;
	vec3 baricentre = (v0 + v1 + v2) / 3.0;

	vec3 punt = step * round(baricentre / step); //cal dividir i arrodonir abans
	float ms = step / 2.0;

	vec4 cara0[4];
	vec4 cara1[4];
	vec4 cara2[4];
	vec4 cara3[4];
	vec4 cara4[4];
	vec4 cara5[4];

	//visionant el cub directament
	// cara de amunt
	cara0[0] = vec4(punt.x-ms, punt.y+ms, punt.z+ms, 1.0);
	cara0[1] = vec4(punt.x-ms, punt.y+ms, punt.z-ms, 1.0);
	cara0[2] = vec4(punt.x+ms, punt.y+ms, punt.z+ms, 1.0);
	cara0[3] = vec4(punt.x+ms, punt.y+ms, punt.z-ms, 1.0);

	//cara frontal
	cara1[0] = vec4(punt.x-ms, punt.y+ms, punt.z+ms, 1.0);
	cara1[1] = vec4(punt.x+ms, punt.y+ms, punt.z+ms, 1.0);
	cara1[2] = vec4(punt.x-ms, punt.y-ms, punt.z+ms, 1.0);
	cara1[3] = vec4(punt.x+ms, punt.y-ms, punt.z+ms, 1.0);

	//cara back
	cara2[0] = vec4(punt.x-ms, punt.y+ms, punt.z-ms, 1.0);
	cara2[1] = vec4(punt.x+ms, punt.y+ms, punt.z-ms, 1.0);
	cara2[2] = vec4(punt.x-ms, punt.y-ms, punt.z-ms, 1.0);
	cara2[3] = vec4(punt.x+ms, punt.y-ms, punt.z-ms, 1.0);

	//cara sota
	cara3[0] = vec4(punt.x-ms, punt.y-ms, punt.z-ms, 1.0);
	cara3[1] = vec4(punt.x-ms, punt.y-ms, punt.z+ms, 1.0);
	cara3[2] = vec4(punt.x+ms, punt.y-ms, punt.z-ms, 1.0);
	cara3[3] = vec4(punt.x+ms, punt.y-ms, punt.z+ms, 1.0);

	//cara esq
	cara4[0] = vec4(punt.x-ms, punt.y-ms, punt.z-ms, 1.0);
	cara4[1] = vec4(punt.x-ms, punt.y-ms, punt.z+ms, 1.0);
	cara4[2] = vec4(punt.x-ms, punt.y+ms, punt.z-ms, 1.0);
	cara4[3] = vec4(punt.x-ms, punt.y+ms, punt.z+ms, 1.0);

	//cara dre
	cara5[0] = vec4(punt.x+ms, punt.y-ms, punt.z-ms, 1.0);
	cara5[1] = vec4(punt.x+ms, punt.y-ms, punt.z+ms, 1.0);
	cara5[2] = vec4(punt.x+ms, punt.y+ms, punt.z-ms, 1.0);
	cara5[3] = vec4(punt.x+ms, punt.y+ms, punt.z+ms, 1.0);

	for( int i = 0 ; i < 4 ; i++ )
	{
		gfrontColor = vfrontColor[0];
		gl_Position = modelViewProjectionMatrix * cara0[i];
		EmitVertex();
	}
	EndPrimitive();

	for( int i = 0 ; i < 4 ; i++ )
	{
		gfrontColor = vfrontColor[0];
		gl_Position = modelViewProjectionMatrix * cara1[i];
		EmitVertex();
	}
	EndPrimitive();

	for( int i = 0 ; i < 4 ; i++ )
	{
		gfrontColor = vfrontColor[0];
		gl_Position = modelViewProjectionMatrix * cara2[i];
		EmitVertex();
	}
	EndPrimitive();

	for( int i = 0 ; i < 4 ; i++ )
	{
		gfrontColor = vfrontColor[0];
		gl_Position = modelViewProjectionMatrix * cara3[i];
		EmitVertex();
	}
	EndPrimitive();

	for( int i = 0 ; i < 4 ; i++ )
	{
		gfrontColor = vfrontColor[0];
		gl_Position = modelViewProjectionMatrix * cara4[i];
		EmitVertex();
	}
	EndPrimitive();

	for( int i = 0 ; i < 4 ; i++ )
	{
		gfrontColor = vfrontColor[0];
		gl_Position = modelViewProjectionMatrix * cara5[i];
		EmitVertex();
	}
    EndPrimitive();
}
