#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform int mode = 2;

void main()
{
    if (mode == 1) {
        if (frontColor.r < 0.5) fragColor = vec4(0.0);
        else fragColor = vec4(1.0);
    }
    else { //mode 2
        int x = int(gl_FragCoord.x);
        int y = int(gl_FragCoord.y);
        vec4 color = frontColor;

        if (x % 2 == 0 && y % 2 == 0) color += -0.5;
        else if (x % 2 == 0 && y % 2 != 0) color += 0.25;
        else if (x % 2 != 0 && y % 2 == 0) color += 0.0;
        else color += -0.25;

        if (color.r < 0.5) fragColor = vec4(0.0);
        else fragColor = vec4(1.0);
    }
}
