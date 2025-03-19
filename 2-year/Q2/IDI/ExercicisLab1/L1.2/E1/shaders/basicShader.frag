#version 330 core

out vec4 FragColor;

void main() {
    FragColor = vec4(0, 0, 0, 1);
    //meitat esquerra
    if (gl_FragCoord.x < 354.) {
        if (gl_FragCoord.y < 354.) {
            FragColor = vec4(1.,1.,0.,1); // groc
        }
        else {
            FragColor = vec4(1.,0.,0.,1); // red
        }
    }
    //meitat dreta
    else {
        if (gl_FragCoord.y < 354.) {
            FragColor = vec4(0.,1.,0.,1); // green
        }
        else {
            FragColor = vec4(0.,0.,1.,1); // blue
        }
    }
}

