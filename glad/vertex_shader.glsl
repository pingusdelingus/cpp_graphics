#version 410 core
in vec4 vPosition;
uniform float dummy;
// vertex shdr
void
main()
{
    if (dummy != 0.0)
      gl_Position = vPosition;
    else
      gl_Position = -vPosition;
}// end of main
