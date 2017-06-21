#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    string colorPath = "/Users/james/Documents/openFrameworksNightly/apps/Roche_OneEurope/Color Palette/Palettes.xml";
    
    palettes = loadPalettes(colorPath);
    
    float x = 0;
    float y = ofGetHeight() / 2;
    
    float numPoints;
    
    for(int i = 0; i < 9; i++) {
        
    }

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
vector<vector<ofColor>> ofApp::loadPalettes(string path) {
    vector<vector<ofColor>> palettes;
    
    ofxXmlSettings settings;
    bool loaded = settings.load(path);
    int numPalettes = settings.getNumTags("Palette");
    palettes.resize(numPalettes);
    for(int i = 0; i < numPalettes; i++) {
        settings.pushTag("Palette", i);
        int numColors = settings.getNumTags("Color");
        for(int j = 0; j < numColors; j++) {
            string colorString = settings.getValue("Color", "255 255 255", j);
            vector<string> colorValues = ofSplitString(colorString, " ");
            int r = std::stoi(colorValues[0]);
            int g = std::stoi(colorValues[1]);
            int b = std::stoi(colorValues[2]);
            ofColor col = ofColor(r, g, b);
            palettes[i].push_back(col);
        }
        settings.popTag();
    }
    return palettes;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
