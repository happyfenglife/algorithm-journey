#include <iostream>
#include <vector>

using namespace std;

// 布尔运算
// 给定一个布尔表达式和一个期望的布尔结果 result
// 布尔表达式由 0 (false)、1 (true)、& (AND)、 | (OR) 和 ^ (XOR) 符号组成
// 布尔表达式一定是正确的，不需要检查有效性
// 但是其中没有任何括号来表示优先级
// 你可以随意添加括号来改变逻辑优先级
// 目的是让表达式能够最终得出result的结果
// 返回最终得出result有多少种不同的逻辑计算顺序
// 测试链接 : https://leetcode.cn/problems/boolean-evaluation-lcci/
class Solution {
 public:
  static int countEval(const string &s, int result) {
    int n = s.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, -1)));
    vector<int> ft = process(s, 0, n - 1, dp);

    return ft[result];
  }

 private:
  // s[l...r]是表达式的一部分，且一定符合范式
  // 0/1  逻  0/1   逻       0/1
  //  l  l+1  l+2  l+3........r
  // s[l...r]  0 : ?
  //           1 : ?
  // ans : int[2] ans[0] = false方法数 ans[1] = true方法数
  static vector<int> process(const string &s, int l, int r, vector<vector<vector<int>>> &dp) {
    if (dp[l][r][0] != -1)
      return dp[l][r];

    int f = 0, t = 0;
    if (l == r) {
      // 只剩一个字符
      f = s[l] == '0';
      t = s[l] == '1';
    } else {
      for (int k = l + 1, a, b, c, d; k < r; k += 2) {
        // l ... r
        // 枚举每一个逻辑符号最后执行 k = l+1 ... r-1  k+=2
        auto tmp = process(s, l, k - 1, dp);
        a = tmp[0];
        b = tmp[1];
        tmp = process(s, k + 1, r, dp);
        c = tmp[0];
        d = tmp[1];

        if (s[k] == '&') {
          t += b * d;
          f += a * c + a * d + b * c;
        } else if (s[k] == '|') {
          t += a * d + b * c + b * d;
          f += a * c;
        } else {
          f += a * c + b * d;
          t += a * d + b * c;
        }
      }
    }

    return dp[l][r] = {f, t};
  }
};
