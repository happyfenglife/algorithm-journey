#include <bits/stdc++.h>

using namespace std;

// 连接棒材的最低费用(洛谷测试)
// 你有一些长度为正整数的棍子
// 这些长度以数组sticks的形式给出
// sticks[i]是第i个木棍的长度
// 你可以通过支付x+y的成本将任意两个长度为x和y的棍子连接成一个棍子
// 你必须连接所有的棍子，直到剩下一个棍子
// 返回以这种方式将所有给定的棍子连接成一个棍子的最小成本
// 测试链接 : https://www.luogu.com.cn/problem/P1090
priority_queue<int, vector<int>, greater<>> heap;
int N;

int main(int argc, char** argv)
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> N;
	for (int i = 1, k; i <= N; ++i)
	{
		cin >> k;
		heap.push(k);
	}

	int sum{};
	while (heap.size() > 1)
	{
		int a = heap.top();
		heap.pop();
		int b = heap.top();
		heap.pop();

		sum += a + b;
		heap.push(a + b);
	}

	cout << sum << endl;
	return 0;
}
