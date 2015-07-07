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

	int Simulation(void);
	int Cheat(void);
	int ListInput(void);

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
	array<array<int, 12>, 12> map;

	int score, score_put, score_remove;
	int times;

	vector<Block> block_history;
};
