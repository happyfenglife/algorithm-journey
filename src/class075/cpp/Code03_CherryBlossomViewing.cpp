#include <iostream>
#include <cstring>

using namespace std;

// 观赏樱花
// 给定一个背包的容量t，一共有n种货物，并且给定每种货物的信息
// 花费(cost)、价值(val)、数量(cnt)
// 如果cnt == 0，代表这种货物可以无限选择
// 如果cnt > 0，那么cnt代表这种货物的数量
// 挑选货物的总容量在不超过t的情况下，返回能得到的最大价值
// 背包容量不超过1000，每一种货物的花费都>0
// 测试链接 : https://www.luogu.com.cn/problem/P1833
const int MAXN = 100001;
const int MAXW = 1001;
const int ENOUGH = 1001;

int v[MAXN];
int w[MAXN];
int dp[MAXW];
int hour1, minute1, hour2, minute2;
char c;
int t, n, m;

int compute() {
  memset(dp, 0, sizeof(dp));

  for (int i = 1; i <= m; ++i) {
    for (int j = t; j >= w[i]; j--) {
      dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    }
  }

  return dp[t];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> hour1 >> c >> minute1;
  cin >> hour2 >> c >> minute2;
  cin >> n;

  if (minute1 > minute2) {
    --hour2;
    minute2 += 60;
  }

  // 计算背包容量
  t = (hour2 - hour1) * 60 + minute2 - minute1;
  m = 0;

  for (int i = 0, cost, val, cnt; i < n; ++i) {
    cin >> cost >> val >> cnt;

    if (!cnt) {
      cnt = ENOUGH;
    }

    // 二进制分组
    for (int k = 1; k <= cnt; k <<= 1) {
      v[++m] = k * val;
      w[m] = k * cost;
      cnt -= k;
    }

    if (cnt > 0) {
      v[++m] = cnt * val;
      w[m] = cnt * cost;
    }
  }

  cout << compute() << endl;
  return 0;
}
