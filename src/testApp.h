//	Test code for a project called The Hidden Kingdom
//	by Molly Schwartz
//	with many thanks for coding help from
//	Kyle McDonald, Shahar Zaks, Rune Madsen & John Schwartz
//	Using Depth Visualizer and Kinect code from the 
//  3d Sensing and & Visualization class taught by Kyle McDonald & Zach Lieberman
//	Some particle code adapted/inspired by Open Frameworks ADVANCED 3D EXAMPLE
//  Spring 2011

#pragma once

#include "ofMain.h"
#include "Swarm.h"
#include "Cluster.h"

//#include "ofxAutoControlPanel.h"
#include "DepthVisualizerInput.h"

class testApp : public ofBaseApp {
	
	public:

		void setup();
		void update();
		void draw();
		void exit();
	
		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
	
		ofLight light; // creates a light and enables lighting
		ofEasyCam cam; // add mouse controls for camera movement
	
		ofxAutoControlPanel panel;

		ofPoint minBound, maxBound;
		ofPoint centroid;
	
		DepthVisualizerInput input;
	
		ofShader dofPoints, dofLines;
		
		// function to create mushrooms
		void createMushroom(ofPoint mushroomcenter, float mushroomsize);
	
		// class of Bins to figure out what is where in the space
		struct Bin
		{
			ofPoint m_min; // one corner
			ofPoint m_max; // opposite corner
			int m_numpx;	// how many kinekt pixels are in this bin
			int m_numpx_prev;	// how many kinekt pixels were in this bin on the prev update
			
			bool ContainsPoint(ofPoint& pt)
			{
				return (pt.x >= m_min.x &&
						pt.x < m_max.x &&
						pt.y >= m_min.y &&
						pt.y < m_max.y &&
						pt.z >= m_min.z &&
						pt.z < m_max.z);
			}
		};
		
	
		// array of the bins
		std::vector<Bin> m_bins;
		
		// class of mushrooms 
		struct Mushroom
		{
			ofPoint m_center;
			float m_size;
			int m_state;	// 0=unexploded, 1-N=mid-explosion
			float m_lastHit; // when hit
			int m_bin;	// which bin the mushroom is in
			
			Mushroom(ofPoint center, float size)
			: m_center(center), m_size(size), m_state(0)
			{}
		};
	
		// array of mushrooms
		std::vector<Cluster> m_mushrooms;
		
		int numXBins;
		int numYBins;
		int numZBins;
		int binTriggerThreshold;
	
		//my custom node
		//Swarm	nodeSwarm;
	
		float movementSpeed;
	
		ofImage bg;
		ofImage ring;
	
		private:
			void capture();
			bool doCapture;
			int framenum;
		
	
};
