#pragma once

#define MAP array<array<int, 12>, 12>

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
{ 3, 2, 1 }};

class Algorithm
{
public:
	Algorithm();

	void SetBlockList(vector<Block>);

	void Alg_Recursive(MAP, vector<Block>, MAP&, int &, int &, int &);
	void Alg_Circulation(MAP, vector<Block>, MAP&, int &, int &, int &);

private:
	// function members
	bool IsPut(MAP, Block, int, int);
	int BlockPositionCount(MAP, Block);
	array<int, 19> GetPositionCounts(MAP);
	int GetPerimeter(MAP);
	int GetSingleCount(MAP);

	void PutDownBlock(MAP&, Block, int, int);
	void PickUpBlock(MAP&, Block, int, int);

	vector<Block> SeriesBlock(vector<Block>, const int);
	void MapRemove(MAP, MAP&, int&);

	void MapRemoveRow(MAP&, int);
	void MapRemoveCol(MAP&, int);

	static bool ComparerParameter(Parameter, Parameter);
	static double RankValueCalc(Parameter);

	void PutBlockSeries(MAP, vector<Block>, MAP&, int &, int &, int &);

	void GenerateParameterCandidate(MAP, vector<Block>);

	void DeepFirstPositionSearch(MAP,
		Parameter, vector<Block>::const_iterator, vector<Block>::const_iterator);

	
	void PrintMap(MAP);

	// constant
	const int max_param_cache_size = 9999;

	// data members
	vector<Block> block_list;
	vector<Parameter> param_cache;
	vector<Parameter> parameter;
};