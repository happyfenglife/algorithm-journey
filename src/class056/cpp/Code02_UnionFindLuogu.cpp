#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10001;

#define MERGE 1
#define QUERY 2

const string YES = "Y";
const string NO = "N";

int father[MAXN];
int N, M, z, x, y;

void build()
{
	for (int i = 0; i <= N; ++i)
	{
		father[i] = i;
	}
}

int find(int i)
{
	if (i != father[i])
	{
		father[i] = find(father[i]);
	}

	return i;
}

void uni(int i, int j)
{
	father[find(i)] = find(j);
}

bool isSameSet(int i, int j)
{
	return find(i) == find(j);
}

// 并查集模版(洛谷)
// 本实现用递归函数实现路径压缩，而且省掉了小挂大的优化，一般情况下可以省略
// 测试链接 : https://www.luogu.com.cn/problem/P3367
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	while (cin >> N >> M)
	{
		build();

		for (int i = 0; i < M; ++i)
		{
			cin >> z >> x >> y;

			if (z == QUERY)
			{
				cout << (isSameSet(x, y) ? YES : NO) << endl;
			}
			else if (z == MERGE)
			{
				uni(x, y);
			}
		}
	}

	return 0;
}
