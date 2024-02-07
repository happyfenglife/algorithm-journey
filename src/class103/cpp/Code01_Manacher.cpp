#include <bits/stdc++.h>

using namespace std;

// Manacher算法模版
// 求字符串s中最长回文子串的长度
// 测试链接 : https://www.luogu.com.cn/problem/P3805
const int MAXN = 11000001;

char ss[MAXN << 1];

int p[MAXN << 1];

int n;

void manacherss(string& s)
{
	n = s.size() * 2 + 1;

	for (int i = 0, j = 0; i < n; ++i)
	{
		ss[i] = (i & 1) ? s[j++] : '#';
	}
}

int manacher(string& s)
{
	manacherss(s);
	int ans = 0;

	for (int i = 0, c = 0, r = 0, len; i < n; ++i)
	{
		len = r > i ? min(p[2 * c - i], r - i) : 1;

		while (i + len < n && i - len >= 0
				&& ss[i + len] == ss[i - len])
		{
			++len;
		}
		if (len + i > r)
		{
			r = i + len;
			c = i;
		}
		ans = max(ans, len);
		p[i] = len;
	}

	return ans - 1;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	string s;
	cin >> s;
	cout << manacher(s) << endl;

	return 0;
}
