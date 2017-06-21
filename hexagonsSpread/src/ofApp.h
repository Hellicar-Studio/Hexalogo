#pragma once

#include "ofMain.h"
#include "Hexagon.h"
#include "ofxXmlSettings.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        vector<Hexagon*> createNeighbors(Hexagon* root);
        void addNeighbors(vector<Hexagon*>* hexLibrary, Hexagon* root, int num = -1);

        vector<vector<ofColor>> loadPalettes(string path);
        void findAllNeighbors(vector<Hexagon*>* hexLib);
    
        void drawPalette();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        vector<Hexagon*> hexs;
    
        vector<vector<ofColor>> palettes;
    
        ofxPanel gui;
    
        ofParameter<int> palette;
        ofParameter<float> size;
        ofParameter<float> spacing;
};
