#version 330 core
out vec4 fragColor;

uniform sampler2D colorMap;

uniform float SIZE;

const int W = 12; // filter size: 2W*2W

void main()
{
    vec2 st = (gl_FragCoord.xy - vec2(0.5)) / SIZE;
    float a = 1.0/SIZE;
    float invVarGaussian = 1.0 / (9.*W*W);
    float invStdGaussian = 1.0 / (3.0 * W);

    vec4 sum=vec4(0.0);
    float count = 0.0;
    for (int i=-W; i<W; ++i)
    for (int j=-W; j<W; ++j)
    {
    	vec2 off = vec2(i,j);
        vec4 tmp = texture(colorMap, st+a*off);
    	float w = 0.25 * invStdGaussian * exp(-0.5 * dot(off, off)*invVarGaussian);
	    sum += w*tmp;
    }
            
    fragColor = sum;
}
