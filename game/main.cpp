#include <iostream>
#include <game.h>
#include <ai.h>
#include <ctime>
#include <conio.h>
using namespace std;

int main()
{
	srand(time(nullptr));
	vector<Player*> players;
	players.emplace_back(new MinMon());
	players.emplace_back(new MinMon());
	players.emplace_back(new MinMon());
	players.emplace_back(new MinMon());
	ConsoleUI* ui = new ConsoleUI();
	while(true)
	{
		Game game(ui, players);
		game.main_loop();
		getch();
	}
	return 0;
}