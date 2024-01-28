#include <bits/stdc++.h>

using namespace std;

// 最大数
// 给定一组非负整数nums
// 重新排列每个数的顺序（每个数不可拆分）使之组成一个最大的整数
// 测试链接 : https://leetcode.cn/problems/largest-number/
class Solution
{
  public:
    string largestNumber(vector<int> &nums)
    {
      vector<string> strs;
      for (int num : nums)
      {
        strs.push_back(to_string(num));
      }

      sort(strs.begin(),
           strs.end(),
           [](const auto &a, const auto &b) {
             return a + b > b + a;
           });

      if (strs[0] == "0")
      {
        return "0";
      }

      string init;
      for (const auto &str : strs)
      {
        init += str;
      }

      return init;
    }
};
