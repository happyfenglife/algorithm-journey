#include <iostream>

using namespace std;

// 合唱队
// 具体描述情打开链接查看
// 测试链接 : https://www.luogu.com.cn/problem/P3205
const int MAXN = 1001;
const int MOD = 19650827;

int nums[MAXN];
int dp[MAXN][2];

int n;

int compute() {
  int dp[n + 1][n + 1][2];
  for (int i = 1; i < n; ++i) {
    if (nums[i] < nums[i + 1]) {
      dp[i][i + 1][0] = 1;
      dp[i][i + 1][1] = 1;
    }
  }

  for (int l = n - 2; l >= 1; --l) {
    for (int r = l + 2; r <= n; ++r) {
      if (nums[l] < nums[l + 1]) {
        dp[l][r][0] = (dp[l][r][0] + dp[l + 1][r][0]) % MOD;
      }

      if (nums[l] < nums[r]) {
        dp[l][r][0] = (dp[l][r][0] + dp[l + 1][r][1]) % MOD;
        dp[l][r][1] = (dp[l][r][1] + dp[l][r - 1][0]) % MOD;
      }

      if (nums[r] > nums[r - 1]) {
        dp[l][r][1] = (dp[l][r][1] + dp[l][r - 1][1]) % MOD;
      }
    }
  }

  return (dp[1][n][0] + dp[1][n][1]) % MOD;
}

int compute2() {
  if (nums[n - 1] < nums[n]) {
    dp[n][0] = 1;
    dp[n][1] = 1;
  }

  for (int l = n - 2; l >= 1; --l) {
    if (nums[l] < nums[l + 1]) {
      dp[l + 1][0] = dp[l + 1][1] = 1;
    } else {
      dp[l + 1][0] = dp[l + 1][1] = 0;
    }

    for (int r = l + 2; r <= n; ++r) {
      int a = 0;
      int b = 0;
      if (nums[l] < nums[l + 1]) {
        a = (a + dp[r][0]) % MOD;
      }

      if (nums[l] < nums[r]) {
        a = (a + dp[r][1]) % MOD;
        b = (b + dp[r - 1][0]) % MOD;
      }

      if (nums[r] > nums[r - 1]) {
        b = (b + dp[r - 1][1]) % MOD;
      }

      dp[r][0] = a;
      dp[r][1] = b;
    }
  }

  return (dp[n][0] + dp[n][1]) % MOD;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> nums[i];
  }

  if (n == 1) {
    cout << 1 << endl;
  } else {
    cout << compute() << endl;
  }

  return 0;
}
