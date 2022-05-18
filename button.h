#pragma once
#include "cmfnc.h"
class Button
{
private:
	SDL_Texture* texture;
	SDL_Rect rect;
public:
	Button();
	Button(SDL_Renderer* renderer, const char* path, SDL_Rect rect);
	Button(SDL_Renderer* renderer, SDL_Texture* texture_, SDL_Rect rect);
	void render(SDL_Renderer* renderer);
	bool isClick(int x,int y);	
};
