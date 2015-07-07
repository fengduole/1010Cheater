#pragma once

#include <iostream>

class Block
{
public:
	Block();

	void SetBlock(int id, int r, int c, int map[5][5]);

	// data member
	int _id;
	int _r, _c;
	int _shape_map[5][5];

	int _times_index, _series_index;
	int _score_put;
};

