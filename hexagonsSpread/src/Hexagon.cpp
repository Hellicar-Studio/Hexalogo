//
//  Hexagon.cpp
//  hexagonsSpread
//
//  Created by James Bentley on 6/20/17.
//
//

#include "Hexagon.h"

Hexagon::Hexagon() {
    neighbors.resize(6);
    for(int i = 0; i < 6; i++) {
        neighbors[i] = nullptr;
    }
    parent = nullptr;
}

void Hexagon::updatePosition() {
    if(parent != nullptr) {
        ofVec2f dir = (pos - parent->getPosition()).normalize();
        pos = parent->getPosition() + dir * (size*2 + spacing);
    }
        
}

void Hexagon::drawFull() {
    ofPushStyle();
    ofFill();
    float angle = angleStep + 30.0f / 180.0f * PI;
    for(int i = 0; i < 6; i++) {
        ofSetColor(cols[i]);
        ofVec2f pos2 = ofVec2f(cos(angle) * (size+3), -sin(angle) * (size+3));
        angle += angleStep;
        ofVec2f pos3 = ofVec2f(cos(angle) * (size+3), -sin(angle) * (size+3));
        ofDrawTriangle(pos, pos + pos2, pos + pos3);
    }
    ofPopStyle();
}

void Hexagon::drawFullSVG() {
	if (svg == nullptr) {
		cout << "SVG is null!" << endl;
		return;
	}
	//svg->setOpacity(0.5);
	svg->setFillOpacity(1);
	svg->setStrokeOpacity(0);
	float angle = angleStep + 30.0f / 180.0f * PI;
	for (int i = 0; i < 6; i++) {
		string hex = RGBToHex(cols[i].r, cols[i].g, cols[i].b);
		svg->fill(hex);
		ofVec2f pos2 = ofVec2f(cos(angle) * (size), -sin(angle) * (size));
		angle += angleStep;
		ofVec2f pos3 = ofVec2f(cos(angle) * (size), -sin(angle) * (size));
		svg->beginPolygon();
		svg->vertex(pos.x, pos.y);
		svg->vertex(pos.x + pos2.x, pos.y + pos2.y);
		svg->vertex(pos.x + pos3.x, pos.y + pos3.y);
		svg->endPolygon();
		//ofDrawTriangle(pos, pos + pos2, pos + pos3);
	}
}

void Hexagon::drawEmpty() {
    ofPushStyle();
    ofNoFill();
    ofSetColor(255);
    float angle = angleStep + 30.0f / 180.0f * PI;
    for(int i = 0; i < 6; i++) {
        ofVec2f pos2 = ofVec2f(cos(angle) * size, -sin(angle) * size);
        angle += angleStep;
        ofVec2f pos3 = ofVec2f(cos(angle) * size, -sin(angle) * size);
        ofDrawTriangle(pos, pos + pos2, pos + pos3);
    }
    ofPopStyle();
}

void Hexagon::drawEmptySVG() {
	if (svg == nullptr) {
		cout << "SVG is null!" << endl;
		return;
	}
	svg->stroke("#FFFFFF", 1.0);
	svg->setFillOpacity(0);
	svg->setStrokeOpacity(1);
	svg->beginPolygon();
	float angle = angleStep + 30.0f / 180.0f * PI;
	for (int i = 0; i < 6; i++) {
		ofVec2f pos2 = ofVec2f(cos(angle) * size, -sin(angle) * size);
		angle += angleStep;
		ofVec2f pos3 = ofVec2f(cos(angle) * size, -sin(angle) * size);
		svg->vertex(pos.x + pos2.x, pos.y + pos2.y);
		svg->vertex(pos.x + pos3.x, pos.y + pos3.y);
	}
	angle = angleStep + 30.0f / 180.0f * PI;
	svg->endPolygon();
	for (int i = 0; i < 3; i++) {
		svg->beginPolygon();
		ofVec2f pos2 = ofVec2f(cos(angle) * size, -sin(angle) * size);
		ofVec2f pos3 = ofVec2f(cos(angle + PI) * size, -sin(angle + PI) * size);
		svg->vertex(pos.x + pos2.x, pos.y + pos2.y);
		svg->vertex(pos.x + pos3.x, pos.y + pos3.y);
		angle += angleStep;
		svg->endPolygon();
	}

		//svg->vertex(pos.x + pos3.x, pos.y + pos3.y);
		//svg->vertex(pos.x, pos.y);
}

void Hexagon::drawDebug() {
	ofPushStyle();
    ofNoFill();
    ofSetColor(0);
    for(int i = 0; i < neighbors.size(); i++) {
        if(neighbors[i] != nullptr) {
            ofVec2f end = (neighbors[i]->getPosition() - pos) * 0.6;
            //ofDrawLine(pos, pos + end);
            ofDrawCircle(pos + end, 5);
        }
    }
    ofPopStyle();
}

void Hexagon::setColorsCube(vector<ofColor>* _cols){
    ofColor colTop = (*_cols)[ofRandom(_cols->size())];
    ofColor colLeft = (*_cols)[ofRandom(_cols->size())];
    ofColor colRight = (*_cols)[ofRandom(_cols->size())];

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
        ofVec2f neighborGuess = ofVec2f(cos(angle) * (size*2), -sin(angle) * (size*2));
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
}

string Hexagon::RGBToHex(int r, int g, int b) {
	string result = "#";

	char rc[255];
	sprintf_s(rc, "%.2X", r);
	result += rc;

	char gc[255];
	sprintf_s(gc, "%.2X", g);
	result += gc;

	char bc[255];
	sprintf_s(bc, "%.2X", b);
	result += bc;

	return result;
}
