#pragma once

#ifndef Game_h
#define Game_h

#include <stdio.h>

#include "SDL.h"
#include "SDL_image.h"
#include "Debug.h"

class Game 
{
public:
	Game();
	~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running()
	{
		return isRunning;
	}
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Debug* debug;
};

#endif // game_h
