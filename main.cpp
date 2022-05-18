#include "pvc.h"
#include "cmfnc.h"
#include "menu.h"
#include "leaderboard.h"
int main(int argc, char* argv[])
{	
	cmfnc::initSDL(window, renderer);
	//FreeConsole();

	std::vector<std::string> data;
	std::ifstream input("data.txt");
	std::string word;	
	while (!input.eof())
	{
		getline(input, word);
		data.push_back(word);				
	}		
	
	PvC pvc(data, renderer);
	Leaderboard leaderboard(renderer);
	Menu menu(renderer);
	
	double point;
	int i;

	while (true)
	{
		switch (menu.getchoice(renderer))
		{
			case 1:
				point = pvc.loop(renderer);
				if (point == -1) return 0;	
				if (point == -2) break;	
				i = leaderboard.insertNewPlayer(point, renderer);
				if (i == -1) return 0;
				i = leaderboard.render(renderer);
				if (i == 0) return 0;
				break;
			case 3:
				std::cout << 1;
				i = leaderboard.render(renderer);
				if (i == 0) return 0;
				break;
			case 4:
				return 0;
				break;
			default:
				return 0;
		}
	}
		

	input.close();
	return 0;
}