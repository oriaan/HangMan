#include "pvc.h"
Level::Level()
{
}

Level::Level(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	rect.x = 50;
	rect.y = 200;
	rect.w = 200;
	rect.h = 80;

	easy = Button(renderer, "easy.png", rect);
	rect.x += 300;
	medium = Button(renderer, "medium.png", rect);
	rect.x += 300;
	hard = Button(renderer, "hard.png", rect);
	rect.x += 300;
	nightmare = Button(renderer, "nightmare.png", rect);
	back = Button(renderer, "back.png", SDL_Rect{ 0,0,50,50 });
}

int Level::getLevel(SDL_Renderer* renderer)
{
	SDL_Event event;
	while (true)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) return -1;
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (easy.isClick(x, y)) return 1;
				if (medium.isClick(x, y)) return 2;
				if (hard.isClick(x, y)) return 3;
				if (nightmare.isClick(x, y)) return 4;
				if (back.isClick(x, y)) return -2;
			}
		}

		easy.render(renderer);
		medium.render(renderer);
		hard.render(renderer);
		nightmare.render(renderer);
		back.render(renderer);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}
	return -1;
}

Slot::Slot()
{
}

Slot::Slot(SDL_Renderer* renderer, SDL_Rect r, SDL_Color color, TTF_Font* font)
{
	texture = cmfnc::createMessage(renderer, color, "-", font);
	rect = r;
	border = SDL_Rect{ r.x - 1,r.y - 1,r.w + 2,r.h + 2 };
}

Slot::Slot(SDL_Renderer* renderer, SDL_Rect r, SDL_Color color, TTF_Font* font, const char* x)
{
	texture = cmfnc::createMessage(renderer, color, x, font);
	rect = r;
	border = SDL_Rect{ r.x - 1,r.y - 1,r.w + 2,r.h + 2 };
}

void Slot::changeC(SDL_Renderer* renderer, SDL_Color color, TTF_Font* font, const char* x)
{
	c = x;
	texture = cmfnc::createMessage(renderer, color, c, font);
}

void Slot::render(SDL_Renderer* renderer)
{
	SDL_RenderDrawRect(renderer, &border);
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Slot::changeBGC(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 204, 255, 246, 255);
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Slot::setBG(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 51, 255, 51, 255);
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

Answer::Answer()
{
}

Answer::Answer(SDL_Renderer* renderer, int length)
{
	font = TTF_OpenFont("ariblk.ttf", 144);
	color = { 0, 0, 0 };

	SDL_Rect rect;
	rect.w = 50;
	rect.h = 50;
	rect.x = (SCREEN_WIDTH - length * 50) / 2;
	rect.y = 100;
	
	for (int i = 0; i < length; i++)
	{
		slots.push_back(Slot(renderer, rect, color, font));
		rect.x += 55;
	}

	answer = "";
	for (int i = 0; i < length; i++) answer += "-";
	pos = -1;
}

void Answer::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (inArea(x, y))
	{		
		int index = getPosition(x, y);
		slots.at(index).changeBGC(renderer);
	}
	if (pos != -1)
	{
		slots.at(pos).setBG(renderer);
	}
	for (int i = 0; i < slots.size(); i++) slots.at(i).render(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

bool Answer::inArea(int x, int y)
{
	for (int i = 0; i < slots.size(); i++) if (slots.at(i).inArea(x, y)) return true;
	return false;
}

int Answer::getPosition(int x, int y)
{
	for (int i = 0; i < slots.size(); i++) if (slots.at(i).inArea(x, y)) return i;
	return -1;
}

void Answer::changeAnswer(SDL_Renderer* renderer,int index, char c)
{
	std::string s = std::string(1, c);
	slots.at(index).changeC(renderer, color, font, s.c_str());
	answer[index] = c;
}

std::vector<int> Answer::getIndex()
{
	std::vector<int> index;
	for (int i = 0; i < answer.size(); i++) if (answer[i] == '-') index.push_back(i);
	return index;
}

void Answer::reset(SDL_Renderer* renderer)
{
	for (int i = 0; i < answer.length(); i++) answer[i] = '-';
	for (int i = 0; i < slots.size(); i++) slots.at(i).changeC(renderer, color, font, "-");
}

Alphabet::Alphabet()
{
}

Alphabet::Alphabet(SDL_Renderer* renderer)
{
	font = TTF_OpenFont("ariblk.ttf", 40);
	color = { 0, 0, 0 };

	rect = SDL_Rect{ 100,200,50,50 };
	
	SDL_Rect r2 = rect;
	for (int i = 0; i < 26; i++)
	{		
		r2.x = rect.x + (i % 10) * 52;
		r2.y = rect.y + (i / 10) * 52;		
		std::string s = std::string(1, char(65 + i));
		character[i] = Slot(renderer, r2, color,font,s.c_str());
	}
}

void Alphabet::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (inArea(x, y))
	{
		for (int i = 0;i < 26;i++) if (character[i].inArea(x,y)) character[i].changeBGC(renderer);
	}
	for (int i = 0; i < 26; i++) character[i].render(renderer);
}

bool Alphabet::inArea(int x, int y)
{
	if (y >= rect.y && y <= rect.y + 2*(rect.h + 2)  && x >= rect.x && x <= rect.x + 10*(rect.w + 2)) return true;
	if (y >= rect.y + 2*(rect.h + 2) && y <= rect.y + 3*(rect.h + 2) && x >= rect.x && x <= rect.x + 6 * (rect.w + 2)) return true;
	return false;
}

bool Alphabet::canGetChar(int x, int y)
{
	for (int i = 0; i < 26; i++) if (character[i].inArea(x, y)) return true;
	return false;
}

char Alphabet::clicked(int x, int y)
{
	x -= 100;
	y -= 200;
	int p = (y / rect.h) * 10 + x / rect.w;
	return 65 + p;
}

PvC::PvC(std::vector<std::string> input, SDL_Renderer* renderer)
{
	data = input;
	level = Level(renderer);
	alphabet = Alphabet(renderer);
	back = Button(renderer, "back.png", SDL_Rect{ 0,0,50,50 });
	help = Button(renderer, "help.png", SDL_Rect{ 1125,0,75,50 });
	giveup = Button(renderer, "giveup.png", SDL_Rect{ 1125,50,75,50 });
	reset = Button(renderer, "reset.png", SDL_Rect{ 900,200,100,75 });
	submit = Button(renderer, "submit.png", SDL_Rect{ 900,300,100,75 });
	vtr = Victory_pose(renderer);
	lose = Lose_pose(renderer);
	submit_remaining = Message(renderer, SDL_Rect{ 1020,310,50,50 },0);
	help_remaining = Message(renderer, SDL_Rect{1050,0,50,50},0);
}

void PvC::generateKeyword(int level)
{
	if (level < 4)
	{
		int max_length = 2 + 3*level;
		int min_length = (level - 1) * 3;
		std::vector<std::string> sample;
		for (int i = 0; i < data.size(); i++) if (data.at(i).length() >= min_length && data.at(i).length() <= max_length) sample.push_back(data.at(i));
		int index = rand() % (sample.size() - 0 + 1) + 0;
		keyword = sample.at(index);
	}
	else
	{
		std::vector<std::string> sample;
		for (int i = 0; i < data.size(); i++) if (data.at(i).length() > 11) sample.push_back(data.at(i));
		int index = rand() % (sample.size() - 0 + 1) + 0;
		keyword = sample.at(index);
	}
}

void PvC::getHelp(SDL_Renderer* renderer)
{
	std::vector<int> index = answer.getIndex();
	int r = rand() % ((index.size() - 1) - 0 + 1) + 0;
	answer.changeAnswer(renderer, index.at(r), keyword[index.at(r)]);
}

void PvC::giveUp()
{
}

double PvC::loop(SDL_Renderer* renderer)
{
	clock_t st, et;
	SDL_Event event;
	char c;
	int i;
	int l;
	int h;
	int s;

generate:
	l = level.getLevel(renderer);
	if (l < 0) return l;
	generateKeyword(l);
	answer = Answer(renderer, keyword.length());
	c = '/';
	i = -1;
	h = keyword.length() - l*2;
	s = keyword.length()*2 - (l - 1)*2;
	help_remaining.modify(renderer, h);
	submit_remaining.modify(renderer, s);

	st = clock();

	while (true)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) return -1;	
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (alphabet.inArea(x, y) && alphabet.canGetChar(x, y) && i != -1) c = alphabet.clicked(x, y);
				if (answer.inArea(x, y))
				{
					i = answer.getPosition(x, y);
					answer.setPos(i);
				}				
				if (back.isClick(x, y)) goto generate;
				if (help.isClick(x, y) && h-- > 0)
				{
					help_remaining.modify(renderer, h);
					getHelp(renderer);
				}
				if (reset.isClick(x, y)) answer.reset(renderer);
				if (submit.isClick(x, y))
				{
					s--;
					submit_remaining.modify(renderer, s);
					if (answer.isTrue(keyword)) goto end;
				}
				if (!alphabet.inArea(x, y) && !answer.inArea(x, y))
				{
					c = '/';
					i = -1;
					answer.setPos(-1);
				}
				if (giveup.isClick(x, y)) goto lose;
			}
		}


		if (s == 0)
		{
		lose:
			lose.createT2(renderer, keyword);
			switch (lose.render(renderer))
			{
				case 0:
					return -1;
				case 1:
					goto generate;				
			}
		}

		if (i != -1 && c != '/')
		{
			answer.changeAnswer(renderer, i, c);
			c = '/';
		}
		

		alphabet.render(renderer);
		answer.render(renderer);
		back.render(renderer);
		help.render(renderer);
		giveup.render(renderer);
		reset.render(renderer);
		submit.render(renderer);
		submit_remaining.render(renderer);
		help_remaining.render(renderer);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}
	
end:
	et = clock();
	
	double t = ((double) et - st)/100;
	double point = (double) 1000 * l * keyword.length() * (1.0 / t);
	vtr.createT2(renderer, point);
	switch (vtr.render(renderer))
	{
		case 0:
			return -1;
		case 1:
			goto generate;
		case 2:
			break;
	}
	return point;
}

Message::Message()
{
}