#version 330 core

in vec4 frontColor;

in vec3 v;
in vec3 n;

out vec4 fragColor;


uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition;

 // (sempre estarà en eye space)
uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

uniform bool world;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

vec4 light(vec3 N, vec3 V, vec3 L)
{
    N = normalize(N); V = normalize(V); L = normalize(L);
    vec3 R = normalize( 2.0*dot(N,L)*N-L );
    float NdotL = max( 0.0, dot( N,L ) );
    float RdotV = max( 0.0, dot( R,V ) );
    float Idiff = NdotL;
    float Ispec = 0;
    if (NdotL>0) Ispec = pow( RdotV, matShininess );
    return
    	matAmbient  * lightAmbient +
    	matDiffuse  * lightDiffuse  * Idiff +
    	matSpecular * lightSpecular * Ispec; 
}

void main()
{
    vec4 colorLlum;
    
    if (!world)
    {
    	vec3 P_eye = vec3(modelViewMatrix * vec4(v,1.0)).xyz;
    	vec3 N = normalMatrix * n;
    	vec3 V = -P_eye;
    	vec3 L = -P_eye;
    	colorLlum = light(N, V, L);
    }
    
    else //world space
    {
    	vec3 P_wor = (modelMatrix * vec4(v,1.0)).xyz;
    	vec3 obs_wor = vec3(inverse(viewMatrix)[3]); //poscio cam es a la 4 columna de la inversa
    	vec3 N = mat3(modelMatrix) * n;
    	vec3 V = obs_wor-P_wor;
    	vec3 L = obs_wor-P_wor;
    	colorLlum = light(N, V, L);    
    }
    
    fragColor = colorLlum;
}
