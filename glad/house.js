var gl;
var program;
var bufferId;
var bufferId2;

var translation;
var translation2;

var canvas;


// from https://developer.mozilla.org/en-US/docs/Web/API/Element/getBoundingClientRect
function getNormalizedCoord(e)
{
    var canvasRect = canvas.getBoundingClientRect();

    var cursorX = e.clientX - canvasRect.left;
    var cursorY = e.clientY - canvasRect.top;
    var clipX = cursorX * 2 / canvas.width - 1;
    var clipY = -(cursorY * 2 / canvas.height - 1);

    return [clipX, clipY];
}


window.onload = function init()
{
    canvas = document.getElementById( "gl-canvas" );
    
    gl = canvas.getContext( "webgl2" );
    if ( !gl ) { alert( "WebGL2 isn't available" ); }

    // Four Vertices
    vertices = [
        vec2( -0.5, -0.5 ),
        vec2(  0.5, -0.5 ),
        vec2( -0.5,  0.5 ),
        vec2(  0.5,  0.5)
    ];

    // A 3D triangle

    // Step 2
    vertices2 = [

        vec3( -0.75, -0.75,  0.5 ),
        vec3(  0.75, -0.75,  0.5 ),
        vec3(  0.0,   0.25, -0.5 ),
    ];

    colors2 = [
        vec4(1.0, 0.0 ,0.0, 1.0), // Red
        vec4(0.0, 1.0 ,0.0, 1.0), // Green
        vec4(0.0, 0.0 ,1.0, 1.0), // Blue
    ];


    //  Configure WebGL
    gl.viewport( 0, 0, canvas.width, canvas.height );
    gl.clearColor( 0.0, 0.0, 0.0, 1.0 );
    
    // Compile the initial shaders and install later edits. Recompiling changes
    // only the GPU program; the vertices and translations in JavaScript keep
    // their current values.

    createWebGL2ShaderEditor({
        gl: gl,
        container: document.getElementById( "shader-editor-host" ),
        vertexSource: document.getElementById( "vertex-shader" ).textContent.trim(),
        fragmentSource: document.getElementById( "fragment-shader" ).textContent.trim(),
        onProgram: function (newProgram) {
            program = newProgram;
        }
    });
    
    // Load the data into the GPU
    bufferId2c = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, bufferId2c);
    gl.bufferData(gl.ARRAY_BUFFER, flatten(colors2), gl.STATIC_DRAW);

    bufferId2 = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, bufferId2);
    gl.bufferData(gl.ARRAY_BUFFER, flatten(vertices2), gl.STATIC_DRAW);

    bufferId = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, bufferId );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW );


    translation = vec4(0.0,0.0,0.0,0.0);
    translation2 = vec4(0.3,0.0,0.0,0.0);



    var mouseIsDown = false;
    var mouseMovedWhileDown = false;

    var downX = 0;
    var downY = 0;

    document.getElementById("z-minus").onclick = function () {
        console.log("remove z");
        translation2[2] -= 0.1
    };

    document.getElementById("z-plus").onclick = function () {
        console.log("add z");
        translation2[2] += 0.1
    };


    document.getElementById("MyButton").onclick = function () {
        console.log("You clicked My Button!");
    };


    canvas.addEventListener("mousemove", function(e) {
        if (mouseIsDown){
        var [clipX, clipY] = getNormalizedCoord(e);
            translation2[0] += clipX - downX;
            translation2[1] += clipY - downY;

            downX = clipX;
            downY = clipY;
            mouseMovedWhileDown = true;
        }else{
            mouseMovedWhileDown = false;
        }
    });


    canvas.addEventListener("mouseup", function(e) {
        mouseIsDown = false;
    });
    canvas.addEventListener("mousedown", function(e) {
        mouseIsDown = true;
        [downX, downY] = getNormalizedCoord(e);
    });


    canvas.addEventListener("click", function (e) {
        console.log("clicked");

        var [clipX, clipY] = getNormalizedCoord(e);
        console.log("X: " + clipX + " Y: " + clipY);

        if (mouseMovedWhileDown == false){
            console.log(`pushing at ${clipX}, ${clipY}`)
            vertices.push(vec2(clipX, clipY));
            gl.bindBuffer( gl.ARRAY_BUFFER, bufferId );
            gl.bufferData( gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW );
        }

    });

    render();
};


function render()
{
//    gl.clear(gl.COLOR_BUFFER_BIT);

       gl.enable(gl.DEPTH_TEST);
       gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    // Select the current program. The shader editor can replace program while
    // the application is running, so render must not rely on an earlier
    // gl.useProgram call made during initialization.
    gl.useProgram( program );

    // get indices in program
    var vPosition = gl.getAttribLocation( program, "vPosition" );
    var colorLoc = gl.getUniformLocation( program, "color" );
    var vColor = gl.getAttribLocation(program , "vColor");
    var uColorLoc = gl.getUniformLocation( program, "uColor" );
    var triColorLoc = gl.getUniformLocation( program, "triangleColor" );
    var translationLoc = gl.getUniformLocation (program ,"translation");
    var useColorLoc = gl.getUniformLocation(program , "useColor");

    var color = vec4(0.0, 1.0, 0.0, 1.0);
    var triColor = vec4(1.0, 0.0, 0.0, 1.0);
    var uColor = vec4(0.0, 0.0, 1.0, 1.0);
    gl.enableVertexAttribArray( vPosition );


    gl.uniform1i( useColorLoc, 1 );
    gl.uniform4fv(uColorLoc, flatten(color));

    // draw house
    gl.uniform4fv( colorLoc, flatten(color) );
    gl.bindBuffer( gl.ARRAY_BUFFER, bufferId );
    gl.vertexAttribPointer( vPosition, 2, gl.FLOAT, false, 0, 0 );
    gl.disableVertexAttribArray( vColor );
    gl.uniform4fv(translationLoc, flatten(translation));
    gl.drawArrays( gl.TRIANGLE_STRIP, 0, vertices.length );


    // draw triangle
    gl.uniform1i( useColorLoc, 0 );

    gl.uniform4fv( translationLoc, flatten(translation2) );
    gl.bindBuffer( gl.ARRAY_BUFFER, bufferId2 );
    gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray(vPosition);

    var blue = vec4(0.0, 0.0, 1.0, 1.0);

    gl.uniform4fv(uColorLoc, flatten(blue));
    gl.bindBuffer(gl.ARRAY_BUFFER, bufferId2c);
    gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vColor );
    gl.drawArrays( gl.TRIANGLE_STRIP, 0, vertices2.length );


    requestAnimationFrame( render );
}
