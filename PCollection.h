/*
 * PCollection.h
 *
 *  Created on: Feb 23, 2016
 *      Author: Jack
 */

#ifndef PCOLLECTION_H_
#define PCOLLECTION_H_

#include "Particle.h"
namespace jab {

class PCollection {
private:
	Particle *pCollection;
	int lastMillis;
public:
	const static int NPARTICLES = 5000;
	PCollection();
	const Particle *getParticles() { return pCollection; };
	void update(int millis);
	virtual ~PCollection();
};

} /* namespace jab */

#endif /* PCOLLECTION_H_ */
