#pragma once
#include "cmfnc.h" 
#include "button.h"
#include "victory.h"
#include "lose.h"
class Level
{
private:
	Button easy;
	Button medium;
	Button hard;
	Button nightmare;
	Button back;
public:
	Level();
	Level(SDL_Renderer* renderer);
	int getLevel(SDL_Renderer* renderer);
};

class Slot
{
private:
	SDL_Texture* texture;
	SDL_Rect rect;
	SDL_Rect border;
	const char* c;		
public:
	Slot();
	Slot(SDL_Renderer* renderer, SDL_Rect r,SDL_Color color, TTF_Font* font);
	Slot(SDL_Renderer* renderer, SDL_Rect r, SDL_Color color, TTF_Font* font, const char* x);	
	void changeC(SDL_Renderer* renderer, SDL_Color color, TTF_Font* font, const char* x);
	void render(SDL_Renderer* renderer);
	void changeBGC(SDL_Renderer* renderer);
	void setBG(SDL_Renderer* renderer);
	bool inArea(int x, int y)
	{
		if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h) return true;
		return false;
	}	
};

class Answer
{
private:
	std::vector<Slot> slots;
	std::string answer;
	TTF_Font* font;
	SDL_Color color;
	std::vector<bool> status;
	int pos;
public:
	Answer();
	Answer(SDL_Renderer* renderer, int length);
	void render(SDL_Renderer* renderer);
	bool inArea(int x, int y);
	int getPosition(int x, int y);
	void changeAnswer(SDL_Renderer* renderer, int index, char c);
	bool isTrue(std::string keyword)
	{
		return answer == keyword;
	}
	std::vector<int> getIndex();
	void reset(SDL_Renderer* renderer);
	void setPos(int index)
	{
		pos = index;
	}
};

class Alphabet
{
private:
	Slot character[26];
	TTF_Font* font;
	SDL_Color color;	
	SDL_Rect rect;
public:
	Alphabet();
	Alphabet(SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);
	bool inArea(int x, int y);
	int index(int x, int y);
	bool canGetChar(int x, int y);
	char clicked(int x, int y);
};

class Message
{
private:
	SDL_Texture* texture;
	SDL_Rect rect;	
	SDL_Rect rrect; 
	TTF_Font* font;
	SDL_Color color;
public:
	Message();
	Message(SDL_Renderer* renderer,SDL_Rect r, int x)
	{
		font = TTF_OpenFont("ariblk.ttf", 40);
		color = { 0, 0, 0 };
		texture = cmfnc::createMessage(renderer, color, std::to_string(x).c_str(), font);
		rect = r;	
		rrect = r;
		rrect.w = rect.w * std::to_string(x).length();
	}
	void modify(SDL_Renderer* renderer, int x)
	{
		texture = cmfnc::createMessage(renderer, color, std::to_string(x).c_str(), font);		
		rrect.w = rect.w * std::to_string(x).length();
	}
	void render(SDL_Renderer* renderer)
	{
		SDL_RenderCopy(renderer, texture, NULL, &rrect);
	}
};

class PvC
{
private:
	std::vector<std::string> data;
	std::string keyword;	
	Level level;
	Alphabet alphabet;
	Answer answer;
	Button back;
	Button help;
	Button submit;
	Button reset;
	Button giveup;
	Victory_pose vtr;
	Lose_pose lose;
	Message help_remaining;
	Message submit_remaining;
	void generateKeyword(int level);
	void getHelp(SDL_Renderer* renderer);	
	void giveUp();
public:
	PvC(std::vector<std::string> input, SDL_Renderer* renderer);
	double loop(SDL_Renderer* renderer);
};