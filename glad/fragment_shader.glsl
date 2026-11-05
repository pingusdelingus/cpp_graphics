#version 410 core
out vec4 fColor;
in mat4 model2clip;
// fragment shdr
void
main()
{
    int fragX = int(gl_FragCoord.x);
    int fragY = int(gl_FragCoord.y);


    if ((fragX / 60 + fragY / 60) %2 == 1)
        fColor = vec4( 0.0, 0.0, 0.0, 1.0 );
    else{
        // r,g,b, z ?...
        fColor = vec4( 1.0, 0.0, 0.0, 1.0 );
    }
    fColor = vec4(0.0, 1.0, 0.0, 1.0);

}
