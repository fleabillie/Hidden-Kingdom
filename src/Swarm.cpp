/*
 *  adapted from:
 *	Swarm.cpp
 *  advanced3dExample
 *
 *  Created by Elliot Woods on 19/01/2011.
 *  Copyright 2011 Kimchi and Chips. All rights reserved.
 *
 */

#include "Swarm.h"

Swarm::Swarm()
{
	//constructor, let's set some defaults
	nParticles = 0;	
	light.setAmbientColor(ofColor(0,0,0));
}

// system of clusters, number of cluster, position & velocity dispersion, scale
void Swarm::init(int _nParticles, float positionDispersion, float velocityDispersion, float scaleRandom)
{
	
	for (int i = 0; i < _nParticles; i++) 
	{
		int x = (ofRandom(1.0f)-0.5f) * positionDispersion;
		int y = (ofRandom(0.0f, -0.15f)) * positionDispersion;
		int z = (ofRandom(1.0f)-0.5f) * positionDispersion;
		
		clusters.push_back( new Cluster(x, y, z));
	}
}

void Swarm::customDraw()
{
	///we run the update ourselves manually
	update();
	
	ofPushStyle();

	///////////////////////////////////////////
	// DRAW SPHERES
	///////////////////////////////////////////
	//
	
	for (int i=0; i < clusters.size(); i++)
	{
		clusters[i]->draw();
	}
	
	///////////////////////////////////////////
	
	//light.disable();
	//ofDisableLighting();
	
	ofPopStyle();
}

void Swarm::update()
{
	
	//calculate time past per frame
	float dt = ofGetElapsedTimef() - timeLastUpdate;
	timeLastUpdate = ofGetElapsedTimef();
	
	//update positions, velocities
	for (int i=0; i< nParticles; i++)
	{
			
		// position motion
		positions[i] += velocities[i] * dt;
		velocities[i] += - SPRING_CONSTANT * positions[i] * dt;	
		velocities[i] += 2 * positions[i] * dt;
		
		//
		/////////////////////////////////

	}
}


