#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
out vec2 gtexCoord;

uniform vec4 lightPosition;
uniform float w = 0.3;
uniform mat4 projectionMatrix;

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gtexCoord = vec2(-1.0, -1.0);
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();

	if (gl_PrimitiveIDIn == 0) {
		vec4 clipL = projectionMatrix * lightPosition;
		vec3 NDCl  = clipL.xyz / clipL.w;
		vec4 quadrat[4];
		quadrat[0] = vec4(NDCl.x + w, NDCl.y + w, NDCl.z, 1.0);
		quadrat[1] = vec4(NDCl.x + w, NDCl.y - w, NDCl.z, 1.0);
		quadrat[2] = vec4(NDCl.x - w, NDCl.y + w, NDCl.z, 1.0);
		quadrat[3] = vec4(NDCl.x - w, NDCl.y - w, NDCl.z, 1.0);

		vec2 tex[4];
		tex[0] = vec2(1.0, 1.0);
		tex[1] = vec2(1.0, 0.0);
		tex[2] = vec2(0.0, 1.0);
		tex[3] = vec2(0.0, 0.0);

		for( int i = 0 ; i < 4 ; i++ )
		{
			gtexCoord = tex[i];
			gfrontColor = vec4(1.0, 0.0, 0.0, 1.0);
			gl_Position = quadrat[i];
			EmitVertex();
		}
		EndPrimitive();
	}
}
