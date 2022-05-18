#pragma once
#include "cmfnc.h"
#include "button.h"
class Menu
{
private:
	Button pvc;
	Button cvp;
	Button leaderboard;
	Button setting;
	Button volume;
	Button exit;
	Button logo;
public:
	Menu(SDL_Renderer* renderer);
	int getchoice(SDL_Renderer* renderer);
};