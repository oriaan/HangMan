#pragma once
#include "cmfnc.h"
#include "button.h"
struct Player
{
	std::string name;
	double point;
	SDL_Texture* texture[30];
	SDL_Rect rect;
	SDL_Color color;
	TTF_Font* font;
	SDL_Texture* createTextureFromChar(SDL_Renderer* renderer, char c);
	std::string toUpper(std::string s)
	{
		for (int i = 0; i < s.length(); i++) s[i] = std::toupper(s[i]);
		return s;
	}	
	Player();
	Player(std::string exit_code)
	{
		name = exit_code;		
	}
	Player(SDL_Renderer* renderer, std::string n, double p, SDL_Rect);	
	bool operator<(const Player& that)
	{
		return point > that.point;
	}
	void rectModify(int index);
	void render(SDL_Renderer* renderer);	
	std::string getName()
	{
		return name;
	}
	double getPoint()
	{
		return point;
	}		
};

class Name
{
private:
	std::vector<SDL_Texture*> textures;
	std::vector<SDL_Rect> rects;	
	std::string name;
	SDL_Color color;
	TTF_Font* font;
public:
	Name()
	{
		name = "";
		font = TTF_OpenFont("ariblk.ttf", 144);
		color = { 105, 105, 105 };
	}
	void addChar(SDL_Renderer* renderer,const char* c)
	{		
		name += c;
		textures.push_back(cmfnc::createMessage(renderer, color, c, font));
		int x = 500 + (textures.size() - 1) * 30;
		rects.push_back(SDL_Rect{x,177,30,40 });
	}
	void delChar()
	{	
		name.erase(name.end() - 1);
		textures.pop_back();
		rects.pop_back();
	}
	void render(SDL_Renderer* renderer)
	{
		for (int i = 0; i < textures.size(); i++) SDL_RenderCopy(renderer, textures.at(i), NULL, &rects.at(i));
	}
	std::string getName()
	{
		return name;
	}
};

class Leaderboard
{
private:		
	std::vector<Player> players;
	SDL_Color color;
	TTF_Font* font;
	Button back;
	Button deleteAll;	
	Button enterName;
	Button submit;
	void reset()
	{
		std::vector<Player> playerss;
		players = playerss;
		update();
	}
	Player createNewPlayer(SDL_Renderer* renderer, double point,int index);
public:
	Leaderboard();
	Leaderboard(SDL_Renderer* renderer);
	void update();
	int insertNewPlayer(double point,SDL_Renderer* renderer);
	int render(SDL_Renderer* renderer);
};