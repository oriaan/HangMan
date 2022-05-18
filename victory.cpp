#include "victory.h"

Victory_pose::Victory_pose()
{
}

Victory_pose::Victory_pose(SDL_Renderer* renderer)
{
	font = TTF_OpenFont("ariblk.ttf", 144);
	color = { 0, 0, 0 };
	texture1 = cmfnc::createMessage(renderer, color, "Congratulations!",font);
	texture3 = cmfnc::createMessage(renderer, color, "Now go outside and touch some grass, please", font);
	rect1 = SDL_Rect{ 100,50,16 * 40,50 };
	rect3 = SDL_Rect{ 100,200,44 * 20,25 };
	enter = Button(renderer, "gotoL.png", SDL_Rect{ 250,275,175,75 });
	replay = Button(renderer, "replay.png", SDL_Rect{ 750,275,175,75 });
}

void Victory_pose::createT2(SDL_Renderer* renderer, double point)
{
	std::string s = "You got " + std::to_string(point) + " points!";
	int i = s.length();
	rect2 = SDL_Rect{ 100,125,i * 40,45 };	
	texture2 = cmfnc::createMessage(renderer, color, s.c_str(), font);
	
}

int Victory_pose::render(SDL_Renderer* renderer)
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
				if (replay.isClick(x, y)) return 1;
				if (enter.isClick(x, y)) return 2;
			}
		}


		SDL_RenderCopy(renderer, texture1, NULL, &rect1);
		SDL_RenderCopy(renderer, texture2, NULL, &rect2);
		SDL_RenderCopy(renderer, texture3, NULL, &rect3);
		enter.render(renderer);
		replay.render(renderer);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}
}