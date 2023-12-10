#include <iostream>

using namespace std;

// 多重背包不进行枚举优化
// 宝物筛选
// 一共有n种货物, 背包容量为t
// 每种货物的价值(v[i])、重量(w[i])、数量(c[i])都给出
// 请返回选择货物不超过背包容量的情况下，能得到的最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1776
const int MAXN = 101;
const int MAXW = 40001;

int v[MAXN];
int w[MAXN];
int c[MAXN];
int dp[MAXW];

int n, t;

// 空间压缩
// 没有优化枚举
// 时间复杂度O(n * t * 每种商品的平均个数)
int compute() {
  for (int i = 1; i <= n; ++i) {
    for (int j = t; j >= 0; --j) {
      for (int k = 1; k <= c[i] && w[i] * k <= j; ++k) {
        dp[j] = max(dp[j], dp[j - k * w[i]] + k * v[i]);
      }
    }
  }

  return dp[t];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  while (cin >> n >> t) {
    for (int i = 1; i <= n; ++i) {
      cin >> v[i] >> w[i] >> c[i];
    }

    cout << compute() << endl;
  }

  return 0;
}
