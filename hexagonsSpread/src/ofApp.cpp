#include "ofApp.h"
//#include <Cocoa/Cocoa.h>


//--------------------------------------------------------------
void ofApp::setup(){

    ofVec2f center = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
    
    string colorPath = "/Users/james/Documents/openFrameworksNightly/apps/Hexalogo/Color Palette/Palettes.xml";
    
    palettes = loadPalettes(colorPath);
    
    hexs.clear();

    hexs.resize(1);
    
    string settingsPath = "settings/settings.xml";
    
    gui.setup(settingsPath);
    gui.add(palette.set("Palettes", 0, 0, palettes.size()-1));
    gui.add(size.set("Size", 52, 40, 58));
    gui.loadFromFile(settingsPath);
    
    hexs[0] = new Hexagon();
    hexs[0]->setSize(size);
    hexs[0]->setSpacing(spacing);
    hexs[0]->setColorsCube(&palettes[palette]);
    hexs[0]->setPosition(center);
    
    img.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
    
    index = 0;
    
    
//    NSWindow * appWindow = (NSWindow *)ofGetCocoaWindow();
//    if(appWindow) {
//        cout<<"got it!"<<endl;
//    }
    
    //1
    //7
    //19
    
    for(int i = 0; i < 7; i++) {
        addNeighbors(&hexs, hexs[i]);
    }
    for(int i = 0; i < hexs.size(); i++) {
        if(ofRandom(1) < 0.8)
            hexs[i]->setFilled(true);
    }
    
    ofBackground(0);
    ofSetLineWidth(2);
    ofHideCursor();
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i = 0; i < hexs.size(); i++) {
        hexs[i]->setSize(size);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i = 0 ; i < hexs.size(); i++) {
        hexs[i]->drawEmpty();
    }
    for(int i = 0 ; i < hexs.size(); i++) {
        if(hexs[i]->isFilled()) hexs[i]->drawFull();
    }
    
//    gui.draw();
//    drawPalette();
}

void ofApp::drawPalette() {
    ofPushMatrix();
    float width = 50;
    float height = 50;
    float x = gui.getPosition().x + gui.getWidth() + 10;
    float y = gui.getPosition().y;
    
    for(int i = 0; i < palettes[palette].size(); i++) {
        ofSetColor(palettes[palette][i]);
        ofDrawRectangle(x, y, width, height);
        x += width;
    }
    ofPopMatrix();
}

// Matching neighbor indices:
// 0 - 3
// 1 - 4
// 2 - 5

// given you are 0
// root 1 -> 2
// root 5 -> 4

// given you are 1
// root 0 -> 5
// root 2 -> 3

// given you are 2
// root 1 -> 0
// root 3 -> 4

// given you are 3
// root 2 -> 1
// root 4 -> 5

// given you are 4
// root 4 -> 1
// root 5 -> 0

// given you are 5
// root 0 -> 1
// root 4 -> 3

//--------------------------------------------------------------
vector<Hexagon*> ofApp::createNeighbors(Hexagon* root) {
    float size = root->getSize();
    float spacing = root->getSpacing();
    float angleStep = 60.0f / 180.0f * PI;
    float angle = 0;
    vector<Hexagon*> rootNeighbors = root->getNeighbors();
    ofVec2f center = root->getPosition();
    vector<Hexagon*> hexs;
    ofColor col = ofColor(ofRandom(255), ofRandom(255), 0);
    for(int i = 0; i < 6; i++) {
        if(rootNeighbors[i] == nullptr) {
            Hexagon* hex = new Hexagon();
            hex->setSize(size);
            hex->setSpacing(spacing);
            int paletteIndex = palette;
            hex->setColorsCube(&(palettes[paletteIndex]));
            ofVec2f pos = ofVec2f(cos(angle) * (size*2 + spacing), -sin(angle) * (size*2 + spacing));
            hex->setPosition(center.x + pos.x, center.y + pos.y);
            root->setNeighbor(hex, i);
            hex->setParent(root);
            hexs.push_back(hex);
        }
        angle += angleStep;
    }
    return hexs;
}

//--------------------------------------------------------------
void ofApp::addNeighbors(vector<Hexagon*>* hexLib, Hexagon* root, int num) {
    vector<Hexagon*> hexs = createNeighbors(root);
    if(num < 0 || num > hexs.size())
        hexLib->insert(hexLib->end(), hexs.begin(), hexs.end());
    else
        hexLib->insert(hexLib->end(), hexs.begin(), hexs.begin() + num);
}

//--------------------------------------------------------------
void ofApp::findAllNeighbors(vector<Hexagon*>* hexLib) {
    for(int i = 0; i < hexLib->size(); i++) {
        (*hexLib)[i]->findNeighbors(hexLib);
        cout<<(*hexLib)[i]<<endl;
    }
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
void ofApp::keyPressed(int key){
    if(key == OF_KEY_RIGHT) {
        palette++;
        palette %= palettes.size();
    } else if(key == 'c') {
        img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        img.save("img" + ofToString(index) + ".jpg");
        index++;
    } else {
        hexs.clear();
        
        hexs.resize(1);
        
        hexs[0] = new Hexagon();
        hexs[0]->setSize(50);
        hexs[0]->setSpacing(0.0);
        hexs[0]->setColorsCube(&palettes[palette]);
        hexs[0]->setPosition(ofGetWidth()/2, ofGetHeight()/2);
        
        //1
        //7
        //19
        
        for(int i = 0; i < 7; i++) {
            addNeighbors(&hexs, hexs[i]);
        }
        
        for(int i = 0; i < hexs.size(); i++) {
            if(ofRandom(1) < 0.3)
                hexs[i]->setFilled(true);
        }
    }
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
