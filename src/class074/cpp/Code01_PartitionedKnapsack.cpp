#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

// 分组背包(模版)
// 给定一个正数m表示背包的容量，有n个货物可供挑选
// 每个货物有自己的体积(容量消耗)、价值(获得收益)、组号(分组)
// 同一个组的物品只能挑选1件，所有挑选物品的体积总和不能超过背包容量
// 怎么挑选货物能达到价值最大，返回最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1757
const int MAXM = 1001;
const int MAXN = 1001;

vector<vector<int>> arr(MAXN, vector<int>(3));
int dp[MAXM];

int m, n;

int compute() {
  memset(dp, 0, sizeof(dp));

  for (int start = 1, end = 2; start <= n;) {
    while (end <= n && arr[end][2] == arr[start][2]) {
      ++end;
    }

    // start....end - 1
    for (int j = m; j >= 1; --j) {
      for (int k = start; k < end; ++k) {
        if (j - arr[k][0] >= 0) {
          dp[j] = max(dp[j], arr[k][1] + dp[j - arr[k][0]]);
        }
      }
    }

    start = end++;
  }

  return dp[m];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  while (cin >> m >> n) {
    for (int i = 1; i <= n; ++i) {
      cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
    }

    sort(arr.begin() + 1, arr.begin() + 1 + n, [&](auto &o1, auto &o2) noexcept {
      return o1[2] < o2[2];
    });

    cout << compute() << endl;
  }

  return 0;
}
