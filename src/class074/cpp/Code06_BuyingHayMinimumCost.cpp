#include <iostream>
#include <cstring>

using namespace std;

// 购买足量干草的最小花费
// 有n个提供干草的公司，每个公司都有两个信息
// cost[i]代表购买1次产品需要花的钱
// val[i]代表购买1次产品所获得的干草数量
// 每个公司的产品都可以购买任意次
// 你一定要至少购买h数量的干草，返回最少要花多少钱
// 测试链接 : https://www.luogu.com.cn/problem/P2918
const int MAXN = 101;
const int MAXM = 55001;

int val[MAXN];
int cost[MAXN];
int dp[MAXM];

int n, h, maxv, m;

// dp[i][j] : 1...i里挑公司，购买严格j磅干草，需要的最少花费
// 1) dp[i-1][j]
// 2) dp[i][j-val[i]] + cost[i]
// 两种可能性中选最小
int compute() {
  memset(dp, 0x3f, sizeof(dp));
  dp[0] = 0;

  for (int i = 1; i <= n; ++i) {
    for (int j = val[i]; j <= m; ++j) {
      if (dp[j - val[i]] != 0x3f3f3f3f) {
        dp[j] = min(dp[j], dp[j - val[i]] + cost[i]);
      }
    }
  }

  int ans = INT_MAX;
  for (int j = h; j <= m; ++j) {
    ans = min(ans, dp[j]);
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  while (cin >> n >> h) {
    maxv = 0;

    for (int i = 1; i <= n; ++i) {
      cin >> val[i] >> cost[i];
      maxv = max(maxv, val[i]);
    }

    // 最核心的一句
    // 包含重要分析
    m = h + maxv;
    cout << compute() << endl;
  }

  return 0;
}
