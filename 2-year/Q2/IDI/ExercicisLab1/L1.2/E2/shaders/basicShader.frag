#version 330 core

out vec4 FragColor;

void main() {
    FragColor = vec4(0, 0, 0, 1);
    //meitat esquerra
    if (gl_FragCoord.x < 354.) {
        if (gl_FragCoord.y < 354.) {
            if (mod(gl_FragCoord.y,5) < 1) FragColor = vec4(1.,1.,0.,1); // groc, el if fa que com es 0.5 els pixels, doncs si es mes petit que un pinta, sino no, i el % 5 es cada 5 pixels pinto
            else discard;
        }
        else {
            if (mod(gl_FragCoord.y,5) < 1) FragColor = vec4(1.,0.,0.,1); // red
            else discard;
        }
    }
    //meitat dreta
    else {
        if (gl_FragCoord.y < 354.) {
            if (mod(gl_FragCoord.y,5) < 1) FragColor = vec4(0.,1.,0.,1); // green
            else discard;
        }
        else {
            if (mod(gl_FragCoord.y,5) < 1) FragColor = vec4(0.,0.,1.,1); // blue
            else discard;
        }
    }
}

