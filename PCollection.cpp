/*
 * PCollection.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: Jack
 */

#include "PCollection.h"

namespace jab {

PCollection::PCollection() {
	// TODO Auto-generated constructor stub
	pCollection = new Particle[NPARTICLES];
	lastMillis = 0;
}

PCollection::~PCollection() {
	// TODO Auto-generated destructor stub
	delete [] pCollection;
}

void PCollection::update(int millis) {
	int interval = millis - lastMillis;
	for(int i = 0; i < NPARTICLES; i++) {
		pCollection[i].update(interval);
	}
	lastMillis = millis;
}

} /* namespace jab */
