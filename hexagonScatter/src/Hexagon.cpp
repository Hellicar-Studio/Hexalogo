//
//  Hexagon.cpp
//  hexagonsSpread
//
//  Created by James Bentley on 6/21/17.
//
//

#include "Hexagon.h"

Hexagon::Hexagon() {
    neighbors.resize(6);
    for(int i = 0; i < 6; i++) {
        neighbors[i] = nullptr;
    }
}

void Hexagon::draw() {
    float angle = angleStep + 30.0f / 180.0f * PI;
    for(int i = 0; i < 6; i++) {
        ofSetColor(cols[i]);
        ofVec2f pos2 = ofVec2f(cos(angle) * size, -sin(angle) * size);
        angle += angleStep;
        ofVec2f pos3 = ofVec2f(cos(angle) * size, -sin(angle) * size);
        ofDrawTriangle(pos, pos + pos2, pos + pos3);
    }
}

void Hexagon::drawDebug() {
    ofPushMatrix();
    ofNoFill();
    draw();
    ofSetColor(0);
    for(int i = 0; i < neighbors.size(); i++) {
        if(neighbors[i] != nullptr) {
            ofVec2f end = (neighbors[i]->getPosition() - pos) * 0.6;
            //ofDrawLine(pos, pos + end);
            ofDrawCircle(pos + end, 5);
        }
    }
    ofPopMatrix();
}

void Hexagon::setColorsCube(vector<ofColor>* _cols){
    ofColor colTop;
    ofColor colLeft;
    ofColor colRight;
    if(_cols->size() >= 3) {
        colTop = (*_cols)[0];
        colLeft = (*_cols)[1];
        colRight = (*_cols)[2];
    } else {
        cout<<"Hexagon::setColorsCube [ERROR] Not enough colors in color vector, you need at least 3, you have: "<<_cols->size()<<endl;
        return;
    }
    cols[1] = colTop;
    cols[2] = colTop;
    cols[3] = colLeft;
    cols[4] = colLeft;
    cols[5] = colRight;
    cols[0] = colRight;
}

void Hexagon::findNeighbors(vector<Hexagon*>* _hexs) {
    bool needsNeighbors = false;
    for(int i = 0; i < neighbors.size(); i++) {
        if(neighbors[i] == nullptr) {
            needsNeighbors = true;
            break;
        }
    }
    if(!needsNeighbors)
        return;
    
    float angleStep = 60.0f / 180.0f * PI;
    float angle = 0;
    int numNeighbors = 0;
    for(int i = 0; i < neighbors.size(); i++) {
        ofVec2f neighborGuess = ofVec2f(cos(angle) * (size*2 + spacing), -sin(angle) * (size*2 + spacing));
        neighborGuess = pos + neighborGuess;
        for(int j = 0; j < _hexs->size(); j++) {
            float dist = ((*_hexs)[j]->getPosition() - neighborGuess).length();
            if(dist < 2) {
                numNeighbors++;
                setNeighbor((*_hexs)[j], i);
            }
        }
        angle += angleStep;
    }
    cout<<numNeighbors<<endl;
}
