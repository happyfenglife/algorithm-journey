#include <bits/stdc++.h>

using namespace std;

// KMP算法模版
// 测试链接 : https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/
class Solution
{
public:
	int strStr(string& s1, string& s2)
	{
		int n = s1.size();
		int m = s2.size();
		int x = 0, y = 0;

		// O(M)
		vector<int> next = nextArray(s2);
		// O(N)
		while (x < n && y < m)
		{
			if (s1[x] == s2[y])
			{
				++x, ++y;
			}
			else if (!y)
			{
				++x;
			}
			else
			{
				y = next[y];
			}
		}

		return y == m ? x - y : -1;
	}

	// 得到next数组
	vector<int> nextArray(string& s)
	{
		int m = s.size();
		if (m == 1)
		{
			return { -1 };
		}

		vector<int> next(m);
		next[0] = -1;

		// i 表示当前要求 next值的位置
		// cn 表示当前要和前一个字符比对的下标
		int i = 2, cn = 0;
		while (i < m)
		{
			if (s[i - 1] == s[cn])
			{
				next[i++] = ++cn;
			}
			else if (cn > 0)
			{
				cn = next[cn];
			}
			else
			{
				next[i++] = 0;
			}
		}

		return next;
	}
};
