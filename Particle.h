/*
 * Particle.h
 *
 *  Created on: Feb 23, 2016
 *      Author: Jack
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

namespace jab {

class Particle {
public:
	double x;
	double y;
	double speed;
	double direction;
	Particle();
	virtual ~Particle();
	void update(int millis);
	void init();
};

} /* namespace jab */

#endif /* PARTICLE_H_ */
