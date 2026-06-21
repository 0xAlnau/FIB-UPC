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
    
    if (gl_PrimitiveIDIn == 0)
    {
        vec4 caraSota[4];
        caraSota[0] = vec4(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMin.z, 1.0);
        caraSota[1] = vec4(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMax.z, 1.0);
        caraSota[2] = vec4(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMin.z, 1.0);
        caraSota[3] = vec4(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMax.z, 1.0);
        
        vec4 caraDreta[4];
        caraDreta[0] = vec4(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMin.z, 1.0);
        caraDreta[1] = vec4(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMax.z, 1.0);
        caraDreta[2] = vec4(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMin.z, 1.0);
        caraDreta[3] = vec4(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMax.z, 1.0);
        
        vec4 caraEsquerra[4];
        caraEsquerra[0] = vec4(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMin.z, 1.0);
        caraEsquerra[1] = vec4(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMax.z, 1.0);
        caraEsquerra[2] = vec4(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMin.z, 1.0);
        caraEsquerra[3] = vec4(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMax.z, 1.0);
        
        vec4 caraDarrere[4];
        caraDarrere[0] = vec4(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMin.z, 1.0);
        caraDarrere[1] = vec4(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMin.z, 1.0);
        caraDarrere[2] = vec4(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMin.z, 1.0);
        caraDarrere[3] = vec4(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMin.z, 1.0);
        
        for( int i = 0 ; i < 4 ; i++ )
        {
            gfrontColor = vec4(0.0, 1.0, 0.0, 1.0);
	    gl_Position = modelViewProjectionMatrix * caraSota[i];
	    EmitVertex();
        }
        EndPrimitive();
        
        for( int i = 0 ; i < 4 ; i++ )
        {
            gfrontColor = vec4(1.0, 0.0, 0.0, 1.0);
	    gl_Position = modelViewProjectionMatrix * caraDreta[i];
	    EmitVertex();
        }
        EndPrimitive();
        
        for( int i = 0 ; i < 4 ; i++ )
        {
            gfrontColor = vec4(1.0, 0.0, 0.0, 1.0);
	    gl_Position = modelViewProjectionMatrix * caraEsquerra[i];
	    EmitVertex();
        }
        EndPrimitive();
        
        for( int i = 0 ; i < 4 ; i++ )
        {
            gfrontColor = vec4(0.0, 0.0, 1.0, 1.0);
	    gl_Position = modelViewProjectionMatrix * caraDarrere[i];
	    EmitVertex();
        }
        EndPrimitive();
    }
}
