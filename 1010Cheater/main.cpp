#include <iostream>

#include "Game.h"

using namespace std;

int main(void)
{
	int mode;
	Game game;

	cin >> mode;

	if (mode == 1)
	{
		game.Simulation();
	}
	else if (mode == 2)
	{
		game.Cheat();
	}
	else if (mode == 3)
	{
		game.ListInput();
	}

	system("pause");

	return 0;
}