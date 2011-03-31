/*
 *  Swarm.h
 *  advanced3dExample
 *
 *  Created by Elliot Woods on 19/01/2011.
 *  Copyright 2011 Kimchi and Chips. All rights reserved.
 *
 */

#include "ofMain.h"
#include "Cluster.h"

#define SPRING_CONSTANT 0.5

class Swarm : public ofNode
{
public:
	Swarm();
	void	init(int _nParticles, float positionDispersion, float velocityDispersion, float scaleRandom);
	
	void	customDraw();
	
	//light
	ofLight		light;
	
protected:
	
	vector <Cluster *> clusters;
	
	//we call this update function ourselves
	//at the beginning of customDraw
	void	update();
	
	//useful variables
	int			nParticles;
	float		timeLastUpdate;
	
	//objects
	ofVec3f		*positions;
	ofVec3f		*extraPositions;
	ofVec3f		*velocities;
	ofColor		*colors;	
	float_t		*scales;
	float_t		*scales2;
	float_t		*scales3;
	
};