#version 120

varying vec4 globalColor;

// the time value is passed into the shader by the OF app.
uniform float scanlineY;
uniform float scanlineH;
uniform float scanlineMaxOffset;

void main()
{
    vec4 position = ftransform();
    
    float displacementX = 0;
    
    
    //only fucks with it if it is within range of the scan line
    
    //top
    if (position.y < scanlineY + scanlineH && position.y >= scanlineY){
        float prc = 1.0 - ((position.y - scanlineY) / scanlineH);
        displacementX = ( scanlineMaxOffset * prc);
    }
    
    //bottom
    if (position.y > scanlineY - scanlineH && position.y <= scanlineY){
        float prc = 1.0  - ((scanlineY - position.y) / scanlineH);
        displacementX = scanlineMaxOffset * prc;
    }
    

    
    vec4 modifiedPosition = position;
	modifiedPosition.x += displacementX;
    gl_Position = modifiedPosition;
    
    // in OpenGL 2.0 we must get the global color using the gl_Color command,
    // and store it in a globalColor (varying) that is passed to our frag shader.
    // please note that the frag shader also has a globalColor (varying),
    // and this is the standard way of passing data from the vertex shader to the frag shader.
    globalColor = gl_Color;
}