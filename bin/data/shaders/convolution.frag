#version 150

// this is how we receive the texture
uniform sampler2DRect cam;
uniform mat3x3 convolution;

uniform float samplingOffset;

in highp vec2 varyingtexcoord;
out vec4 outputColor;



void main(){
    
    outputColor = texture(cam, varyingtexcoord);
    
    vec4 accum = vec4(0,0,0,0);
    
    accum += texture(cam, varyingtexcoord + vec2(-1,-1) * samplingOffset) * convolution[0][0];
    accum += texture(cam, varyingtexcoord + vec2(-1,0) * samplingOffset) * convolution[0][1];
    accum += texture(cam, varyingtexcoord + vec2(-1,1) * samplingOffset) * convolution[0][2];
    
    
    accum += texture(cam, varyingtexcoord + vec2(0,-1) * samplingOffset) * convolution[1][0];
    accum += texture(cam, varyingtexcoord + vec2(0,0) * samplingOffset) * convolution[1][1];
    accum += texture(cam, varyingtexcoord + vec2(0,1) * samplingOffset) * convolution[1][2];
    
    
    accum += texture(cam, varyingtexcoord + vec2(1,-1) * samplingOffset) * convolution[2][0];
    accum += texture(cam, varyingtexcoord + vec2(1,0) * samplingOffset) * convolution[2][1];
    accum += texture(cam, varyingtexcoord + vec2(1,1) * samplingOffset) * convolution[2][2];
    
    //outputColor = accum;
    
}