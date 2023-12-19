#include <iostream>
#include <climits>
#include <vector>

using namespace std;

// 涂色 & 奇怪打印机
// 假设你有一条长度为5的木板，初始时没有涂过任何颜色
// 你希望把它的5个单位长度分别涂上红、绿、蓝、绿、红
// 用一个长度为5的字符串表示这个目标：RGBGR
// 每次你可以把一段连续的木板涂成一个给定的颜色，后涂的颜色覆盖先涂的颜色
// 例如第一次把木板涂成RRRRR
// 第二次涂成RGGGR
// 第三次涂成RGBGR，达到目标
// 返回尽量少的涂色次数
// 测试链接 : https://www.luogu.com.cn/problem/P4170
// 测试链接 : https://leetcode.cn/problems/strange-printer/
class Solution {
 public:
  static int strangePrinter(const string &s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n));

    for (int i = 0; i < n - 1; ++i) {
      dp[i][i] = 1;
      dp[i][i + 1] = (s[i] == s[i + 1]) ? 1 : 2;
    }
    dp[n - 1][n - 1] = 1;

    for (int l = n - 3, ans; l >= 0; --l) {
      for (int r = l + 2; r < n; ++r) {
        if (s[l] == s[r]) {
          dp[l][r] = dp[l][r - 1];
        } else {
          ans = INT_MAX;

          for (int m = l; m < r; ++m) {
            ans = min(ans, dp[l][m] + dp[m + 1][r]);
          }
          dp[l][r] = ans;
        }
      }
    }

    return dp[0][n - 1];
  }
};
