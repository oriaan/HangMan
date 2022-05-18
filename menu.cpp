#include "menu.h"
#include "cmfnc.h"
Menu::Menu(SDL_Renderer* renderer)
{	
	pvc = Button(renderer, "pvc.png", SDL_Rect{ 100, 250, 200, 80 });
	cvp = Button(renderer, "cvp.png", SDL_Rect{ 500, 250, 200, 80 });
	leaderboard = Button(renderer, "leaderboard.png", SDL_Rect{ 900, 250, 200, 80 });
	exit = Button(renderer, "exit.png", SDL_Rect{ 1150,0,50,50 });
	logo = Button(renderer, "logo.png", SDL_Rect{ 300,0,600,200 });
}

int Menu::getchoice(SDL_Renderer* renderer)
{
	SDL_Event event;
	while (true)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) return 0;
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (pvc.isClick(x, y)) return 1;
				if (cvp.isClick(x, y)) return 2;
				if (leaderboard.isClick(x, y)) return 3;
				if (exit.isClick(x, y)) return 4;
			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		pvc.render(renderer);
		cvp.render(renderer);
		leaderboard.render(renderer);
		exit.render(renderer);
		logo.render(renderer);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}
	return -1;
}
