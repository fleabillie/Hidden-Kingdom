#include "Ball.h"



// a ball has position, scale and color

Ball::Ball(int x, int y, int z, int s, ofColor c)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
	scale = s;
	col = c;
}

void Ball::update()
{

	pos.x + 1;
	
}

void Ball::draw(int state)
{

	ofPushStyle();
	if (state == 0) {
		ofSetColor(col);
		
	}
	else {
		ofSetColor(255, 0, 0);
		pos.y = pos.y + ofRandom(-4,3);
	}
	ofSphere(pos, scale);
	ofPopStyle();
}

// void explode
 // do weird explosion