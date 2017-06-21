//
//  Hexagon.h
//  hexagonsSpread
//
//  Created by James Bentley on 6/20/17.
//
//

// Each hexagon has a position and a size as well as an array of pointers to neighboring hexagons.

#pragma once

#include "ofMain.h"

class Hexagon {
public:
    // Constructor
    Hexagon();
    // Setters
    void setPosition(ofVec2f val) { pos = val; };
    void setPosition(float x, float y) { setPosition(ofVec2f(x, y)); };
    void setColor(ofColor val) { for(int i = 0; i < 6; i++) { cols[i] = val; } };
    void setColor(float r, float g, float b) { setColor(ofColor(r, g, b)); };
    void setColorsCube(vector<ofColor>* _cols);
    void setSpacing(float val) { spacing = val; };
    void setNeighbor(Hexagon* hex, int index) { if(index < 6 && index >= 0) neighbors[index] = hex; };
    void setFilled(bool val) { filled = val; };
    void setParent(Hexagon* p) { parent = p; };
    // Getters
    void setSize(float val) { size = val; };
    ofVec2f getPosition() { return pos; };
    float getSize() { return size; };
    float getSpacing() { return spacing; };
    bool isFilled() { return filled; };
    vector<Hexagon*> getNeighbors() { return neighbors; };
    int getRealNeighbors() {
        int numNeighbors = 0;
        for(int i = 0; i < neighbors.size(); i++) {
            if(neighbors[i] != nullptr) {
                numNeighbors++;
            }
        }
        return numNeighbors;
    }
    bool needsNeighbor() {
        for(int i = 0; i < neighbors.size(); i++) {
            if(neighbors[i] == nullptr) {
                return true;
            }
        }
        return false;
    }
    
    // Functionality
    void drawFull();
    void drawEmpty();
    
    void drawDebug();
    void findNeighbors(vector<Hexagon*>* _hexs);
    
    void updatePosition();
        
private:
    ofVec2f pos;
    float size;
    float angleStep = 60.0f / 180.0f * PI;
    ofColor cols[6];
    vector<Hexagon*> neighbors;
    Hexagon* parent;
    bool filled;
    float spacing;
};


