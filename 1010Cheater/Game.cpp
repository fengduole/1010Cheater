#include "Game.h"


Game::Game()
{
	// initialize variables
	score = score_put = score_remove = 0;
	times = 0;
	block_history.clear();
	
	LoadBlock();

	srand((unsigned)time(NULL));
}

void Game::InitializeMap(void)
{
	for (int i_r = 0; i_r < 12; i_r++)
	{
		for (int i_c = 0; i_c < 12; i_c++)
		{
			map[i_r][i_c] = -1;
		}
	}

	for (int i_r = 1; i_r <= 10; i_r++)
	{
		for (int i_c = 1; i_c <= 10; i_c++)
		{
			map[i_r][i_c] = 0;
		}
	}
}

int Game::Simulation(int alg)
{
	MAP next_step_map;
	vector<Block> three_blocks;
	Algorithm algorithm;
	int score = 0,
		score_put_delta = 0,
		score_remove_delta = 0;
	int status = -1;

	algorithm.SetBlockList(block_list);
	InitializeMap();

	while (true)
	{
		score_put_delta = 0;
		score_remove_delta = 0;
		status = -1;
		
		times++;

		three_blocks = RandomThreeBlocks(times);

		if (alg == 1)
		{
			algorithm.Alg_Recursive(map, three_blocks, next_step_map, status, score_put_delta, score_remove_delta);
		}
		else if (alg == 2)
		{
			algorithm.Alg_Circulation(map, three_blocks, next_step_map, status, score_put_delta, score_remove_delta);
		}
		
		if (status == 1)
		{
			cout << "DEAD" << endl;
			MapDisplay(times + 1);
			printf("%2d %2d %2d\n", three_blocks[0]._id, three_blocks[1]._id, three_blocks[2]._id);
			return score;
		}
		
		map = next_step_map;

		score += score_put_delta + score_remove_delta;

		printf("%4d:  %5d   +%2d (%2d %2d %2d)  +%2d\n", times, score, score_put_delta, three_blocks[0]._id, three_blocks[1]._id, three_blocks[2]._id, score_remove_delta);
	}

	return score;
}

int Game::Cheat(void)
{
	int block_id[3];
	MAP next_step_map;
	vector<Block> three_blocks;
	Algorithm algorithm;
	int score = 0,
		score_put_delta = 0,
		score_remove_delta = 0;
	int status = -1;
		
	algorithm.SetBlockList(block_list);
	InitializeMap();
	

	while (true)
	{
		score_put_delta = 0;
		score_remove_delta = 0;
		status = -1;

		times++;

		for (int i = 0; i < 3; i++)
		{
			cin >> block_id[i];
		}	

		three_blocks = SelectThreeBlocks(times, block_id);
		algorithm.Alg_Recursive(map, three_blocks, next_step_map, status, score_put_delta, score_remove_delta);

		if (status == 1)
		{
			cout << "DEAD" << endl;
			return score;
		}

		map = next_step_map;
		score += score_put_delta + score_remove_delta;
		printf("%2d:  %5d   +%2d (%2d %2d %2d)  +%2d\n", times, score, score_put_delta, three_blocks[0]._id, three_blocks[1]._id, three_blocks[2]._id, score_remove_delta);

		MapDisplay(times);
	}
}

int Game::ListInput(int alg)
{
	ifstream in_file("block_list.txt");
	int block_id[3];
	MAP next_step_map;
	vector<Block> three_blocks;
	Algorithm algorithm;
	int score = 0,
		score_put_delta = 0,
		score_remove_delta = 0;
	int status = -1;

	algorithm.SetBlockList(block_list);
	InitializeMap();

	while (!in_file.eof())
	{
		score_put_delta = 0;
		score_remove_delta = 0;
		status = -1;

		times++;

		for (int i = 0; i < 3; i++)
		{
			in_file >> block_id[i];
		}

		three_blocks = SelectThreeBlocks(times, block_id);

		if (alg == 1)
		{
			algorithm.Alg_Recursive(map, three_blocks, next_step_map, status, score_put_delta, score_remove_delta);
		}
		else if (alg == 2)
		{
			algorithm.Alg_Circulation(map, three_blocks, next_step_map, status, score_put_delta, score_remove_delta);
		}

		if (status == 1)
		{
			cout << "DEAD" << endl;
			MapDisplay(times + 1);
			printf("%2d %2d %2d\n", three_blocks[0]._id, three_blocks[1]._id, three_blocks[2]._id);
			
			in_file.close();
			return score;
		}

		map = next_step_map;

		score += score_put_delta + score_remove_delta;

		printf("%4d:  %5d   +%2d (%2d %2d %2d)  +%2d\n", times, score, score_put_delta, three_blocks[0]._id, three_blocks[1]._id, three_blocks[2]._id, score_remove_delta);
	}

	in_file.close();
	return score;
}

vector<Block> Game::RandomThreeBlocks(int times)
{
	vector<Block> group;

	for (int i = 1; i <= 3; i++)
	{
		int selected_index = rand() % block_list.size();

		Block block = block_list[selected_index];
		block._times_index = times;
		
		group.push_back(block);
	}

	return group;
}

vector<Block> Game::SelectThreeBlocks(int times, int id[])
{
	vector<Block> group;

	for (int i = 1; i <= 3; i++)
	{
		int selected_index = id[i - 1] - 1;

		Block block = block_list[selected_index];
		block._times_index = times;

		group.push_back(block);
	}

	return group;
}

void Game::MapDisplay(int times)
{
	for (int i_r = 1; i_r <= 10; i_r++)
	{
		for (int i_c = 1; i_c <= 10; i_c++)
		{
			if (map[i_r][i_c] == 0)
			{
				printf(". ");
			}
			else if (map[i_r][i_c] > (times - 1) * 3)
			{
				printf("%d ", map[i_r][i_c] - (times - 1) * 3);
			}
			else
			{
				printf("* ");
			}
		}
		cout << endl;
	}
}

/* 
 * read block config from the file 
 */
void Game::LoadBlock()
{
	fstream in_file(block_file_name);
	int n_block;

	in_file >> n_block;

	for (int i = 1; i <= n_block; i++)
	{
		int r, c;
		int shape_map[5][5];

		in_file >> r >> c;

		for (int i_r = 0; i_r < r; i_r++)
		{
			for (int i_c = 0; i_c < c; i_c++)
			{
				in_file >> shape_map[i_r][i_c];
			}
		}

		Block theBlock;
		theBlock.SetBlock(i, r, c, shape_map);

		block_list.push_back(theBlock);
	}

	in_file.close();
}