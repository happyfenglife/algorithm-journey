#include <iostream>
#include <cstring>

using namespace std;

// 让字符串成为回文串的最少插入次数
// 给你一个字符串 s
// 每一次操作你都可以在字符串的任意位置插入任意字符
// 请你返回让s成为回文串的最少操作次数
// 测试链接 : https://leetcode.cn/problems/minimum-insertion-steps-to-make-a-string-palindrome/
class Solution {
 public:
  // 暴力尝试
  static int minInsertions(const string &s) {
    return f1(s, 0, s.length() - 1);
  }

  static int minInsertions2(const string &s) {
    int n = s.size();
    if (n < 2) {
      return 0;
    }

    int dp[n];
    memset(dp, 0, sizeof(dp));
    dp[n - 1] = s[n - 2] != s[n - 1];

    for (int l = n - 3, leftDown, backup; l >= 0; --l) {
      leftDown = dp[l + 1];
      dp[l + 1] = s[l] != s[l + 1];

      for (int r = l + 2; r < n; ++r) {
        backup = dp[r];

        if (s[l] == s[r]) {
          dp[r] = leftDown;
        } else {
          dp[r] = min(dp[r - 1], dp[r]) + 1;
        }

        leftDown = backup;
      }
    }

    return dp[n - 1];
  }

 private:
  // s[l....r]这个范围上的字符串，整体都变成回文串
  // 返回至少插入几个字符
  static int f1(const string &s, int l, int r) {
    if (l == r) {
      return 0;
    }

    if (l + 1 == r) {
      return s[l] != s[r];
    }

    // l...r不只两个字符
    if (s[l] == s[r]) {
      return f1(s, l + 1, r - 1);
    } else {
      return min(f1(s, l, r - 1), f1(s, l + 1, r)) + 1;
    }
  }
};
