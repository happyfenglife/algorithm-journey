#include <bits/stdc++.h>

using namespace std;

// 不停删除之后剩下的字符串
// 给定一个字符串s1，如果其中含有s2字符串，就删除最左出现的那个
// 删除之后s1剩下的字符重新拼接在一起，再删除最左出现的那个
// 如此周而复始，返回最终剩下的字符串
// 测试链接 : https://www.luogu.com.cn/problem/P4824
const int MAXN = 1000001;

int next_[MAXN];

int st1[MAXN];
int st2[MAXN];

int sz;

string s1, s2;

void nextArray(int m)
{
	next_[0] = -1;
	next_[1] = 0;
	int i = 2, cn = 0;

	while (i < m)
	{
		if (s2[i - 1] == s2[cn])
		{
			next_[i++] = ++cn;
		}
		else if (cn > 0)
		{
			cn = next_[cn];
		}
		else
		{
			next_[i++] = 0;
		}
	}
}

void compute()
{
	sz = 0;
	int n = s1.size(), m = s2.size(), x = 0, y = 0;
	nextArray(m);

	while (x < n)
	{
		if (s1[x] == s2[y])
		{
			st1[sz] = x;
			st2[sz] = y;
			++sz;
			++x;
			++y;
		}
		else if (y == 0)
		{
			st1[sz] = x;
			st2[sz] = -1;
			++sz;
			++x;
		}
		else
		{
			y = next_[y];
		}

		if (y == m)
		{
			// 相当于栈直接弹出了m条记录
			sz -= m;
			y = sz > 0 ? (st2[sz - 1] + 1) : 0;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> s1 >> s2;
	compute();

	for (int i = 0; i < sz; ++i)
	{
		cout << s1[st1[i]];
	}

	cout << "\n";
	return 0;
}
