#version 150

// these are for the programmable pipeline system and are passed in
// by default from OpenFrameworks
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;


uniform float scale;


in vec4 position;
in vec4 color;
in vec4 normal;
in vec2 texcoord;
// this is the end of the default functionality

out highp vec2 varyingtexcoord;

void main(){
    // here we move the texture coordinates
    //varyingtexcoord = texcoord;
    
    
    
				
    //varyingtexcoord = vec2(floor((texcoord - float2(.5,.5))/scale) * scale);
    
    varyingtexcoord = vec2(scale*floor((((texcoord - vec2(.5,.5))/scale)) + vec2(.5,.5))) + vec2(.5,.5);
    
    // send the vertices to the fragment shader
    gl_Position = modelViewProjectionMatrix * position;
}

