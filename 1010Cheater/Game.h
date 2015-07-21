#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <ctime>

#include "Algorithm.h"
#include "Block.h"

using namespace std;

class Game
{
public:
	Game();

	int Simulation(int);
	int Cheat(void);
	int ListInput(int);
	int Core();

private:
	// function members
	void LoadBlock();
	void InitializeMap();
	vector<Block> RandomThreeBlocks(int);
	vector<Block> SelectThreeBlocks(int, int[]);

	void MapDisplay(int);

	// constant members
	const string block_file_name = "blocks.txt";
	
	// data members
	vector<Block> block_list;
	MAP map;

	int score, score_put, score_remove;
	int times;

	vector<Block> block_history;
};
