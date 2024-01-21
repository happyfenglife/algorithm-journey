#include <bits/stdc++.h>

using namespace std;

// 火柴拼正方形
// 你将得到一个整数数组 matchsticks
// 其中 matchsticks[i] 是第 i个火柴棒的长度
// 你要用 所有的火柴棍拼成一个正方形
// 你 不能折断 任何一根火柴棒，但你可以把它们连在一起，而且每根火柴棒必须 使用一次
// 如果你能拼出正方形，则返回 true ，否则返回 false
// 测试链接 : https://leetcode.cn/problems/matchsticks-to-square/
class Solution
{
  public:
    bool makesquare(vector<int> &matchsticks)
    {
      int sum = accumulate(matchsticks.begin(), matchsticks.end(), 0);
      if (sum % 4)
      {
        return false;
      }

      int n = matchsticks.size();
      vector<int> dp(1 << n);

      return dfs(matchsticks, sum / 4, (1 << n) - 1, 0, 4, dp);
    }

  private:
    // limit : 每条边规定的长度
    // status : 表示哪些数字还可以选
    // cur : 当前要解决的这条边已经形成的长度
    // rest : 一共还有几条边没有解决
    // 返回 : 能否用光所有火柴去解决剩下的所有边
    // 因为调用子过程之前，一定保证每条边累加起来都不超过limit
    // 所以status是决定cur和rest的，关键可变参数只有status
    bool dfs(vector<int> &matchsticks, int limit, int status, int cur, int rest, vector<int> &dp)
    {
      if (!rest)
      {
        return !status;
      }

      if (dp[status])
      {
        return dp[status] == 1;
      }

      bool ans{};
      for (int i = 0; i < matchsticks.size(); ++i)
      {
        // 考察每一根火柴，只能使用状态为1的火柴
        if ((status & (1 << i)) && cur + matchsticks[i] <= limit)
        {
          if (cur + matchsticks[i] == limit)
          {
            ans = dfs(matchsticks, limit, status ^ (1 << i), 0, rest - 1, dp);
          } else
          {
            ans = dfs(matchsticks, limit, status ^ (1 << i), cur + matchsticks[i], rest, dp);
          }

          if (ans)
          {
            break;
          }
        }
      }

      dp[status] = ans ? 1 : -1;
      return ans;
    }
};
