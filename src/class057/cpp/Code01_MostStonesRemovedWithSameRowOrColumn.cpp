#include <bits/stdc++.h>

using namespace std;

// 移除最多的同行或同列石头
// n 块石头放置在二维平面中的一些整数坐标点上。每个坐标点上最多只能有一块石头
// 如果一块石头的 同行或者同列 上有其他石头存在，那么就可以移除这块石头
// 给你一个长度为 n 的数组 stones ，其中 stones[i] = [xi, yi] 表示第 i 块石头的位置
// 返回 可以移除的石子 的最大数量。
// 测试链接 : https://leetcode.cn/problems/most-stones-removed-with-same-row-or-column/
class Solution
{
public:
	int removeStones(vector<vector<int>>& stones)
	{
		int n = stones.size();
		build(n);

		for (int i = 0; i < n; ++i)
		{
			int r = stones[i][0];
			int c = stones[i][1];

			if (rows[r] != -1)
			{
				uni(i, rows[r]);
			}
			else
			{
				rows[r] = i;
			}

			if (cols[c] != -1)
			{
				uni(i, cols[c]);
			}
			else
			{
				cols[c] = i;
			}
		}

		return n - sets;
	}

	void build(int n)
	{
		memset(rows, 0xff, sizeof(rows));
		memset(cols, 0xff, sizeof(cols));
		for (int i = 0; i < n; ++i)
		{
			father[i] = i;
		}

		sets = n;
	}

	int find(int i)
	{
		if (i != father[i])
		{
			father[i] = find(father[i]);
		}

		return father[i];
	}

	void uni(int i, int j)
	{
		int fi = find(i);
		int fj = find(j);

		if (fi != fj)
		{
			father[fi] = fj;
			--sets;
		}
	}

public:
	int rows[10'001];
	int cols[10'001];
	int father[1'001];
	int sets;
};
