#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;

in vec4 vfrontColor[];
out vec4 gfrontColor;

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();

	for( int i = 0 ; i < 3 ; i++ )
	{
		vec4 posOmbra = vec4(gl_in[i].gl_Position.x, boundingBoxMin.y, gl_in[i].gl_Position.z, gl_in[i].gl_Position.w);
		gfrontColor = vec4(0.0);
		gl_Position = modelViewProjectionMatrix * posOmbra;
		EmitVertex();
	}
    EndPrimitive();
}
