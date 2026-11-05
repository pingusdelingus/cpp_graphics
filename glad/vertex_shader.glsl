#version 410 core
in vec4 vPosition;
uniform float dummy;
uniform float theta;
uniform vec4 translation;
// vertex shdr

// xnew = xcos - ysin
// ynew = ysin + ycos

void
main()
{
    float s = sin(theta);
    float c = cos(theta);

    gl_Position = translation + vec4(vPosition.x * c - vPosition.y* s, vPosition.x * s + vPosition.y * c, 0.5, 1.0);
    gl_Position = vPosition;
}// end of main
