
in vec4 vPosition;
uniform float dummy;

void
main()
{
    if (dummy != 0.0)
      gl_Position = vPosition;
    else
      gl_Position = -vPosition;
}// end of main
