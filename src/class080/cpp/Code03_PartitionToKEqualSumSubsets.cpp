#include <bits/stdc++.h>

using namespace std;

// 划分为k个相等的子集
// 给定一个整数数组  nums 和一个正整数 k，
// 找出是否有可能把这个数组分成 k 个非空子集，其总和都相等。
// 测试链接 : https://leetcode.cn/problems/partition-to-k-equal-sum-subsets/
class Solution
{
  public:
    // 状压DP解法同火柴拼正方形
    // ...
    // 纯暴力的递归（不做任何动态规划），利用良好的剪枝策略，可以做到非常好的效率
    // 但这并不是正式的解，如果数据设计的很苛刻，是通过不了的
    bool canPartitionKSubsets(vector<int> &nums, int k)
    {
      int sum = accumulate(nums.begin(), nums.end(), 0);

      if (sum % k)
      {
        return false;
      }

      int n = nums.size();
      sort(nums.begin(), nums.end());
      vector<int> group(k);

      return dfs(group, sum / k, nums, n - 1);
    }

  private:
    // group里面是各个集合已经有的累加和
    // 随着递归的展开，group里的累加和会变化
    // 所以这是一个带路径的递归，而且路径信息比较复杂(group数组)
    // 无法改成动态规划，但是利用剪枝策略可以通过
    // group[0....index]这些数字，填入每个集合，一定要都使用
    // 每个集合的累加和一定都要是target，返回能不能做到
    bool dfs(vector<int> &group, int target, vector<int> &nums, int index)
    {
      if (index < 0)
      {
        return true;
      }

      int num = nums[index];
      int len = group.size();
      for (int i = 0; i < len; ++i)
      {
        if (group[i] + num <= target)
        {
          // 当前数字num放进i号集合
          group[i] += num;

          if (dfs(group, target, nums, index - 1))
          {
            return true;
          }

          // 递归完成后将路径还原
          group[i] -= num;
          while (i + 1 < group.size() && group[i + 1] == group[i])
          {
            ++i;
          }
        }
      }

      return false;
    }
};
