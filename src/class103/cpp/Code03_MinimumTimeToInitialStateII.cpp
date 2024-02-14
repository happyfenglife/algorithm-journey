#include <bits/stdc++.h>

using namespace std;

// 将单词恢复初始状态所需的最短时间II
// 给你一个下标从0开始的字符串word和一个整数k
// 在每一秒，必须执行以下操作
// 移除word的前k个字符
// 在word的末尾添加k个任意字符
// 添加的字符不必和移除的字符相同
// 返回将word恢复到初始状态所需的最短时间
// 该时间必须大于零
// 测试链接 : https://leetcode.cn/problems/minimum-time-to-revert-word-to-initial-state-ii/
class Solution
{
public:
	int z[1000001];

public:
	int minimumTimeToInitialState(string& s, int k)
	{
		zArray(s);
		int n = s.size();

		for (int i = k; i < n; i += k)
		{
			if (z[i] == n - i)
			{
				return i / k;
			}
		}

		return (n + k - 1) / k;
	}

	void zArray(string& s)
	{
		int n = s.size();
		z[0] = n;

		for (int i = 1, c = 1, r = 1, len; i < n; ++i)
		{
			len = r > i ? min(r - i, z[i - c]) : 0;

			while (i + len < n && s[i + len] == s[len])
			{
				++len;
			}

			if (i + len > r)
			{
				r = i + len;
				c = i;
			}

			z[i] = len;
		}
	}
};
