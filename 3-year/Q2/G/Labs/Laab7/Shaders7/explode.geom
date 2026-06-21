#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 vnormal[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform float time;

const float speed = 0.5;

void main( void )
{
	vec3 promigN = vec3(0.0);
	for (int i = 0; i < vnormal.length(); ++i) promigN += vnormal[i];
	promigN = promigN / vnormal.length();
	vec4 transla = vec4(speed*time*promigN, 0.0);

	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * (gl_in[i].gl_Position + transla);
		EmitVertex();
	}
    EndPrimitive();
}
