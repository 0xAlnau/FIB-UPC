#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 vnormal[];
out vec3 gnormal;

uniform mat4 modelViewProjectionMatrix;
uniform float d = 1.0;

void main( void )
{
	vec3 N = (vnormal[0] + vnormal[1] + vnormal[2]) / 3.0;
	N = normalize(N);

	//amunt
	vec4 cara0[3];
	cara0[0] = gl_in[0].gl_Position + vec4(d*N, 0.0);
	cara0[1] = gl_in[1].gl_Position + vec4(d*N, 0.0);
	cara0[2] = gl_in[2].gl_Position + vec4(d*N, 0.0);

	//abaix
	vec4 cara1[3];
	cara1[0] = gl_in[0].gl_Position;
	cara1[1] = gl_in[1].gl_Position;
	cara1[2] = gl_in[2].gl_Position;

	//esq
	vec4 cara2[4];
	cara2[0] = gl_in[0].gl_Position;
	cara2[1] = gl_in[2].gl_Position;
	cara2[2] = gl_in[0].gl_Position + vec4(d*N, 0.0);
	cara2[3] = gl_in[2].gl_Position + vec4(d*N, 0.0);

	//dre
	vec4 cara3[4];
	cara3[0] = gl_in[0].gl_Position;
	cara3[1] = gl_in[1].gl_Position;
	cara3[2] = gl_in[0].gl_Position + vec4(d*N, 0.0);
	cara3[3] = gl_in[1].gl_Position + vec4(d*N, 0.0);

	//back
	vec4 cara4[4];
	cara4[0] = gl_in[2].gl_Position;
	cara4[1] = gl_in[1].gl_Position;
	cara4[2] = gl_in[2].gl_Position + vec4(d*N, 0.0);
	cara4[3] = gl_in[1].gl_Position + vec4(d*N, 0.0);


	for( int i = 0 ; i < 3 ; i++ )
	{
		gnormal = N;
		gl_Position = modelViewProjectionMatrix * cara0[i];
		EmitVertex();
	}
    EndPrimitive();

	for( int i = 0 ; i < 3 ; i++ )
	{
		gnormal = -N;
		gl_Position = modelViewProjectionMatrix * cara1[i];
		EmitVertex();
	}
	EndPrimitive();

	for( int i = 0 ; i < 4 ; i++ )
	{
		gnormal = normalize(cross(cara2[0].xyz - cara2[1].xyz, N));
		gl_Position = modelViewProjectionMatrix * cara2[i];
		EmitVertex();
	}
	EndPrimitive();

	for( int i = 0 ; i < 4 ; i++ )
	{
		gnormal = normalize(cross(cara3[1].xyz - cara3[0].xyz, N));
		gl_Position = modelViewProjectionMatrix * cara3[i];
		EmitVertex();
	}
	EndPrimitive();

	for( int i = 0 ; i < 4 ; i++ )
	{
		gnormal = normalize(cross(cara4[0].xyz - cara4[1].xyz, N));
		gl_Position = modelViewProjectionMatrix * cara4[i];
		EmitVertex();
	}
	EndPrimitive();
}
