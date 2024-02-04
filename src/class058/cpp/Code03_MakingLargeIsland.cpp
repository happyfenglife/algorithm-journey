#include <bits/stdc++.h>

using namespace std;

// 最大人工岛
// 给你一个大小为 n * n 二进制矩阵 grid 。最多 只能将一格 0 变成 1 。
// 返回执行此操作后，grid 中最大的岛屿面积是多少？
// 岛屿 由一组上、下、左、右四个方向相连的 1 形成
// 测试链接 : https://leetcode.cn/problems/making-a-large-island/
class Solution
{
public:
	int largestIsland(vector<vector<int>>& grid)
	{
		int n = grid.size();
		int m = grid[0].size();

		int id = 2;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				if (grid[i][j] == 1)
				{
					dfs(grid, n, m, i, j, id++);
				}
			}
		}

		int sizes[id];
		memset(sizes, 0, sizeof(sizes));

		int ans = 0;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				if (grid[i][j] > 1)
				{
					ans = max(ans,
							++sizes[grid[i][j]]);
				}
			}
		}

		// 讨论所有的0，变成1，能带来的最大岛的大小
		bool visited[id];
		memset(visited, 0, sizeof(visited));

		int up, down, left, right, merge;

		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				if (!grid[i][j])
				{
					up = i > 0 ? grid[i - 1][j] : 0;
					down = i + 1 < n ? grid[i + 1][j] : 0;
					left = j > 0 ? grid[i][j - 1] : 0;
					right = j + 1 < m ? grid[i][j + 1] : 0;

					visited[up] = true;
					merge = 1 + sizes[up];

					if (!visited[down])
					{
						merge += sizes[down];
						visited[down] = true;
					}
					if (!visited[left])
					{
						merge += sizes[left];
						visited[left] = true;
					}
					if (!visited[right])
					{
						merge += sizes[right];
						visited[right] = true;
					}

					ans = max(ans, merge);
					visited[up] = visited[down]
							= visited[left]
							= visited[right] = false;
				}
			}
		}

		return ans;
	}

	void dfs(vector<vector<int>>& grid, int n, int m, int i, int j, int id)
	{
		if (i < 0 || i == n
				|| j < 0 || j == m
				|| grid[i][j] != 1)
		{
			return;
		}

		grid[i][j] = id;
		dfs(grid, n, m, i - 1, j, id);
		dfs(grid, n, m, i + 1, j, id);
		dfs(grid, n, m, i, j - 1, id);
		dfs(grid, n, m, i, j + 1, id);
	}
};
