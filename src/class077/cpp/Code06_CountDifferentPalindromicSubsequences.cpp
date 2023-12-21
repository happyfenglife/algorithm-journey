#include <vector>
#include <string>

using namespace std;

// 统计不同回文子序列
// 给你一个字符串s，返回s中不同的非空回文子序列个数
// 由于答案可能很大，请你将答案对10^9+7取余后返回
// 测试链接 : https://leetcode.cn/problems/count-different-palindromic-subsequences/
class Solution {
 public:
  static int countPalindromicSubsequences(const string &s) {
    const int MOD = 1000000007;
    int n = s.size();
    vector<int> last(256, -1);
    // left[i] : i位置的左边和s[i]字符相等且最近的位置在哪，不存在就是-1
    vector<int> left(n);
    for (int i = 0; i < n; ++i) {
      left[i] = last[s[i]];
      last[s[i]] = i;
    }

    fill(last.begin(), last.end(), n);
    // right[i] : i位置的右边和s[i]字符相等且最近的位置在哪，不存在就是n
    vector<int> right(n, n);
    for (int i = n - 1; i >= 0; --i) {
      right[i] = last[s[i]];
      last[s[i]] = i;
    }

    // dp[i][j] : i...j范围上有多少不同的回文子序列
    // 如果i>j，那么认为是无效范围dp[i][j] = 0
    vector<vector<long long>> dp(n, vector<long long>(n));
    for (int i = 0; i < n; ++i) {
      dp[i][i] = 1;
    }

    for (int i = n - 2, l, r; i >= 0; --i) {
      for (int j = i + 1; j < n; ++j) {
        if (s[i] != s[j]) {
          // a ..... b
          // i       j
          dp[i][j] = dp[i][j - 1] + dp[i + 1][j] - dp[i + 1][j - 1] + MOD;
        } else {
          // s[i] == s[j]
          // a......a
          // i      j
          l = right[i];
          r = left[j];

          if (l > r) {
            // i...j的内部没有s[i]字符
            // a....a
            // i    j
            // (i+1..j-1) + a(i+1..j-1)a + a + aa
            dp[i][j] = dp[i + 1][j - 1] * 2 + 2;
          } else if (l == r) {
            // i...j的内部有一个s[i]字符
            // a.....a......a
            // i     lr     j
            // (i+1..j-1) + a(i+1..j-1)a + aa
            dp[i][j] = dp[i + 1][j - 1] * 2 + 1;
          } else {
            // i...j的内部不只一个s[i]字符
            // a...a....这内部可能还有a但是不重要....a...a
            // i   l                               r   j
            dp[i][j] = dp[i + 1][j - 1] * 2 - dp[l + 1][r - 1] + MOD;
          }
        }

        dp[i][j] %= MOD;
      }
    }

    return dp[0][n - 1];
  }
};
