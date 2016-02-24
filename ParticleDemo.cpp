/*
 * ParticleDemo.cpp
 *
 *  Created on: Feb 20, 2016
 *      Author: Jack
 */
#include "Screen.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char* args[]) {
	srand(time(NULL));
	jab::Screen* screen = new jab::Screen(800, 600);
	while(true) {
		if(screen->update() > 0) {
			break;
		}
	}
	screen->quitFull();
	delete screen;
	return 0;
}


