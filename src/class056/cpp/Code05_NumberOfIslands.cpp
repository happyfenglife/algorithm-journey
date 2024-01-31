#include <bits/stdc++.h>

using namespace std;

// 岛屿数量
// 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量
// 岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成
// 此外，你可以假设该网格的四条边均被水包围
// 测试链接 : https://leetcode.cn/problems/number-of-islands/
class Solution
{
public:
	int numIslands(vector<vector<char>>& grid)
	{
		int n = grid.size();
		int m = grid[0].size();

		build(n, m, grid);
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0, k; j < m; ++j)
			{
				if (grid[i][j] == '1')
				{
					if (j > 0 && grid[i][j - 1] == '1')
					{
						uni(i, j, i, j - 1);
					}
					if (i > 0 && grid[i - 1][j] == '1')
					{
						uni(i, j, i - 1, j);
					}
				}
			}
		}

		return sets;
	}

	int index(int i, int j)
	{
		return i * cols + j;
	}

	int find(int i)
	{
		if (i != father[i])
		{
			father[i] = find(father[i]);
		}

		return father[i];
	}

	void uni(int i, int j, int x, int y)
	{
		int fx = find(index(i, j));
		int fy = find(index(x, y));

		if (fx != fy)
		{
			father[fx] = fy;
			--sets;
		}
	}

	void build(int n, int m, vector<vector<char>>& grid)
	{
		cols = m;
		sets = 0;

		for (int i = 0; i < n; ++i)
		{
			for (int j = 0, k; j < m; ++j)
			{
				if (grid[i][j] == '1')
				{
					++sets;
					k = index(i, j);
					father[k] = k;
				}
			}
		}
	}

public:
	int father[90001];
	int cols;
	int sets;
};
