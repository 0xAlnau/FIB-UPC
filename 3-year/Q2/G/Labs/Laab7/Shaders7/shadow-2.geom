#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;
uniform mat4 modelViewProjectionMatrix;

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

	if (gl_PrimitiveIDIn == 0) {
		float R = distance(boundingBoxMin, boundingBoxMax) / 2.0;
		vec3 C = (boundingBoxMax + boundingBoxMin) / 2.0;

		vec4 triangle1[3];
		vec4 triangle2[3];
		triangle1[0] = vec4(C.x - R, boundingBoxMin.y - 0.01, C.z + R, 1.0);
		triangle1[1] = vec4(C.x - R, boundingBoxMin.y - 0.01, C.z - R, 1.0);
		triangle1[2] = vec4(C.x + R, boundingBoxMin.y - 0.01, C.z + R, 1.0);

		triangle2[0] = vec4(C.x + R, boundingBoxMin.y - 0.01, C.z - R, 1.0);
		triangle2[1] = vec4(C.x - R, boundingBoxMin.y - 0.01, C.z - R, 1.0);
		triangle2[2] = vec4(C.x + R, boundingBoxMin.y - 0.01, C.z + R, 1.0);

		for( int i = 0 ; i < 3 ; i++ )
		{
			gfrontColor = vec4(0.0,1.0,1.0,1.0);
			gl_Position = modelViewProjectionMatrix * triangle1[i];
			EmitVertex();
		}
		EndPrimitive();

		for( int i = 0 ; i < 3 ; i++ )
		{
			gfrontColor = vec4(0.0,1.0,1.0,1.0);
			gl_Position = modelViewProjectionMatrix * triangle2[i];
			EmitVertex();
		}
		EndPrimitive();
	}
}
