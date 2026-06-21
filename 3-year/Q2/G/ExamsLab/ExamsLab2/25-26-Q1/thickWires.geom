#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
out float sum;

void main( void )
{
	vec3 NDC[3];
	NDC[0] = gl_in[0].gl_Position.xyz / gl_in[0].gl_Position.w;
	NDC[1] = gl_in[1].gl_Position.xyz / gl_in[1].gl_Position.w;
	NDC[2] = gl_in[2].gl_Position.xyz / gl_in[2].gl_Position.w;

	//AB = 0 1
	//BC = 1 2
	//AC = 0 2

	vec4 quad0[4];
	vec3 n0 = NDC[0] - NDC[1];
	n0 = vec3(-n0.y, n0.x, 0.0);
	n0 = normalize(n0);
	quad0[0] = vec4(NDC[0] + 0.01*n0, 1.0);
	quad0[1] = vec4(NDC[1] + 0.01*n0, 1.0);
	quad0[2] = vec4(NDC[0] - 0.01*n0, 1.0);
	quad0[3] = vec4(NDC[1] - 0.01*n0, 1.0);

	vec4 quad1[4];
	vec3 n1 = NDC[1] - NDC[2];
	n1 = vec3(-n1.y, n1.x, 0.0);
	n1 = normalize(n1);
	quad1[0] = vec4(NDC[1] + 0.01*n1, 1.0);
	quad1[1] = vec4(NDC[2] + 0.01*n1, 1.0);
	quad1[2] = vec4(NDC[1] - 0.01*n1, 1.0);
	quad1[3] = vec4(NDC[2] - 0.01*n1, 1.0);

	vec4 quad2[4];
	vec3 n2 = NDC[0] - NDC[2];
	n2 = vec3(-n2.y, n2.x, 0.0);
	n2 = normalize(n2);
	quad2[0] = vec4(NDC[0] + 0.01*n2, 1.0);
	quad2[1] = vec4(NDC[2] + 0.01*n2, 1.0);
	quad2[2] = vec4(NDC[0] - 0.01*n2, 1.0);
	quad2[3] = vec4(NDC[2] - 0.01*n2, 1.0);

	/*
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
	*/

	//quad0
	for (int i = 0; i < 4; ++i) {
		if (i % 2 == 0) gfrontColor = vfrontColor[0];
		else gfrontColor = vfrontColor[1];

		if (i <= 1) sum = 1.0;
		else sum = -1.0;

		gl_Position = quad0[i];
		EmitVertex();
	}
	EndPrimitive();

	//quad1
	for (int i = 0; i < 4; ++i) {
		if (i % 2 == 0) gfrontColor = vfrontColor[1];
		else gfrontColor = vfrontColor[2];

		if (i <= 1) sum = 1.0;
		else sum = -1.0;

		gl_Position = quad1[i];
		EmitVertex();
	}
	EndPrimitive();

	//quad2
	for (int i = 0; i < 4; ++i) {
		if (i % 2 == 0) gfrontColor = vfrontColor[0];
		else gfrontColor = vfrontColor[2];

		if (i <= 1) sum = 1.0;
		else sum = -1.0;

		gl_Position = quad2[i];
		EmitVertex();
	}
	EndPrimitive();
}
