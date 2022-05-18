#include "button.h"

Button::Button()
{
}

Button::Button(SDL_Renderer* renderer, const char* path, SDL_Rect r)
{
	texture = cmfnc::loadTexture(renderer, path);
	rect = r;
}

Button::Button(SDL_Renderer* renderer, SDL_Texture* texture_, SDL_Rect r)
{
	texture = texture_;
	rect = r;
}

void Button::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

bool Button::isClick(int x,int y)
{
	if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h) return true;
	return false;
}