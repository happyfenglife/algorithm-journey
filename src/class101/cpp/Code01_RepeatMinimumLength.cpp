#include <bits/stdc++.h>

using namespace std;

// 最短循环节的长度
// 给你一个字符串s，它一定是由某个循环节不断自我连接形成的
// 题目保证至少重复2次，但是最后一个循环节不一定完整
// 现在想知道s的最短循环节是多长
// 测试链接 : https://www.luogu.com.cn/problem/P4391
const int MAXN = 1000001;

int next_[MAXN];

int n;

string s;

void nextArray()
{
	next_[0] = -1;
	next_[1] = 0;

	int i = 2, cn = 0;
	while (i <= n)
	{
		if (s[i - 1] == s[cn])
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

int compute()
{
	nextArray();

	return n - next_[n];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> n >> s;

	cout << compute() << "\n";
	return 0;
}
