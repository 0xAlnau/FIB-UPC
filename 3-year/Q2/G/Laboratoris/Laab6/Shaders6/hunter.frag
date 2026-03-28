#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform vec2 mousePosition;
uniform vec2 viewport;
uniform sampler2D jungla;
uniform float magnific = 3;

vec4 blurImage( in vec2 coords )
{
    float Pi = 6.28318530718; // Pi*2
    float Directions = 16.0; // BLUR DIRECTIONS (Default 16.0 - More is better but slower)
    float Quality = 8.0; // BLUR QUALITY (Default 4.0 - More is better but slower)
    float Size = 10.0; // BLUR SIZE (Radius)
   
    vec2 Radius = Size/viewport;

    vec4 Color = texture(jungla, coords);
    for( float d=0.0; d<Pi; d+=Pi/Directions)
    {
        float cd = cos(d);
        float sd = sin(d);
		for(float i=1.0/Quality; i<=1.0; i+=1.0/Quality)
        {
			Color += texture(jungla, coords+vec2(cd,sd)*Radius*i);		
        }
    }
    
    // Output to screen
    Color /= Quality * Directions - 15.0;
    return  Color;
}

void main()
{
    float xRat = mousePosition.x / viewport.x;
    float yRat = mousePosition.y / viewport.y;

    float textXpixel_X = 1.0 / viewport.x;
    float textXpixel_Y = 1.0 / viewport.y;

    float de = distance(vtexCoord, vec2(xRat - (80.0*textXpixel_X), yRat));

    float dd = distance(vtexCoord, vec2(xRat + (80.0*textXpixel_X), yRat));


    if (step(textXpixel_X*105.0,de) == 0.0 || step(textXpixel_X*105.0,dd) == 0.0) {
        vec2 mouseTex = mousePosition / viewport; //[0,1]
        vec2 P = mouseTex + (vtexCoord - mouseTex) / magnific; //usant igualtat, i mirant dist com restes
        vec4 possibleColor = texture(jungla, P);

        if (step(textXpixel_X*100.0,de) == 0.0) fragColor = possibleColor;
        else if (step(textXpixel_X*100.0,dd) == 0.0) fragColor = possibleColor;
        else fragColor = vec4(vec3(0.0), 1.0);
    }
    else fragColor = blurImage(vtexCoord);

}

//dist(F,M) = magnific * dist(P,M)
