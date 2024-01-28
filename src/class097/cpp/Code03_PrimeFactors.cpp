#include <bits/stdc++.h>

using namespace std;

class UnionFind
{
  public:
    UnionFind(int n)
    {
      parent = vector<int>(n);
      rank = vector<int>(n, 1);
      for (int i = 0; i < n; i++)
      {
        parent[i] = i;
      }
    }

    void uni(int x, int y)
    {
      int fx = find(x);
      int fy = find(y);

      if (fx != fy)
      {
        parent[fx] = fy;
        rank[fy] += rank[fx];
      }
    }

    int find(int x)
    {
      if (parent[x] != x)
      {
        parent[x] = find(parent[x]);
      }

      return parent[x];
    }

    int maxSize()
    {
      return *max_element(rank.begin(), rank.end());
    }

  private:
    vector<int> parent;
    vector<int> rank;
};

// 按公因数计算最大组件大小
// 给定一个由不同正整数的组成的非空数组 nums
// 如果 nums[i] 和 nums[j] 有一个大于1的公因子，那么这两个数之间有一条无向边
// 返回 nums中最大连通组件的大小。
// 测试链接 : https://leetcode.cn/problems/largest-component-size-by-common-factor/
class Solution
{
  public:
    int largestComponentSize(vector<int> &nums)
    {
      int n = nums.size();
      int m = *max_element(nums.begin(), nums.end());
      vector<int> factors(m + 1, -1);

      UnionFind uf(n);
      for (int i = 0, x; i < n; ++i)
      {
        x = nums[i];

        for (int j = 2; j * j <= x; ++j)
        {
          if (x % j)
          {
            continue;
          }

          if (factors[j] == -1)
          {
            factors[j] = i;
          } else
          {
            uf.uni(factors[j], i);
          }

          while (!(x % j))
          {
            x /= j;
          }
        }

        if (x > 1)
        {
          if (factors[x] == -1)
          {
            factors[x] = i;
          } else
          {
            uf.uni(factors[x], i);
          }
        }
      }

      return uf.maxSize();
    }
};
