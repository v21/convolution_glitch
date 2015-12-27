#version 150

// this is how we receive the texture
uniform sampler2DRect cam;
uniform sampler2DRect recurse;
uniform mat3x3 convolution;

uniform float scale;
uniform float varyingSamplingOffset;
uniform float greyscale;
uniform float sourceOpacity;
in highp vec2 varyingtexcoord;
out vec4 outputColor;



void main(){
    
    
    
    vec4 cam = texture(cam, varyingtexcoord);
    
    float samplingOffset = varyingSamplingOffset * scale;
    
    vec4 accum = vec4(0,0,0,0);
    
    accum += texture(recurse, varyingtexcoord + vec2(-1,-1) * samplingOffset) * convolution[0][0];
    accum += texture(recurse, varyingtexcoord + vec2(-1,0) * samplingOffset) * convolution[0][1];
    accum += texture(recurse, varyingtexcoord + vec2(-1,1) * samplingOffset) * convolution[0][2];
    
    
    accum += texture(recurse, varyingtexcoord + vec2(0,-1) * samplingOffset) * convolution[1][0];
    accum += texture(recurse, varyingtexcoord + vec2(0,0) * samplingOffset) * convolution[1][1];
    accum += texture(recurse, varyingtexcoord + vec2(0,1) * samplingOffset) * convolution[1][2];
    
    
    accum += texture(recurse, varyingtexcoord + vec2(1,-1) * samplingOffset) * convolution[2][0];
    accum += texture(recurse, varyingtexcoord + vec2(1,0) * samplingOffset) * convolution[2][1];
    accum += texture(recurse, varyingtexcoord + vec2(1,1) * samplingOffset) * convolution[2][2];
    
    outputColor = (1 - sourceOpacity) * accum + sourceOpacity * cam;
    
    float gray = dot(outputColor.rgb, vec3(0.299, 0.587, 0.114));
    
    outputColor = (1 - greyscale) * outputColor + greyscale * gray;

    //outputColor = vec4(varyingtexcoord.r / 1024,varyingtexcoord.g /768,1,1);
    //outputColor = vec4(sourceOpacity,cam.g,0,1);
}