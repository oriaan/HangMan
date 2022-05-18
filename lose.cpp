#include "lose.h"

Lose_pose::Lose_pose()
{
}

Lose_pose::Lose_pose(SDL_Renderer* renderer)
{
	font = TTF_OpenFont("ariblk.ttf", 144);
	color = { 0, 0, 0 };
	texture1 = cmfnc::createMessage(renderer, color, "Poor you, it seem to be hard :(", font);
	texture3 = cmfnc::createMessage(renderer, color, "Better luck next time!", font);
	rect1 = SDL_Rect{ 100,50,31 * 20,40 };
	rect3 = SDL_Rect{ 100,200,22 * 20,40 };	
	replay = Button(renderer, "replay.png", SDL_Rect{ 500,275,200,75 });
}

void Lose_pose::createT2(SDL_Renderer* renderer, std::string keyword)
{
	std::string s = "Keyword is " + keyword;
	int i = s.length();
	rect2 = SDL_Rect{ 100,125,i * 40,45 };
	texture2 = cmfnc::createMessage(renderer, color, s.c_str(), font);
}

int Lose_pose::render(SDL_Renderer* renderer)
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
			}
		}


		SDL_RenderCopy(renderer, texture1, NULL, &rect1);
		SDL_RenderCopy(renderer, texture2, NULL, &rect2);
		SDL_RenderCopy(renderer, texture3, NULL, &rect3);		
		replay.render(renderer);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}
	return 0;
}