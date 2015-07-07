#include "Block.h"


Block::Block()
{
	_id = -1;
	_r = _c = 0;
	_times_index = 0;
	_series_index = 0;
	_score_put = 0;

	memset(_shape_map, 0, sizeof(_shape_map));
}

void Block::SetBlock(int id, int r, int c, int map[5][5])
{
	_id = id;
	_r = r;
	_c = c;

	_score_put = 0;

	for (int i_r = 0; i_r < r; i_r++)
	{
		for (int i_c = 0; i_c < c; i_c++)
		{
			_shape_map[i_r][i_c] = map[i_r][i_c];

			if (map[i_r][i_c])
				_score_put++;
		}
	}
}