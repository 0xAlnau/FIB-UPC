#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

uniform sampler2D explosion;
uniform sampler2D myMap;
uniform float time;

void main()
{
    float fps = 30.0;
    int frame = int(fps*time) % 48;
    
    int col = frame % 8;
    int row = frame / 6;
    
    float offsetX = float(col) * (1.0/8.0);
    float offsetY = 5.0 - float(row) * (1.0/6.0);
    
    vec2 vtexCoordNou = vec2(vtexCoord.s * (1.0/8.0) + offsetX, vtexCoord.t * (1.0/6.0) + offsetY);
    
    vec4 color = texture(explosion, vtexCoordNou); 
    fragColor = color.a * color;
}
