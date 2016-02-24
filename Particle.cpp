/*
 * Particle.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: Jack
 */

#include "Particle.h"
#include <math.h>
#include <stdlib.h>

namespace jab {

Particle::Particle(): x(0), y(0) {
	// TODO Auto-generated constructor stub
	direction = (2 * M_PI * rand())/RAND_MAX;
	speed = (0.0001 * rand())/RAND_MAX;
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

void Particle::update(int millis) {
	double xSpeed = cos(direction) * speed;
	double ySpeed = sin(direction) * speed;
	if(x < -1 || x > 1) {
		xSpeed = -xSpeed;
	}
	if(y < -1 || y > 1) {
		ySpeed = -ySpeed;
	}
//	double xSpeed = 0.01 * ((2.0 * rand()/RAND_MAX) - 1);
//	double ySpeed = 0.01 * ((2.0 * rand()/RAND_MAX) - 1);
//	if(x < 0 || x > 800) {
//		xSpeed = -xSpeed;
//	}
//	if(y < 0 || y > 600) {
//		ySpeed = -ySpeed;
//	}
	x += xSpeed * millis;
	y += ySpeed * millis;
}

} /* namespace jab */
