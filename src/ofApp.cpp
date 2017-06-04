#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    mesh1 = ofMesh::sphere(50);
    
    cout<<mesh1.getNumVertices()<<endl;
    cout<<mesh2.getNumVertices()<<endl;

    mesh1.setMode(OF_PRIMITIVE_POINTS);
    mesh2.setMode(OF_PRIMITIVE_POINTS);

    float range = 20;
    
    for(int i = 0; i < NUM_POINTS; i++) {
        float x = ofRandom(range*2, range*4);
        float y = ofRandom(-range, range);
        float z = ofRandom(-range, range);
        
        mesh2.addVertex(ofVec3f(x, y, z));
        mesh2.addColor(ofColor(255, 255, 0));
    }
    
    orderedPoints1 = setOrderedPoints(mesh1);
    orderedPoints2 = setOrderedPoints(mesh2);

    cout<<"Points1: "<<endl;
    for(int i = 0; i < mesh1.getNumVertices(); i++) {
        //cout<<orderedPoints[i].x<<endl;
        float r = ofMap(orderedPoints1[i].x, 0, 1, 0, 255);
        float g = ofMap(orderedPoints1[i].y, 0, 1, 0, 255);
        float b = ofMap(orderedPoints1[i].z, 0, 1, 0, 255);
        
        cout<<orderedPoints1[i].x<<endl;

        mesh1.addColor(ofColor(r, g, b));
    }
    
    cout<<"Points2: "<<endl;
    
    for(int i = 0; i < mesh2.getNumVertices(); i++) {
        //cout<<orderedPoints[i].x<<endl;
        float r = ofMap(orderedPoints2[i].x, 0, 1, 0, 255);
        float g = ofMap(orderedPoints2[i].y, 0, 1, 0, 255);
        float b = ofMap(orderedPoints2[i].z, 0, 1, 0, 255);
        
        cout<<orderedPoints2[i].x<<endl;

        
        mesh2.setColor(i, ofColor(r, g, b));
    }
    
    nearestIndicies.resize(NUM_POINTS);
    
    for(int i = 0; i < NUM_POINTS; i++) {
        nearestIndicies[i] = findNearestPoint(i, orderedPoints2, orderedPoints1);
    }
    
    ofBackground(0);
}

struct {
    bool operator()(pair<int, float> a, pair<int, float> b) const {
        return a.second > b.second;
    }
} customGreater;

vector<ofVec3f> ofApp::setOrderedPoints(ofMesh mesh) {
    int size = mesh.getNumVertices();
    vector<ofVec3f> points;
    points.resize(size);
    
    vector< pair<int, float> > xValues;
    xValues.resize(size);
    vector< pair<int, float> > yValues;
    yValues.resize(size);
    vector< pair<int, float> > zValues;
    zValues.resize(size);

    for(int i = 0; i < size; i++) {
        xValues[i].second = mesh.getVertex(i).x;
        xValues[i].first = i;
        yValues[i].second = mesh.getVertex(i).y;
        yValues[i].first = i;
        zValues[i].second = mesh.getVertex(i).z;
        zValues[i].first = i;
    }
    
    std::sort(xValues.begin(), xValues.end(), customGreater);
    std::sort(yValues.begin(), yValues.end(), customGreater);
    std::sort(zValues.begin(), zValues.end(), customGreater);

    for(int i = 0; i < size; i++) {
        xValues[i].second = i;
        yValues[i].second = i;
        zValues[i].second = i;
    }
    for(int i = 0; i < size; i++) {
        points[xValues[i].first].x = (float)xValues[i].second / (float)size;
        points[yValues[i].first].y = (float)yValues[i].second / (float)size;
        points[zValues[i].first].z = (float)zValues[i].second / (float)size;
    }
    
    return points;
}

int ofApp::findNearestPoint(int index, vector<ofVec3f> a, vector<ofVec3f> b) {
    ofVec3f point = a[index];
    float minDist = 1000;
    int minIndex;
    for(int i = 0; i < b.size(); i++) {
        float dist = (point - b[i]).length();
        if(dist < minDist) {
            minDist = dist;
            minIndex = i;
        }
    }
    return minIndex;
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i = 0; i < NUM_POINTS; i++) {
        ofVec3f tar = mesh1.getVertex(nearestIndicies[i]);
        ofVec3f point = mesh2.getVertex(i);
        
        float x = ofLerp(point.x, tar.x, 0.01);
        float y = ofLerp(point.y, tar.y, 0.01);
        float z = ofLerp(point.z, tar.z, 0.01);

        mesh2.setVertex(i, ofVec3f(x, y, z));
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    mesh1.draw();
    mesh2.draw();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
