#include <iostream>

#include "Game.h"

using namespace std;

int main(void)
{
	int game_mode, alg_mode;
	Game game;

	//input_mode = 2;
	//alg_mode = 2;

	cin >> game_mode >> alg_mode;
	
	if (game_mode == 1)
	{
		game.Simulation(alg_mode);
	}
	else if (game_mode == 2)
	{
		game.ListInput(alg_mode);
	}
	else if (game_mode == 3)
	{
		game.Cheat();
	}
	else if (game_mode == 4)
	{
	}

	system("pause");

	return 0;
}