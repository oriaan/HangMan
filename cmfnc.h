#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <Windows.h>
#include <cmath>
#include <algorithm>
#include <string>
static const int SCREEN_WIDTH = 1200;
static const int SCREEN_HEIGHT = 400;
static SDL_Window* window;
static SDL_Renderer* renderer;
namespace cmfnc
{	
	void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
	void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
	SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path);
	SDL_Texture* createMessage(SDL_Renderer* renderer, SDL_Color color, const char* mess, TTF_Font* font);
}