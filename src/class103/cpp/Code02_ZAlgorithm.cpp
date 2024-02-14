#include <bits/stdc++.h>

using namespace std;

// 扩展KMP模版，又称Z算法或Z函数
// 给定两个字符串a、b，求出两个数组
// b与b每一个后缀串的最长公共前缀长度，z数组
// b与a每一个后缀串的最长公共前缀长度，e数组
// 计算出要求的两个数组后，输出这两个数组的权值即可
// 对于一个数组x，i位置的权值定义为 : (i * (x[i] + 1))
// 数组权值为所有位置权值的异或和
// 测试链接 : https://www.luogu.com.cn/problem/P5410
const int MAXN = 20000001;

vector<int> z(MAXN);
vector<int> e(MAXN);

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

void eArray(string& s1, string& s2)
{
	int n = s1.size(), m = s2.size();
	for (int i = 0, c = 0, r = 0, len; i < n; ++i)
	{
		len = r > i ? min(r - i, z[i - c]) : 0;

		while (i + len < n && len < m && s1[i + len] == s2[len])
		{
			++len;
		}

		if (i + len > r)
		{
			r = i + len;
			c = i;
		}

		e[i] = len;
	}
}

using ll = long long;

ll eor(vector<int>& v, int n)
{
	ll ans = 0;
	for (int i = 0; i < n; ++i)
	{
		ans ^= (i + 1L) * (v[i] + 1);
	}

	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	string a, b;
	cin >> a >> b;

	zArray(b);
	eArray(a, b);

	cout << eor(z, b.size()) << "\n"
		 << eor(e, a.size()) << "\n";

	return 0;
}
