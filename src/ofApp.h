#pragma once

#include "ofMain.h"

#define NUM_POINTS 325

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        vector<ofVec3f> setOrderedPoints(ofMesh mesh);
        int findNearestPoint(int i, vector<ofVec3f> a, vector<ofVec3f> b);

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
    
    ofMesh mesh1;
    ofMesh mesh2;

    
    ofEasyCam cam;
    
    vector<ofVec3f> orderedPoints1;
    vector<ofVec3f> orderedPoints2;
    
    vector<int> nearestIndicies;
		
};
