/*
 * Screen.h
 *
 *  Created on: Feb 19, 2016
 *      Author: Jack
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include "pCollection.h"
#include "Particle.h"

namespace jab {

class Screen {
public:
	Screen(int WIDTH, int HEIGHT): WIDTH(WIDTH), HEIGHT(HEIGHT) {
		pixel_buffer = new Uint32[WIDTH * HEIGHT];
		startSDL();
		startTTF();
		createWindow();
		createRenderer();
		createTexture();
		createFont();
	}
	void quitFull();
	int update();
	void setPixelColor(int x, int y, Uint8 r, Uint8 g, Uint8 b);
	virtual ~Screen();
private:
	const int WIDTH;
	const int HEIGHT;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	Uint32 *pixel_buffer;
	TTF_Font* font;
	PCollection collection;
	SDL_Event event;
	void startSDL();
	void startTTF();
	void createWindow();
	void createRenderer();
	void createTexture();
	void blur();
	void createFont();
	int getColor(Uint8 r, Uint8 g, Uint8 b);
	void setText(int x, int y, int w, int h, std::string message);
	void clearBuffer();
	void quitWindow();
};

} /* namespace jab */

#endif /* SCREEN_H_ */
