//	Test code for a project called The Hidden Kingdom
//	by Molly Schwartz
//	with many thanks for coding help from
//	Kyle McDonald, Shahar Zaks, Rune Madsen & John Schwartz
//	Using Depth Visualizer and Kinect code from the 
//  3d Sensing and & Visualization class taught by Kyle McDonald & Zach Lieberman
//	Some particle code adapted/inspired by Open Frameworks ADVANCED 3D EXAMPLE
//  Spring 2011


#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	
	ofSetFrameRate(60);
	
	numXBins = 12;
	numYBins = 1;
	numZBins = 12;
	
	binTriggerThreshold = 2;
	
	input.setup(panel);  // < -- could pass in useKinnect here?
	
	panel.setup("Control Panel", 1024-310, 5, 300, 600);
	panel.addPanel("Threshold and Scale");
	panel.addPanel("Control");
	
	panel.setWhichPanel("Threshold and Scale");
	panel.addSlider("near threshold", "nearThreshold", 255, 0, 255, true);
	panel.addSlider("far threshold", "farThreshold", 0, 0, 255, true);
	panel.addSlider("point size", "pointSize", 1, 1, 10, true);
	
	panel.setWhichPanel("Control");
	panel.addSlider("rotate y axis", "rotateY", 0, -360, 360, false);	
	panel.addToggle("auto rotate", "autoRotate", false);
	panel.addToggle("draw scene bounding frustrum", "drawSceneBox", false);
	panel.addToggle("draw debug", "drawDebug", false);
	
	if (input.usingKinect() == false){
		panel.addSlider("playback speed", "playSpeed", 0.5, -1, 1, false);
	}
	
	

	
	// set up sizes of sides of bins, choose space, divide by # of bins
	ofxVec3f gmin (-250, 30, -350);
	ofxVec3f gmax (250, 50, 150);
	ofxVec3f binSide(
					 (gmax.x - gmin.x) / numXBins,
					 (gmax.y - gmin.y) / numYBins,
					 (gmax.z - gmin.z) / numZBins);
	
	// create bins & fill bin array
	for (int x = 0; x < numXBins; x ++) {
		for (int y = 0; y < numYBins; y ++) {
			for (int z = 0; z < numZBins; z ++) {
				
				Bin b;
				
				b.m_min.x =	ofMap(x, 0, numXBins -1, gmin.x, gmax.x - binSide.x);		
				b.m_min.y =	ofMap(y, 0, numYBins -1, gmin.y, gmax.y - binSide.y);
				b.m_min.z =	ofMap(z, 0, numZBins -1, gmin.z, gmax.z - binSide.z);
				
				b.m_max.x =	ofMap(x, 0, numXBins -1, gmin.x + binSide.x, gmax.x);		
				b.m_max.y =	ofMap(y, 0, numYBins -1, gmin.y + binSide.y, gmax.y);	
				b.m_max.z =	ofMap(z, 0, numZBins -1, gmin.z + binSide.z, gmax.z);	
				
				m_bins.push_back(b);
			}
		}
	}
	
	// create mushrooms randomly in space also occupied by bins, # of mushrooms
	for (int i = 0; i <300; i++) {
		
		createMushroom(ofPoint(ofRandom(gmin.x, gmax.x), ofRandom(gmin.y, gmax.y), ofRandom(gmin.z, gmax.z)), ofRandom(1,8));
	}
	
	ring.loadImage("ring.png");
	ofBackground(30, 80, 60);
}

//--------------------------------------------------------------
void testApp::createMushroom(ofPoint mushroomcenter, float mushroomsize) {
	
	
	//Mushroom newmushroom(mushroomcenter, mushroomsize);
	Cluster newmushroom(mushroomcenter.x, mushroomcenter.y, mushroomcenter.z);
	
	for (int i=0; i < m_bins.size(); ++i)
	{
		if (m_bins[i].ContainsPoint(mushroomcenter))
		{
			newmushroom.m_bin=i;
			break;
		}
	}
	
	m_mushrooms.push_back(newmushroom);
	
}

//--------------------------------------------------------------
void testApp::update() {
	
	movementSpeed = .1;
	
	bool isFrameNew = input.update();
	
	if(isFrameNew) {
		
		// remember the previous pixel count per bin,
		// clear the current pixel count per bin
		int i, j;
		for (i=0; i < m_bins.size(); ++i)
		{
			m_bins[i].m_numpx_prev=m_bins[i].m_numpx;
			m_bins[i].m_numpx=0;
		}
		
		//point cloud 
		vector<ofPoint>& pointCloud = input.pointCloud;
		bool needsSetting = true;
		for(int i = 0; i < pointCloud.size(); i++) {
			ofPoint& cur = pointCloud[i];
			
			for (j=0; j < m_bins.size(); ++j)
			{
				if (m_bins[j].ContainsPoint(cur))
				{
					m_bins[j].m_numpx++;
					break;
				}
			}
		}
		
		for (int i=0; i < m_mushrooms.size(); i++) {
			
			if (ofGetElapsedTimef() - m_mushrooms[i].m_lastHit > .1){
				m_mushrooms[i].m_state =0; 
			}	
			
		}
		
		
		for (i=0; i < m_bins.size(); ++i)
		{
			if (m_bins[i].m_numpx > binTriggerThreshold)
			{
				for (j=0; j < m_mushrooms.size(); ++j)
				{
					if (m_mushrooms[j].m_state == 0 && // not yet exploded
						m_bins[i].ContainsPoint(m_mushrooms[j].pos))
						//m_mushrooms[j].m_bin == i  // a less verbose way to write, for still mushrooms
						
					{
						m_mushrooms[j].m_state++;	// start explosion on next update
						m_mushrooms[j].m_lastHit = ofGetElapsedTimef();
					}
				}
			}
		}
		
	}
}

//--------------------------------------------------------------
void testApp::draw() {
	
	ofEnableSmoothing();
	glEnable(GL_DEPTH_TEST);
	
	//ofSetColor(255,255,255,255);
	
	
	//cam.begin();	
	
//	
//	// draw debug or non debug
	if (panel.getValueB("drawDebug")){
		input.drawDebug();
		
	} else {
		ofPushMatrix();
		
		// center everything
		ofTranslate(ofGetWidth()/2, ofGetWidth()/2, -500);
		
		ofSetColor(5, 200, 200);
		ofRotateY(panel.getValueF("rotateY"));
		if (panel.getValueB("autoRotate")) {
			ofRotateY(ofGetElapsedTimef()*5);
		}
		
	
		ofScale(4.8,4.8,4.8); // zoom in so 1 cm = 3 pixels
		ofRotateY(-180); // make it so the scene starts out proper rotation
		
		input.drawPerspective();
		
		// draw anything else: 
		
		ofEnableLighting();
		//light.setAmbientColor(ofColor(ofRandom(5),ofRandom(18),ofRandom(12)));
		light.enable();
		//light.getIsDirectional();
		//light.setDirectional(100);
		light.setPosition(0, -200, 150);
		
		//sphere showing location of the light
//		ofFill();
//		ofSetColor(255, 255, 255);
//		ofSphere(0, -100, 100, 20);
		
		//mushrooms
		for (int j=0; j < m_mushrooms.size(); j++) {		
			m_mushrooms[j].draw();
		}
		
		ofDisableLighting();
		
		// make outlines where the bins are
		for(int i = 0; i < m_bins.size(); i++) {
			
			//ofSetColor(20,20,20,);
			ofBox(m_bins[i].m_min, m_bins[i].m_max);
		}
		
		ofPopMatrix();
		
		//cam.end();
		
		glDisable(GL_DEPTH_TEST);
		//glDisable(GL_POLYGON_SMOOTH);
	}
	
	ofEnableAlphaBlending();
	ofSetColor(255,255,255,255);
	ring.draw(0, 0, 800, 800);
	ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::exit() {
}

//--------------------------------------------------------------
void testApp::keyPressed (int key) {
	if(key == 'f') {
		ofToggleFullscreen();
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {
}

