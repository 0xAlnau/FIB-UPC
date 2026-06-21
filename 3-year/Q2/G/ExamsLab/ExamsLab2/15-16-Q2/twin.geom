#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

void main( void )
{
	vec3 NDC[3];
	NDC[0] = gl_in[0].gl_Position.xyz / gl_in[0].gl_Position.w;
	NDC[1] = gl_in[1].gl_Position.xyz / gl_in[1].gl_Position.w;
	NDC[2] = gl_in[2].gl_Position.xyz / gl_in[2].gl_Position.w;

	vec4 fig1[3];
	fig1[0] = vec4(NDC[0].x + 0.5, NDC[0].y, NDC[0].z, 1.0);
	fig1[1] = vec4(NDC[1].x + 0.5, NDC[1].y, NDC[1].z, 1.0);
	fig1[2] = vec4(NDC[2].x + 0.5, NDC[2].y, NDC[2].z, 1.0);

	vec4 fig2[3];
	fig2[0] = vec4(NDC[0].x - 0.5, NDC[0].y, NDC[0].z, 1.0);
	fig2[1] = vec4(NDC[1].x - 0.5, NDC[1].y, NDC[1].z, 1.0);
	fig2[2] = vec4(NDC[2].x - 0.5, NDC[2].y, NDC[2].z, 1.0);

	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = fig1[i];
		EmitVertex();
	}
    EndPrimitive();

	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = fig2[i];
		EmitVertex();
	}
    EndPrimitive();
}
