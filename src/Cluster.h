#pragma once

#include "ofMain.h"
#include "Ball.h"

class Cluster
{
public:
	Cluster(int x, int y, int z);
	void draw();
	void update();
	
	int m_state;	// 0=unexploded, 1-N=mid-explosion
	float m_lastHit; // when hit
	int m_bin;	// which bin the mushroom is in
	ofPoint pos;
	
	ofLight light;
	
private:
	
	vector <Ball *> balls;
	
	
};