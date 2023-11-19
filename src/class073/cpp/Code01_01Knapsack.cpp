#include <iostream>
#include <cstring>

using namespace std;

// 01背包(模版)
// 给定一个正数t，表示背包的容量
// 有m个货物，每个货物可以选择一次
// 每个货物有自己的体积costs[i]和价值values[i]
// 返回在不超过总容量的情况下，怎么挑选货物能达到价值最大
// 返回最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1048

const int MAXT = 1001;
const int MAXM = 101;

int cost[MAXM];
int val[MAXM];
int dp[MAXT];

int T, M;

// 严格位置依赖的动态规划
// n个物品编号1~n，第i号物品的花费cost[i]、价值val[i]
// cost、val数组是全局变量，已经把数据读入了
// 空间压缩
int compute() {
  memset(dp, 0, sizeof(dp));

  for (int i = 1; i <= M; ++i) {
    for (int j = T; j >= cost[i]; --j) {
      dp[j] = max(dp[j], dp[j - cost[i]] + val[i]);
    }
  }

  return dp[T];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  while (cin >> T >> M) {
    for (int i = 1; i <= M; ++i) {
      cin >> cost[i] >> val[i];
    }

    cout << compute() << endl;
  }

  return 0;
}
