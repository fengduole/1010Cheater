#include "Algorithm.h"


Algorithm::Algorithm()
{
}

void Algorithm::SetBlockList(vector<Block> blocks)
{
	block_list.clear();

	copy(blocks.begin(), blocks.end(), back_inserter(block_list));
}

void Algorithm::Alg(array<array<int, 12>, 12> origin_map,
					vector<Block> blocks, 
					array<array<int, 12>, 12>& new_map, 
					int& status,
					int& score_put_delta, 
					int& score_remove_delta)
{
	parameter.clear();
	
	for (int i_combine = 0; i_combine < 6; i_combine++)
	{
		vector<Block> series_block = SeriesBlock(blocks, i_combine);

		param_cache.clear();
		PutBlockSeries(origin_map, series_block, new_map, status, score_put_delta, score_remove_delta);
		parameter.insert(parameter.end(), param_cache.begin(), param_cache.end());
	}

	sort(parameter.begin(), parameter.end(), ComparerParameter);

	if ((int)parameter.size() <= 0)
	{
		status = 1;
		return;
	}

	Parameter best_parameter = parameter[0];

	new_map = best_parameter.new_map;
	score_put_delta = best_parameter.score_put;
	score_remove_delta = best_parameter.score_remove;
	status = 0;
	
//	PrintMap(origin_map);
//	PrintMap(best_parameter.new_map);

	
	/*for (int i = 0; i <= 3; i++)
	{
		cout << parameter[i].perimeter << endl;
		PrintMap(parameter[i].new_map);
	}*/
}

/*
whether the map(row, col) can be put the block
*/
bool Algorithm::IsPut(array<array<int, 12>, 12> map, Block block, int row, int col)
{
	for (int i_r = 0; i_r < block._r; i_r++)
	{
		for (int i_c = 0; i_c < block._c; i_c++)
		{
			if (block._shape_map[i_r][i_c] && map[row + i_r][col + i_c])
			{
				return false;
			}
		}
	}

	return true;
}

/*
calculate how many positions can put the block
*/
int Algorithm::BlockPositionCount(array<array<int, 12>, 12> map, Block block)
{
	int count = 0;

	for (int i_r = 1; i_r <= 11 - block._r; i_r++)
	{
		for (int i_c = 1; i_c <= 11 - block._c; i_c++)
		{
			bool can_be_put = IsPut(map, block, i_r, i_c);

			if (can_be_put)
			{
				count++;
			}
		}
	}

	return count;
}

array<int, 19> Algorithm::GetPositionCounts(array<array<int, 12>, 12> map)
{
	array<int, 19> counts;
	counts.fill(0);

	for (int i = 0; i < (int)block_list.size(); i++)
	{
		counts[i] = BlockPositionCount(map, block_list[i]);
	}

	return counts;
}

int Algorithm::GetPerimeter(array<array<int, 12>, 12> map)
{
	int perimeter = 0;

	for (int i_r = 1; i_r <= 10; i_r++)
	{
		for (int i_c = 1; i_c <= 10; i_c++)
		{
			if (!map[i_r][i_c])
			{
				perimeter += map[i_r + 1][i_c] != 0;
				perimeter += map[i_r - 1][i_c] != 0;
				perimeter += map[i_r][i_c + 1] != 0;
				perimeter += map[i_r][i_c - 1] != 0;
			}
		}
	}

	return perimeter;
}

int Algorithm::GetSingleCount(array<array<int, 12>, 12> map)
{
	int count = 0;

	for (int i_r = 1; i_r <= 10; i_r++)
	{
		for (int i_c = 1; i_c <= 10; i_c++)
		{
			if (!map[i_r][i_c])
			{
				if (map[i_r + 1][i_c] != 0 && map[i_r - 1][i_c] != 0 && map[i_r][i_c + 1] != 0 && map[i_r][i_c - 1] != 0)
					count++;
			}
		}
	}

	return count;
}

void Algorithm::PutDownBlock(array<array<int, 12>, 12>& map, Block block, int row, int col)
{
	for (int i_r = 0; i_r < block._r; i_r++)
	{
		for (int i_c = 0; i_c < block._c; i_c++)
		{
			if (block._shape_map[i_r][i_c])
			{
				map[row + i_r][col + i_c] = block._series_index;
			}
		}
	}
}

void Algorithm::PickUpBlock(array<array<int, 12>, 12>& map, Block block, int row, int col)
{
	for (int i_r = 0; i_r < block._r; i_r++)
	{
		for (int i_c = 0; i_c < block._c; i_c++)
		{
			if (block._shape_map[i_r][i_c])
			{
				map[row + i_r][col + i_c] = 0;
			}
		}
	}
}


vector<Block> Algorithm::SeriesBlock(vector<Block> blocks, const int i_series)
{
	vector<Block> series_block;

	for (int i = 0; i < 3; i++)
	{
		Block block = blocks[series_index[i_series][i] - 1];
		block._series_index = (block._times_index - 1) * 3 + i + 1;

		series_block.push_back(block);
	}

	return series_block;
}

void Algorithm::MapRemove(array<array<int, 12>, 12> origin_map,
	array<array<int, 12>, 12>& new_map, int& score_remove)
{
	new_map = origin_map;

	array<int, 12> sum_col;
	array<int, 12> sum_row;

	sum_col.fill(0);
	sum_row.fill(0);

	for (int i_r = 1; i_r <= 10; i_r++)
	{
		for (int i_c = 1; i_c <= 10; i_c++)
		{
			if (origin_map[i_r][i_c])
			{
				sum_row[i_r]++;
				sum_col[i_c]++;
			}
		}
	}
	
	int total_removed = 0;

	for (int i = 1; i <= 10; i++)
	{
		if (sum_row[i] == 10)
		{
			MapRemoveRow(new_map, i);
			total_removed++;
		}

		if (sum_col[i] == 10)
		{
			MapRemoveCol(new_map, i);
			total_removed++;
		}
	}

	score_remove = total_removed * (total_removed + 1) * 5;
}


void Algorithm::MapRemoveRow(array<array<int, 12>, 12>& map, int row)
{
	for (int i = 1; i <= 10; i++)
	{
		map[row][i] = 0;
	}
}

void Algorithm::MapRemoveCol(array<array<int, 12>, 12>& map, int col)
{
	for (int i = 1; i <= 10; i++)
	{
		map[i][col] = 0;
	}
}

bool Algorithm::ComparerParameter(Parameter p1, Parameter p2)
{
	double rank_p1 = 0, rank_p2 = 0; //larger is better

	rank_p1 = RankValueCalc(p1);
	rank_p2 = RankValueCalc(p2);

	return rank_p1 > rank_p2;
}

double Algorithm::RankValueCalc(Parameter para)
{
	double value = 0, value_pos = 0;
	double weight_pos[19] = {1, 1.2, 1.2, 1.5, 1.5, 2, 2, 2, 2, 3, 3, 2.5, 3.5, 3.5, 4, 4, 4, 4, 5};

	value = para.perimeter * -5 +
		(para.score_remove + 10) * 10 +
		para.single_count * -300;

	for (int i = 10; i < 19; i++)
	{
		value_pos += para.new_positions[i] * weight_pos[i];
	}

	return value + value_pos;
}

void Algorithm::PutBlockSeries(array<array<int, 12>, 12> origin_map,
							   vector<Block> blocks,
							   array<array<int, 12>, 12>& new_map,
							   int& status,
							   int& score_put_delta,
							   int& score_remove_delta)
{
	Parameter para;

	DeepFirstPositionSearch(origin_map, para, blocks.begin(), blocks.end());
}


void Algorithm::DeepFirstPositionSearch(array<array<int, 12>, 12> map, Parameter theParam, vector<Block>::const_iterator iter, vector<Block>::const_iterator end_iter)
{
	if ((int)param_cache.size() >= max_param_cache_size)
	{
		return;
	}

	if (iter == end_iter)
	{
		theParam.index = parameter.size() + param_cache.size() + 1;
		theParam.new_map = map;
		theParam.new_positions = GetPositionCounts(map);
		theParam.single_count = GetSingleCount(map);
		param_cache.push_back(theParam);
		
		if (theParam.score_remove == 20)
		{
			int x;
			x = 1;
		}
		return;
	}

	Block block = *iter;

	for (int i_r = 1; i_r <= 11 - block._r; i_r++)
	{
		for (int i_c = 1; i_c <= 11 - block._c; i_c++)
		{
			bool can_be_put = IsPut(map, block, i_r, i_c);

			if (can_be_put)
			{
				Point position;
				position.r = i_r;
				position.c = i_c;

				array<array<int, 12>, 12> new_map;
				int score_remove = 0;

				PutDownBlock(map, block, i_r, i_c);
				MapRemove(map, new_map, score_remove);

				theParam.series_block.push_back(block);
				theParam.series_position.push_back(position);
				theParam.perimeter = GetPerimeter(new_map);
				theParam.score_put += block._score_put;
				theParam.score_remove += score_remove;
				iter++;

				DeepFirstPositionSearch(new_map, theParam, iter, end_iter);

				iter--;
				theParam.score_remove -= score_remove;
				theParam.score_put -= block._score_put;
				theParam.perimeter = 0;
				theParam.series_position.pop_back();
				theParam.series_block.pop_back();
				PickUpBlock(map, block, i_r, i_c);
			}
		}
	}

}

void Algorithm::PrintMap(array<array<int, 12>, 12> map)
{
	for (int i_r = 1; i_r <= 10; i_r++)
	{
		for (int i_c = 1; i_c <= 10; i_c++)
		{
			printf("%2d ", map[i_r][i_c]);
		}
		cout << endl;
	}

	cout << endl;
}