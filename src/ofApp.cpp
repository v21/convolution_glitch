#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //ofDisableArbTex();
    shader.load("shaders/convolution.vert","shaders/convolution.frag");
    int camWidth = 1024;
    int camHeight = 768;
    
    camera.setVerbose(true);
    camera.initGrabber(camWidth, camHeight);
    buf.allocate(1024,768);
    
    
    mesh.setMode(OF_PRIMITIVE_POINTS);
    for(int x = 0; x < 1024; x++){
        for(int y = 0; y < 768; y++){
            mesh.addVertex(ofVec3f(x,y));
            mesh.addTexCoord(ofVec2f(x-0, y-0.5)); //why -1? i don't know. but otherwise the image goes up off the screen
        }
    }

    
    
    matrix = ofMatrix3x3( 1.24767506,  -0.865139842,  1.05035031, -1.30395234, 1.92903697,  -1.21178854,  -1.07417428,  -0.191877395,  0.572679877);
    
    /*
    matrix = ofMatrix3x3( -1.359526516282074, -3.0227895803484603, -1.4459971459746497, -0.11793611496265499, 6.142406421160574, 3.0552070426861557, 0.008522988466054482, 2.2830605225302225, -1.3281742316525806);*/
}

//--------------------------------------------------------------
void ofApp::update(){
    camera.update();
    
    
    
    buf.dst->begin();
    
    shader.begin();
    
    shader.setUniformTexture("cam", camera.getTexture(), 0);
    
    shader.setUniformTexture("recurse", buf.src->getTexture(),1);
    
    
    shader.setUniformMatrix3f("convolution", matrix);
    shader.setUniform1f("varyingSamplingOffset", samplingOffset);
    
    shader.setUniform1f("sourceOpacity", sourceOpacity);
    shader.setUniform1f("greyscale", greyscale);
    
    shader.setUniform1f("scale", scale);

    
    mesh.draw();
    
    
    shader.end();
    
    
    buf.dst->end();
    
    buf.swap();

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    buf.src->draw(0,0,1024,768);

    
}



ofMatrix3x3 ofApp::genConvolveMatrix(float range)
{
    ofMatrix3x3 rand = ofMatrix3x3(ofRandomf() * range, ofRandomf() * range, ofRandomf() * range,
                                   ofRandomf() * range, ofRandomf() * range, ofRandomf() * range,
                                   ofRandomf() * range, ofRandomf() * range, ofRandomf() * range);
    
    float sum = rand[0] + rand[1] + rand[2] + rand[3] + rand[4] + rand[0] + rand[5] + rand[6] + rand[7] + rand[8];
    float adjustment = (1 - sum) / 9;
    for (int i = 0; i < 9; i++) {
        rand[i] = rand[i] + adjustment;
    };
    return rand;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'r')
    {
        
        shader.load("shaders/convolution.vert","shaders/convolution.frag");
    }
    
    if (key == 'z')
    {
        
        
        matrix = genConvolveMatrix(2);
    }
    
    if (key == '0')
    {
        
        
        matrix = ofMatrix3x3(0,0,0,0,1,0,0,0,0);
    }
    
    
    
    if (key == '1')
    {
        
        
        matrix = ofMatrix3x3(0.1,0.1,0.1,
                             0.1,0.1,0.2,
                             0.1,0.1,0.1);
    }
    
    if (key == '[')
    {
        sourceOpacity = MAX(0, sourceOpacity - 0.03);
        ofLog() << "sourceOpacity " << sourceOpacity;
    }
    
    if (key == ']')
    {
        sourceOpacity = MIN(1, sourceOpacity + 0.03);
        ofLog() << "sourceOpacity " << sourceOpacity;
    }
    
    
    if (key == 'o')
    {
        greyscale = MAX(0, greyscale - 0.03);
        ofLog() << "greyscale " << greyscale;
    }
    
    if (key == 'p')
    {
        greyscale = MIN(1, greyscale + 0.03);
        ofLog() << "greyscale " << greyscale;
    }

    
    
    if (key == 'k')
    {
        scale = MAX(1, scale - 1);
        ofLog() << "scale " << scale;
    }
    
    if (key == 'l')
    {
        scale = MIN(100, scale + 1);
        ofLog() << "scale " << scale;
    }
    
    

    

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    //samplingOffset = y / 768.0 * 10;
    //ofLog() << "samplingOffset " << samplingOffset;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
