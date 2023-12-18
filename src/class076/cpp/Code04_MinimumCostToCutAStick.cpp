#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 切棍子的最小成本
// 有一根长度为n个单位的木棍，棍上从0到n标记了若干位置
// 给你一个整数数组cuts，其中cuts[i]表示你需要将棍子切开的位置
// 你可以按顺序完成切割，也可以根据需要更改切割的顺序
// 每次切割的成本都是当前要切割的棍子的长度，切棍子的总成本是历次切割成本的总和
// 对棍子进行切割将会把一根木棍分成两根较小的木棍
// 这两根木棍的长度和就是切割前木棍的长度
// 返回切棍子的最小总成本
// 测试链接 : https://leetcode.cn/problems/minimum-cost-to-cut-a-stick/
class Solution {
 public:
  static int minCost(int n, vector<int> &cuts) {
    int m = cuts.size();
    sort(cuts.begin(), cuts.end());
    cuts.insert(cuts.begin(), 0);
    cuts.push_back(n);

    vector<vector<int>> dp(m + 2, vector<int>(m + 2, -1));
    return f(cuts, 1, m, dp);
  }

  static int minCost2(int n, vector<int> &cuts) {
    int m = cuts.size();
    sort(cuts.begin(), cuts.end());
    cuts.insert(cuts.begin(), 0);
    cuts.push_back(n);

    vector<vector<int>> dp(m + 2, vector<int>(m + 2));

    for (int i = 1; i <= m; ++i) {
      dp[i][i] = cuts[i + 1] - cuts[i - 1];
    }

    for (int l = m - 1, next; l >= 1; --l) {
      for (int r = l + 1; r <= m; ++r) {
        next = INT_MAX;

        for (int k = l; k <= r; ++k) {
          next = min(next, dp[l][k - 1] + dp[k + 1][r]);
        }

        dp[l][r] = cuts[r + 1] - cuts[l - 1] + next;
      }
    }

    return dp[1][m];
  }

 private:
  // 切点[l....r]，决定一个顺序
  // 让切点都切完，总代价最小
  static int f(vector<int> &cuts, int l, int r, vector<vector<int>> &dp) {
    if (l > r) {
      return 0;
    }

    if (l == r) {
      return cuts[r + 1] - cuts[l - 1];
    }

    if (dp[l][r] != -1) {
      return dp[l][r];
    }

    int ans = INT_MAX;
    for (int k = l; k <= r; ++k) {
      ans = min(ans, f(cuts, l, k - 1, dp) + f(cuts, k + 1, r, dp));
    }

    ans += cuts[r + 1] - cuts[l - 1];
    return dp[l][r] = ans;
  }
};
