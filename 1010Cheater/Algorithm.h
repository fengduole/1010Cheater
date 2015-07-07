#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

#include "Block.h"
#include "Parameter.h"

using namespace std;

const int series_index[6][3] = { 
{ 1, 2, 3 },
{ 1, 3, 2 },
{ 2, 1, 3 },
{ 2, 3, 1 },
{ 3, 1, 2 },
{ 3, 2, 1 } };

class Algorithm
{
public:
	Algorithm();

	void SetBlockList(vector<Block>);

	void Alg(array<array<int, 12>, 12>, 
			 vector<Block>, 
			 array<array<int, 12>, 12>&, 
			 int &,
			 int &, 
			 int &);

private:
	// function members
	bool IsPut(array<array<int, 12>, 12>, Block, int, int);
	int BlockPositionCount(array<array<int, 12>, 12>, Block);
	array<int, 19> GetPositionCounts(array<array<int, 12>, 12>);
	int GetPerimeter(array<array<int, 12>, 12>);
	int GetSingleCount(array<array<int, 12>, 12>);

	void PutDownBlock(array<array<int, 12>, 12>&, Block, int, int);
	void PickUpBlock(array<array<int, 12>, 12>&, Block, int, int);

	vector<Block> SeriesBlock(vector<Block>, const int);
	void MapRemove(array<array<int, 12>, 12>, array<array<int, 12>, 12>&, int&);

	void MapRemoveRow(array<array<int, 12>, 12>&, int);
	void MapRemoveCol(array<array<int, 12>, 12>&, int);

	static bool ComparerParameter(Parameter, Parameter);
	static double RankValueCalc(Parameter);

	void PutBlockSeries(array<array<int, 12>, 12>, 
						vector<Block>,
						array<array<int, 12>, 12>&,
						int &,
						int &,
						int &);

	void DeepFirstPositionSearch(array<array<int, 12>, 12>,
		Parameter, vector<Block>::const_iterator, vector<Block>::const_iterator);

	
	void PrintMap(array<array<int, 12>, 12>);

	// constant
	const int max_param_cache_size = 9999;

	// data members
	vector<Block> block_list;
	vector<Parameter> param_cache;
	vector<Parameter> parameter;
};