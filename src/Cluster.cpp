#include "Cluster.h"


// a cluster has a random number of balls

Cluster::Cluster(int x, int y, int z)
{
	
	
	m_state = 0;
	m_lastHit = 0;
	
	pos.x = x;
	pos.y = y;
	pos.z = z;
	
	// how many balls are in each cluster, the size of the cluster is determined by variable 'ran'
	int ran = ofRandom(1, 6);
	
	for (int i = 0; i < ran; i++) 
	{
		int x = ofRandom(pos.x - 5, pos.x + 5);
		int y = ofRandom(pos.y - 9, pos.y + 9);
		int z = ofRandom(pos.z - 5, pos.z + 5);
		int scale = ofRandom(2, 7);
		ofColor c;
//		c.r = ofRandom(60.0f, 160.0f);
//		c.g = ofRandom(110.0f, 110.0f);
//		c.b = ofRandom(50.0f);
		
		c.r = ofRandom(0.0f, 40.0f);
		c.g = ofRandom(230.0f, 255.0f);
		c.b = ofRandom(220.0f, 255.0f);
		
		balls.push_back( new Ball(x, y, z, scale, c));
	}
}

void Cluster::update()
{

	// loop through balls
	// upadte ball position with +1 or -1
	
	// if person pos is within pos 
	// call explode method
	
}

void Cluster::draw()
{
	for (int i = 0; i < balls.size(); i++) 
	{
		balls[i]->draw(m_state);
	}

}

// void explode
	// loop through balls and call their explode method