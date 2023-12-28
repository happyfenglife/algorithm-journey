#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;

  TreeNode(int v)
    : val(v), left(nullptr), right(nullptr)
  {
  }
};

// 从树中删除边的最小分数
// 存在一棵无向连通树，树中有编号从0到n-1的n个节点，以及n-1条边
// 给你一个下标从0开始的整数数组nums长度为n，其中nums[i]表示第i个节点的值
// 另给你一个二维整数数组edges长度为n-1
// 其中 edges[i] = [ai, bi] 表示树中存在一条位于节点 ai 和 bi 之间的边
// 删除树中两条不同的边以形成三个连通组件，对于一种删除边方案，定义如下步骤以计算其分数：
// 分别获取三个组件每个组件中所有节点值的异或值
// 最大 异或值和 最小 异或值的 差值 就是这种删除边方案的分数
// 返回可能的最小分数
// 测试链接 : https://leetcode.cn/problems/minimum-score-after-removals-on-a-tree/
class Solution
{
  static constexpr int MAXN = 1001;
  int dfn[MAXN]; // 下标为原始节点编号
  int XOR[MAXN]; // 下标为dfn序号
  int size[MAXN]; // 下标为dfn序号
  int dfnCnt;

  public:
    int minimumScore(vector<int> &nums, vector<vector<int> > &edges)
    {
      int n = nums.size(), m = edges.size();
      vector<vector<int> > graph(n);
      for (auto &edge : edges)
      {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
      }
      dfnCnt = 0;

      dfs(nums, graph, 0, -1);
      int ans = INT_MAX;

      for (int i = 0, a, b, pre, pos, sum1, sum2, sum3; i < m; ++i)
      {
        a = max(dfn[edges[i][0]], dfn[edges[i][1]]);

        for (int j = i + 1; j < m; ++j)
        {
          b = max(dfn[edges[j][0]], dfn[edges[j][1]]);
          pre = min(a, b);
          pos = max(a, b);

          sum1 = XOR[pos];
          // xor[1] : 整棵树的异或和
          // 因为头节点是0，一定拥有最小的dfn序号1
          // f函数调用的时候，也是从0节点开始的
          if (pos < pre + size[pre])
          {
            sum2 = XOR[pre] ^ XOR[pos];
            sum3 = XOR[1] ^ XOR[pre];
          } else
          {
            sum2 = XOR[pre];
            sum3 = XOR[1] ^ sum1 ^ sum2;
          }

          ans = min(ans, max({sum1, sum2, sum3}) - min({sum1, sum2, sum3}));
        }
      }
      return ans;
    }

  private:
    void dfs(vector<int> &nums, vector<vector<int> > &graph, int u, int f)
    {
      int i = ++dfnCnt;
      dfn[u] = i;
      XOR[i] = nums[u];
      size[i] = 1;

      for (auto v : graph[u])
      {
        if (v != f)
        {
          dfs(nums, graph, v, u);
          XOR[i] ^= XOR[dfn[v]];
          size[i] += size[dfn[v]];
        }
      }
    }
};
