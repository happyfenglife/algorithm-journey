#include <iostream>

using namespace std;

// 多重背包单调队列优化
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
int queue[MAXW];
int l, r;
int n, t;

// s的容量用来装i号商品，可以得到多少价值
int inc(int s, int i) {
  return s / w[i] * v[i];
}

int compute() {
  int dp[n + 1][t + 1];

  for (int i = 1; i <= n; ++i) {
    for (int mod = 0; mod <= min(t, w[i] - 1); ++mod) {
      l = r = 0;

      for (int j = mod; j <= t; j += w[i]) {
        while (l < r && dp[i - 1][queue[r - 1]] + inc(j - queue[r - 1], i) <= dp[i - 1][j]) {
          // queue[r - 1] 是队列尾部的列号 vs j这个列号
          // 指标之间pk
          --r;
        }

        queue[r++] = j;
        if (queue[l] == j - w[i] * (c[i] + 1)) {
          // 检查单调队列的最左列号是否过期
          // 比如
          // i号物品，重量为3，个数4
          // queue[l]是队列头部的列号，假设是2
          // 当j == 17时，依赖的格子为dp[i-1][17、14、11、8、5]
          // 所以此时头部的列号2，过期了，要弹出
          ++l;
        }

        // dp[i][j] = dp[i - 1][拥有最强指标的列] + (j - 拥有最强指标的列) / w[i] * v[i]
        dp[i][j] = dp[i - 1][queue[l]] + inc(j - queue[l], i);
      }
    }
  }

  return dp[n][t];
}

// 单调队列优化枚举 + 空间压缩
int compute2() {
  for (int i = 1; i <= n; ++i) {
    for (int mod = 0; mod <= min(t, w[i] - 1); ++mod) {
      // 因为空间压缩时，关于j的遍历是从右往左，而不是从左往右
      // 所以先让dp[i - 1][...右侧的几个位置进入窗口]
      l = r = 0;

      for (int j = t - mod, k = 0; j >= 0 && k <= c[i]; j -= w[i], ++k) {
        while (l < r && dp[j] + inc(queue[r - 1] - j, i) >= dp[queue[r - 1]]) {
          --r;
        }

        queue[r++] = j;
      }

      // 然后j开始从右向左遍历
      // 注意: 因为j从右从向左遍历，所以
      // 更靠右的j位置更早进入窗口，更靠左的j位置更晚进入
      for (int j = t - mod; j >= 0; j -= w[i]) {
        dp[j] = dp[queue[l]] + inc(j - queue[l], i);

        // 求解完dp[j]
        // 求解dp[j - w[i]](根据余数分组)
        // 窗口最左的下标是不是j
        // 是的话，说明最左下标过期了，要弹出
        if (queue[l] == j) {
          ++l;
        }

        // 最后，新的dp[i - 1][enter]要进入窗口
        int enter = j - w[i] * (c[i] + 1);
        if (enter >= 0) {
          while (l < r && dp[enter] + inc(queue[r - 1] - enter, i) >= dp[queue[r - 1]]) {
            --r;
          }

          queue[r++] = enter;
        }
      }
    }
  }

  return dp[t];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> t;

  for (int i = 1; i <= n; ++i) {
    cin >> v[i] >> w[i] >> c[i];
  }

  cout << compute() << endl;
  return 0;
}
