#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

auto __FAST_IO__ = []() noexcept {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  return 0;
}();

class Solution {
  static const int MAXN = 1 << 20;
  int lsum[MAXN];
  int rsum[MAXN];
  int fill;

 public:
  int minAbsDifference(vector<int> &nums, int goal) {
    long long upper = 0;
    long long lower = 0;
    int n = nums.size();

    for (int num : nums) {
      upper += max(num, 0);
      lower += min(num, 0);
    }

    if (upper < goal) {
      return abs(goal - upper);
    }

    if (lower > goal) {
      return abs(goal - lower);
    }

    // 原始数组排序，为了后面递归的时候，还能剪枝
    // 常数优化
    sort(nums.begin(), nums.end());
    fill = 0;
    dfs(nums, 0, n >> 1, 0, lsum);
    int lsize = fill;
    fill = 0;
    dfs(nums, n >> 1, n, 0, rsum);
    int rsize = fill;

    sort(lsum, lsum + lsize);
    sort(rsum, rsum + rsize);
    int ans = abs(goal);

    for (int i = 0, j = rsize - 1; i < lsize; ++i) {
      while (j > 0 && abs(goal - lsum[i] - rsum[j - 1]) <= abs(goal - lsum[i] - rsum[j])) {
        --j;
      }

      ans = min(ans, abs(goal - lsum[i] - rsum[j]));
    }

    return ans;
  }

 private:
  void dfs(vector<int> &nums, int i, int e, int s, int sum[]) {
    if (i == e) {
      sum[fill++] = s;
    } else {
      // nums[i.....]这一组，相同的数字有几个
      int j = i + 1;
      while (j < e && nums[j] == nums[i]) {
        ++j;
      }

      // nums[ 1 1 1 1 1 2....
      //       i         j
      for (int k = 0; k <= j - i; ++k) {
        // k = 0个
        // k = 1个
        // k = 2个
        dfs(nums, j, e, s + k * nums[i], sum);
      }
    }
  }
};
