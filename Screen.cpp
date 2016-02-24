/*
 * Screen.cpp
 *
 *  Created on: Feb 19, 2016
 *      Author: Jack
 */

#include "Screen.h"
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <iomanip>
#include <math.h>
#include <string>
#include <sstream>
#include "SDL/SDL_ttf.h"
#include "PCollection.h"
#include "Particle.h"

namespace jab {

//Screen::Screen(int WIDTH, int HEIGHT) {
//	// TODO Auto-generated constructor stub
//	createWindow();
//}

Screen::~Screen() {
	// TODO Auto-generated destructor stub
	delete [] pixel_buffer;
}

void Screen::startSDL() {
	std::cout << "Initializing SDL = ";
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failure: " << SDL_GetError() << std::endl;
		exit(1);
	}
	std::cout << "Success!" << std::endl;
}

void Screen::startTTF() {
	std::cout << "Initializing TTF = ";
	if(TTF_Init() < 0) {
		std::cout << "Failure: " << TTF_GetError() << std::endl;
		exit(1);
	}
	std::cout << "Success!" << std::endl;
}

void Screen::createWindow() {
	std::cout << "Initializing Window = ";
	window = SDL_CreateWindow("Particle Explosion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if(window == NULL) {
		std::cout << "Failure: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}
	std::cout << "Success!" << std::endl;
}

void Screen::createRenderer() {
	std::cout << "Initializing Renderer = ";
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	if(renderer == NULL) {
		std::cout << "Failure: " << SDL_GetError() << std::endl;
		quitWindow();
		exit(1);
	}
	std::cout << "Success!" << std::endl;
}

void Screen::createTexture() {
	std::cout << "Initializing Texture = ";
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
	if(renderer == NULL) {
		std::cout << "Failure: " << SDL_GetError() << std::endl;
		SDL_DestroyRenderer(renderer);
		quitWindow();
		exit(1);
	}
	std::cout << "Success!" << std::endl;
}

void Screen::createFont() {
	std::cout << "Initializing Font = ";
	font = TTF_OpenFont("OpenSans-Regular.ttf", 100);
	if(font == NULL) {
		std::cout << "Failure: " << TTF_GetError() << std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(texture);
		quitWindow();
		exit(1);
	}
	std::cout << "Success!" << std::endl;
}

int Screen::getColor(Uint8 r,  Uint8 g, Uint8 b) {
	Uint32 color = r;
	color <<= 8;
	color += g;
	color <<= 8;
	color += b;
	color <<= 8;
	color += 255;
	return color;
}

void Screen::setPixelColor(int x, int y, Uint8 r,  Uint8 g, Uint8 b) {
	if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return;
	pixel_buffer[y * WIDTH + x] = getColor(r, g, b);
}

void Screen::setText(int x, int y, int w, int h, std::string message) {
	SDL_Color white = {255, 255, 255};
	SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), white);
	SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
	if(surface == NULL) {
		std::cout << TTF_GetError() << std::endl;
	} else {
		SDL_Texture* sMessage = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_RenderCopy(renderer, sMessage, NULL, &rect);
		SDL_DestroyTexture(sMessage);
		SDL_FreeSurface(surface);
	}
}

void Screen::clearBuffer() {
	std::memset(pixel_buffer, 0, WIDTH * HEIGHT * sizeof(Uint32));
}

void Screen::blur() {
	Uint32* second_buffer = pixel_buffer;
	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {

			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;

			for(int r = -1; r <= 1; r++) {
				for(int c = -1; c <= 1; c++) {
					int curX = x + c;
					int curY = y + r;

					if(curX >= 0 && curX < WIDTH && curY >= 0 && curY < HEIGHT) {
						Uint32 color = second_buffer[curY * WIDTH + curX];
						Uint8 red = color >> 24;
						Uint8 green = color >> 16;
						Uint8 blue = color >> 8;

						redTotal += red;
						greenTotal += green;
						blueTotal += blue;
					}
				}
			}

			Uint8 red = redTotal / 9;
			Uint8 green = greenTotal / 9;
			Uint8 blue = blueTotal / 9;
			setPixelColor(x, y, red, green, blue);
		}
	}
}

int Screen::update() {
	unsigned char red = (1 + sin(SDL_GetTicks() * 0.0005)) * 128;
	unsigned char green = (1 + sin(SDL_GetTicks() * 0.0007)) * 128;
	unsigned char blue = (1 + cos(SDL_GetTicks() * 0.0007)) * 128;
	collection.update(SDL_GetTicks());
//	clearBuffer();
	const Particle * const pCollection = collection.getParticles();
	for(int i = 0; i < collection.NPARTICLES; i++) {
		Particle particle = pCollection[i];
		int x = (particle.x + 1) * 400;
		int y = (particle.y * 400) + HEIGHT / 2;
		setPixelColor(x, y, red, green, blue);
	}
	blur();
//	std::memset(pixel_buffer, 255, WIDTH * HEIGHT * sizeof(Uint32));
	SDL_UpdateTexture(texture, NULL, pixel_buffer, WIDTH*sizeof(Uint32));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	setText(10,0,150,55, "Version 1");
	SDL_RenderPresent(renderer);
	//Check for events
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			return 1;
		}
	}
	return 0;
}

void Screen::quitWindow() {
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Screen::quitFull() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
	quitWindow();
}

} /* namespace jab */
