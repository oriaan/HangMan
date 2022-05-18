#pragma once
#include "cmfnc.h"
#include "button.h"
class Lose_pose
{
private:
	SDL_Texture* texture1;
	SDL_Texture* texture2;
	SDL_Texture* texture3;
	SDL_Rect rect1;
	SDL_Rect rect2;
	SDL_Rect rect3;
	SDL_Color color;
	TTF_Font* font;	
	Button replay;
public:
	Lose_pose();
	Lose_pose(SDL_Renderer* renderer);
	void createT2(SDL_Renderer* renderer, std::string keyword);
	int render(SDL_Renderer* renderer);
};