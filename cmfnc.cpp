#include "cmfnc.h"
void cmfnc::initSDL(SDL_Window*& window, SDL_Renderer*& renderer)
{
	window = SDL_CreateWindow("Hang Man", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	TTF_Init();
	srand(time(NULL));
}
void cmfnc::quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
SDL_Texture* cmfnc::loadTexture(SDL_Renderer* renderer, const char* path)
{
	SDL_Surface* surface = IMG_Load(path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	return texture;
}
SDL_Texture* cmfnc::createMessage(SDL_Renderer* renderer, SDL_Color color, const char* mess, TTF_Font* font)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, mess, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	return texture;
}