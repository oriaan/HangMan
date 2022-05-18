#include "leaderboard.h"

SDL_Texture* Player::createTextureFromChar(SDL_Renderer* renderer, char c)
{
	std::string s = std::string(1, c);
	return cmfnc::createMessage(renderer, color, s.c_str(), font);
}

Player::Player()
{	
}

Player::Player(SDL_Renderer* renderer, std::string n, double p, SDL_Rect r)
{
	font = TTF_OpenFont("ariblk.ttf", 144);
	color = { 105, 105, 105 };
	name = n;
	point = p;
	rect = r;
	std::string result = toUpper(name);
	std::string ps = std::to_string(p);
	for (int i = 1; i <= 30 - name.length() - ps.length(); i++) result += " ";
	result += ps;
	for (int i = 0; i < 30; i++)
	{
		texture[i] = createTextureFromChar(renderer, result[i]);
	}
	
}

void Player::rectModify(int index)
{
	rect = SDL_Rect{ 200,100 + index * 30,15,20 };
}

void Player::render(SDL_Renderer* renderer)
{
	for (int i = 0; i < 30; i++)
	{
		SDL_Rect r = rect;
		r.x += i * 20;
		SDL_RenderCopy(renderer, texture[i], NULL, &r);
	}
}

Player Leaderboard::createNewPlayer(SDL_Renderer* renderer,double point,int index)
{
	
	SDL_Event event;	
	Name name;
	while (true)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) return Player("exit_code_1077");
			if (event.type == SDL_KEYDOWN)
			{
				SDL_Keycode code = event.key.keysym.sym;
				if (code == SDLK_BACKSPACE) name.delChar();
				else
				{
					if (code == SDLK_SPACE)
					{						
						name.addChar(renderer, " ");						
					}
					else
					{											
						name.addChar(renderer, SDL_GetKeyName(code));
					}
				}
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (submit.isClick(x, y)) goto getResult;
			}
		}

		enterName.render(renderer);
		submit.render(renderer);
		name.render(renderer);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}
getResult:
	std::string temp = name.getName();
	return Player(renderer, temp, point, SDL_Rect{200,100 + index*30,15,20});
}

Leaderboard::Leaderboard()
{
}

Leaderboard::Leaderboard(SDL_Renderer* renderer)
{
	font = TTF_OpenFont("ariblk.ttf", 144);
	color = { 105, 105, 105 };

	std::ifstream input("leaderboard.txt");
	std::string name, point;
	int i = 0;
	std::string check;
	getline(input, check);
	if (check != "empty")
	while (!input.eof())
	{		
		getline(input, name);		
		getline(input, point);
		players.push_back(Player(renderer, name, std::stod(point), SDL_Rect{ 200,100 + i * 30,15,20 }));
		i++;
	}	
	input.close();	
	back = Button(renderer, "back.png", SDL_Rect{ 0,0,50,50 });
	deleteAll = Button(renderer, "delete.png", SDL_Rect{1100,0,100,50});
	enterName = Button(renderer, "enterName.png", SDL_Rect{ 150,150,300,100 });
	submit = Button(renderer, "submit.png", SDL_Rect{ 550,250,150,75 });
}

void Leaderboard::update()
{
	std::ofstream output("leaderboard.txt", std::ofstream::trunc);
	if (players.size() == 0)
	{
		output << "empty";
	}
	else
	{
		output << "data" << std::endl;
		std::sort(players.begin(), players.end());
		for (int i = 0; i < players.size(); i++) players.at(i).rectModify(i);
		int i;
		for (i = 0; i < ((players.size() > 7 ? 7 : players.size())) - 1; i++) output << players.at(i).getName() << std::endl << players.at(i).getPoint() << std::endl;
		output << players.at(i).getName() << std::endl << players.at(i).getPoint();
	}
	output.close();
}

int Leaderboard::insertNewPlayer(double point,SDL_Renderer* renderer)
{
	Player temp = createNewPlayer(renderer, point,players.size());
	if (temp.getName() == "exit_code_1077") return -1;
	players.push_back(temp);
	//std::sort(players.begin(), players.end(),compare);	
	update();
	return 0;
}

int Leaderboard::render(SDL_Renderer* renderer)
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
				if (back.isClick(x, y)) return 1;
				if (deleteAll.isClick(x, y)) reset();
			}
		}
		
		for (int i = 0; i < players.size(); i++) players.at(i).render(renderer);
		back.render(renderer);
		deleteAll.render(renderer);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}
	return 0;
}