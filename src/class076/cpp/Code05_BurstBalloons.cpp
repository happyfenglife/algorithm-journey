#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 戳气球
// 有 n 个气球，编号为0到n-1，每个气球上都标有一个数字，这些数字存在数组nums中
// 现在要求你戳破所有的气球。戳破第 i 个气球
// 你可以获得 nums[i - 1] * nums[i] * nums[i + 1] 枚硬币
// 这里的 i - 1 和 i + 1 代表和 i 相邻的两个气球的序号
// 如果 i - 1或 i + 1 超出了数组的边界，那么就当它是一个数字为 1 的气球
// 求所能获得硬币的最大数量
// 测试链接 : https://leetcode.cn/problems/burst-balloons/
class Solution {
 public:
  static int maxCoins(vector<int> &nums) {
    int n = nums.size();
    // a b c d e
    // 1 a b c d e 1
    nums.insert(nums.begin(), 1);
    nums.push_back(1);

    vector<vector<int>> dp(n + 2, vector<int>(n + 2, -1));
    return f(nums, 1, n, dp);
  }

  // 严格位置依赖的动态规划
  static int maxCoins2(vector<int> &nums) {
    int n = nums.size();
    // a b c d e
    // 1 a b c d e 1
    nums.insert(nums.begin(), 1);
    nums.push_back(1);

    vector<vector<int>> dp(n + 2, vector<int>(n + 2, -1));
    for (int i = 1; i <= n; ++i) {
      dp[i][i] = nums[i - 1] * nums[i] * nums[i + 1];
    }

    for (int l = n, ans; l >= 1; --l) {
      for (int r = l + 1; r <= n; ++r) {
        ans = max(
            nums[l - 1] * nums[l] * nums[r + 1] + dp[l + 1][r], // l位置的气球最后打爆
            nums[l - 1] * nums[r] * nums[r + 1] + dp[l][r - 1]// r位置的气球最后打爆
        );

        for (int k = l + 1; k < r; ++k) {
          // k位置的气球最后打爆
          ans = max(ans, nums[l - 1] * nums[k] * nums[r + 1] + dp[l][k - 1] + dp[k + 1][r]);
        }

        dp[l][r] = ans;
      }
    }

    return dp[1][n];
  }

 private:
  // arr[l...r]这些气球决定一个顺序，获得最大得分返回！
  // 一定有 : arr[l-1]一定没爆！
  // 一定有 : arr[r+1]一定没爆！
  // 尝试每个气球最后打爆
  static int f(vector<int> &nums, int l, int r, vector<vector<int>> &dp) {
    if (dp[l][r] != -1) {
      return dp[l][r];
    }

    int ans;

    if (l == r) {
      ans = nums[l - 1] * nums[l] * nums[r + 1];
    } else {
      ans = max(
          nums[l - 1] * nums[l] * nums[r + 1] + f(nums, l + 1, r, dp), // l位置的气球最后打爆
          nums[l - 1] * nums[r] * nums[r + 1] + f(nums, l, r - 1, dp) // r位置的气球最后打爆
      );

      for (int k = l + 1; k < r; ++k) {
        // k位置的气球最后打爆
        ans = max(ans, nums[l - 1] * nums[k] * nums[r + 1] + f(nums, l, k - 1, dp) + f(nums, k + 1, r, dp));
      }
    }

    return dp[l][r] = ans;
  }
};
