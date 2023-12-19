#include <iostream>
#include <climits>
#include <vector>

using namespace std;

// 完成配对需要的最少字符数量
// 给定一个由'['、']'、'('，')'组成的字符串
// 请问最少插入多少个括号就能使这个字符串的所有括号正确配对
// 例如当前串是 "([[])"，那么插入一个']'即可满足
// 输出最少需要插入多少个字符
// 测试链接 : https://www.nowcoder.com/practice/e391767d80d942d29e6095a935a5b96b
int f(const string &s, int l, int r, vector<vector<int>> &dp) {
  if (l == r) {
    return 1;
  }

  if (l == r - 1) {
    if ((s[l] == '(' && s[r] == ')') || (s[l] == '[' && s[r] == ']')) {
      return 0;
    }

    return 2;
  }

  if (dp[l][r] != -1) {
    return dp[l][r];
  }

  // 可能性1: [l,r]本来就是配对的
  int p1 = INT_MAX;
  if ((s[l] == '(' && s[r] == ')') || (s[l] == '[' && s[r] == ']')) {
    p1 = f(s, l + 1, r - 1, dp);
  }

  // 可能性1: [l,r]本来就是配对的
  int p2 = INT_MAX;
  for (int m = l; m < r; ++m) {
    p2 = min(p2, f(s, l, m, dp) + f(s, m + 1, r, dp));
  }

  return dp[l][r] = min(p1, p2);
}

int compute(const string &str) {
  int n = str.size();
  vector<vector<int>> dp(n, vector<int>(n, -1));

  return f(str, 0, n - 1, dp);
}

int compute2(const string &s) {
  int n = s.size();
  vector<vector<int>> dp(n, vector<int>(n, INT_MAX));

  for (int i = 0; i < n - 1; ++i) {
    dp[i][i] = 1;
    dp[i][i + 1] = (s[i] == '(' && s[i + 1] == ')') || (s[i] == '[' && s[i + 1] == ']') ? 0 : 2;
  }

  dp[n - 1][n - 1] = 1;

  for (int l = n - 3; l >= 0; --l) {
    for (int r = l + 2; r < n; ++r) {
      if ((s[l] == '(' && s[r] == ')') || (s[l] == '[' && s[r] == ']')) {
        dp[l][r] = dp[l + 1][r - 1];
      }

      for (int m = l; m < r; ++m) {
        dp[l][r] = min(dp[l][r], dp[l][m] + dp[m + 1][r]);
      }
    }
  }

  return dp[0][n - 1];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string str;
  cin >> str;

  cout << compute2(str) << endl;
  return 0;
}
