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
	init();
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

void Particle::init() {
	x = 0;
	y = 0;
	direction = (2 * M_PI * rand())/RAND_MAX;
	speed = (0.05 * rand())/RAND_MAX;
	speed *= speed;
}

void Particle::update(int millis) {
	direction += millis * 0.0004;
	double xSpeed = cos(direction) * speed;
	double ySpeed = sin(direction) * speed;
	if(x < -1 || x > 1 || y < -1 || y > 1) {
		init();
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
