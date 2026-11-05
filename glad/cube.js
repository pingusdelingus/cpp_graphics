class Cube
{
    constructor (gl) {
        this.verts = [ new PV(0, 0, 0, true),
                       new PV(1, 0, 0, true),
                       new PV(0, 1, 0, true),
                       new PV(1, 1, 0, true),
                       new PV(0, 0, 1, true),
                       new PV(1, 0, 1, true),
                       new PV(0, 1, 1, true),
                       new PV(1, 1, 1, true) ];
        
        this.faces = [ [0, 1, 5, 4],
                       [0, 4, 6, 2],
                       [0, 2, 3, 1],
                       [7, 3, 2, 6],
                       [7, 6, 4, 5],
                       [7, 5, 1, 3] ];
        
        this.colors = [ new PV(1, 0, 0, true),
                        new PV(0, 1, 0, true),
                        new PV(1, 1, 0, true),
                        new PV(0, 0, 1, true),
                        new PV(1, 0, 1, true),
                        new PV(0, 1, 1, true) ];
        
        this.vertex_buffer = gl.createBuffer();
        // STEP 1
        // Load this.verts into vertex_buffer
        gl.bindBuffer(gl.ARRAY_BUFFER, this.vertex_buffer);
        gl.bufferData( gl.ARRAY_BUFFER, flatten(this.verts), gl.STATIC_DRAW );


        this.element_buffers = [];
        // STEP 1
        // For each face in this.faces:
        //   Create a buffer.
        //   Push it onto this.element_buffers
        //   Load the elements of the face into that buffer
        // See square.js for the incantation.
            for (const fc of this.faces){
                    const elemBuff = gl.createBuffer();
                    this.element_buffers.push(elemBuff);

                    gl.bindBuffer( gl.ELEMENT_ARRAY_BUFFER, elemBuff );
                    gl.bufferData ( gl.ELEMENT_ARRAY_BUFFER, flattenElements( fc ) , gl.STATIC_DRAW );
            }// end of for


    }// end of constructor

    render (gl, program) {
        // STEP 2
        // Get the locations of vPosition and color in the shader programs.
        // Connect this.vertex_buffer to vPosition

        var vPositionLoc = gl.getAttribLocation (program, "vPosition");
        var colorLoc = gl.getUniformLocation(program , "color");

        gl.bindBuffer(gl.ARRAY_BUFFER, this.vertex_buffer);
        gl.vertexAttribPointer( vPositionLoc, 4, gl.FLOAT, false, 0, 0 );
        gl.enableVertexAttribArray(vPositionLoc);

        // STEP 2
        // For each face this.faces[i]:
        //   Set uniform variable color to this.colors[i].
        //   Draw the elements in this.element_buffers[i].
        for (var index = 0; index < this.faces.length; index++){
                console.assert( this.faces.length === this.colors.length );

                var cc = this.colors[index];
                gl.uniform4f(colorLoc, cc.x, cc.y, cc.z, cc.w);

                gl.bindBuffer( gl.ELEMENT_ARRAY_BUFFER, this.element_buffers[index]);
                gl.drawElements( gl.TRIANGLE_FAN, this.faces[index].length, gl.UNSIGNED_SHORT, 0 );
        }


    }// end of render
}
        
