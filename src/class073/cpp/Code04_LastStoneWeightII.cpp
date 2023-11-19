#include <iostream>
#include <vector>
#include <numeric>

using namespace std;
// 最后一块石头的重量 II
// 有一堆石头，用整数数组 stones 表示
// 其中 stones[i] 表示第 i 块石头的重量。
// 每一回合，从中选出任意两块石头，然后将它们一起粉碎
// 假设石头的重量分别为 x 和 y，且 x <= y
// 那么粉碎的可能结果如下：
// 如果 x == y，那么两块石头都会被完全粉碎；
// 如果 x != y，那么重量为 x 的石头将会完全粉碎，而重量为 y 的石头新重量为 y-x
// 最后，最多只会剩下一块 石头，返回此石头 最小的可能重量
// 如果没有石头剩下，就返回 0
// 测试链接 : https://leetcode.cn/problems/last-stone-weight-ii/
class Solution {
 public:
  int lastStoneWeightII(vector<int> &stones) {
    int sum = accumulate(stones.begin(), stones.end(), 0);

    // nums中随意选择数字
    // 累加和一定要 <= sum / 2
    // 又尽量接近
    int closest = near(stones, sum / 2);
    return sum - closest - closest;
  }

 private:
  // 非负数组nums中，子序列累加和不超过t，但是最接近t的累加和是多少
  // 01背包问题(子集累加和尽量接近t) + 空间压缩
  int near(vector<int> &stones, int limit) {
    vector<int> dp(limit + 1);

    for (int stone : stones) {
      for (int j = limit; j >= stone; --j) {
        dp[j] = max(dp[j], dp[j - stone] + stone);
      }
    }

    return dp[limit];
  }
};

auto __FAST_IO__ = []() noexcept {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  return 0;
}();
