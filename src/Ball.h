#pragma once

#include "ofMain.h"

class Ball
{
public:
	Ball(int x, int y, int z, int s, ofColor c);
	void draw(int state);
	void update();

	ofLight light;
	

private:
	ofPoint pos;
	int scale;
	ofColor col;
};