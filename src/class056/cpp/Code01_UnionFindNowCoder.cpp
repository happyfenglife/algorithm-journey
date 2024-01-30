#include <bits/stdc++.h>

using namespace std;

const string YES = "Yes";
const string NO = "No";
const int QUERY = 1;
const int MERGE = 2;
const int MAXN = 1'000'001;

int father[MAXN];
int sz[MAXN];
int st[MAXN];

int N, M, opt, x, y;

void build()
{
	for (int i = 0; i <= N; ++i)
	{
		father[i] = i;
		sz[i] = 1;
	}
}

// i号节点，往上一直找，找到代表节点返回！
int find(int i)
{
	// 栈顶指针
	int ptr{};
	while (i != father[i])
	{
		st[ptr++] = i;
		i = father[i];
	}

	// 沿途节点收集好了，i已经跳到代表节点了
	while (ptr)
	{
		father[st[--ptr]] = i;
	}

	return i;
}

bool isSameSet(int x, int y)
{
	return find(x) == find(y);
}

void uni(int x, int y)
{
	int fx = find(x);
	int fy = find(y);

	if (fx != fy)
	{
		// fx是集合的代表: 拿大小
		// fy是集合的代表: 拿大小
		if (sz[fx] >= sz[fy])
		{
			sz[fx] += sz[fy];
			father[fy] = fx;
		}
		else
		{
			sz[fy] += sz[fx];
			father[fx] = fy;
		}
	}
}

// 并查集模版(牛客)
// 路径压缩 + 小挂大
// 测试链接 : https://www.nowcoder.com/practice/e7ed657974934a30b2010046536a5372
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
			cin >> opt >> x >> y;

			if (opt == QUERY)
			{
				cout << (isSameSet(x, y) ? YES : NO) << endl;
			}
			else
			{
				uni(x, y);
			}
		}
	}

	return 0;
}
