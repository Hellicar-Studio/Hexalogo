//
//  HexGrid.h
//  hexagonsSpread
//
//  Created by James Bentley on 6/20/17.
//
//

#pragma once

#include "ofMain.h"
#include "Hexagon.h"

class HexGrid {
public:
    // Constructor
    HexGrid();
    // Functionality
    void draw();
    // Setters
    void setPosition(ofVec2f val) { pos = val; };
    void setPosition(float x, float y) { setPosition(ofVec2f(x, y)); };
    void setSize(float val) { size = val; };
    void setSpacing(float val) { spacing = val; };
    // Getters
    ofVec2f getPosition() { return pos; };
    float getSize() { return size; };
private:
    vector<Hexagon*> hexs;
    float size;
    float spacing;
    ofVec2f pos;
};

