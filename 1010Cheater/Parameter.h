#pragma once

#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <array>

#include "Block.h"

using namespace std;

struct Point
{
	int r, c;
};

class Parameter
{
public:
	Parameter();

	MAP origin_map;
	MAP new_map;

	array<int, 19> origin_positions;
	array<int, 19> new_positions;

	vector<Block> series_block;
	vector<Point> series_position;

	int index;
	int score, score_put, score_remove;
	int perimeter;
	int single_count;

	double rank_value;
};

