#version 330 core

out vec4 FragColor;
in vec4 vertex_color;
uniform float num_referencia;

void main() {
    if (num_referencia != 2.0) FragColor = vertex_color;
    else {
        FragColor = vec4(0, 0, 0, 1);
        if (mod(gl_FragCoord.x,10) < 5 || mod(gl_FragCoord.y,10) < 5) FragColor = vertex_color; //
        else discard;
    }

}

