#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

// 完全背包(模版)
// 给定一个正数t，表示背包的容量
// 有m种货物，每种货物可以选择任意个
// 每种货物都有体积costs[i]和价值values[i]
// 返回在不超过总容量的情况下，怎么挑选货物能达到价值最大
// 返回最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1616
const int MAXM = 10001;
const int MAXT = 10000001;

int w[MAXM];
int v[MAXM];
long long dp[MAXT];

int t, m;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  while (cin >> t >> m) {
    for (int i = 1; i <= m; ++i) {
      cin >> w[i] >> v[i];
    }

    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= m; ++i) {
      for (int j = w[i]; j <= t; ++j) {
        dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
      }
    }

    cout << dp[t] << endl;
  }

  return 0;
}
