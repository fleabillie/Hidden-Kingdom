#pragma once

#include "ofMain.h"
#include "ofxAutoControlPanel.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "scanDataPlayer.h"
#include "ofx3dGraphics.h"

class DepthVisualizerInput {
	
public: 
	
	
	class ofxKinectHack : public ofxKinect {
	public:
		ofPixels dummy;
		ofPixels& getPixelsRef() {
			return dummy;
		}
	};
	
	// you can get  3  things from this class
	
	// 1) grayscale depth image
	ofxCvGrayscaleImage depthImage;
	
	// 2) point cloud of projected points'
	vector<ofPoint> pointCloud;
	
	// 3) same as above, but structured as a grid
	//    empty points are (0,0,0)
	ofxVec3f pointGrid[480][640];
	
	int camWidth, camHeight;
	float rawFarThreshold, rawNearThreshold;
	
	ofxKinectHack kinect;
	scanDataPlayer animation;
	
	ofxControlPanel* panel;
	void setup(ofxControlPanel& panel);
	bool update(); // returns true if this is a new frame
	void drawDebug();
	void drawOrthographic();
	void drawPerspective();
	
	bool usingKinect();
	void exit();
	
protected:
	
	void thresholdDepthImage();
	void buildPointCloud();
	
};