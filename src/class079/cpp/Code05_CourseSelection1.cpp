#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 选课
// 在大学里每个学生，为了达到一定的学分，必须从很多课程里选择一些课程来学习
// 在课程里有些课程必须在某些课程之前学习，如高等数学总是在其它课程之前学习
// 现在有 N 门功课，每门课有个学分，每门课有一门或没有直接先修课
// 若课程 a 是课程 b 的先修课即只有学完了课程 a，才能学习课程 b
// 一个学生要从这些课程里选择 M 门课程学习
// 问他能获得的最大学分是多少
// 测试链接 : https://www.luogu.com.cn/problem/P2014

const int MAXN = 301;
int nums[MAXN];
vector<vector<int> > graph(MAXN);
vector<vector<vector<int> > > dp(MAXN);
int n, m;

// 普通解法，邻接表建图 + 相对好懂的动态规划
// 几乎所有题解都是普通解法的思路，只不过优化了常数时间、做了空间压缩
// 但时间复杂度依然是O(n * 每个节点的孩子平均数量 * m的平方)
void build(int n)
{
  for (int i = 0; i <= n; ++i)
  {
    graph[i].clear();
  }
}

// 当前来到i号节点为头的子树
// 只在i号节点、及其i号节点下方的前j棵子树上挑选节点
// 一共挑选k个节点，并且保证挑选的节点连成一片
// 返回最大的累加和
int dfs(int i, int j, int k)
{
  if (!k)
  {
    return 0;
  }

  if (!j || k == 1)
  {
    return nums[i];
  }

  if (dp[i][j][k] != -1)
  {
    return dp[i][j][k];
  }

  int ans = dfs(i, j - 1, k);
  int v = graph[i][j - 1];
  for (int s = 1; s < k; ++s)
  {
    ans = max(ans, dfs(i, j - 1, k - s) + dfs(v, graph[v].size(), s));
  }

  return dp[i][j][k] = ans;
}

int compute()
{
  for (int i = 0; i <= n; ++i)
  {
    dp[i] = vector<vector<int> >(graph[i].size() + 1, vector<int>(m + 1));
  }

  for (int i = 0; i <= n; i++)
  {
    for (auto &j : dp[i])
    {
      for (int k = 0; k <= m; k++)
      {
        j[k] = -1;
      }
    }
  }

  return dfs(0, graph[0].size(), m);
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  m += 1;
  build(n);
  for (int i = 1, pre; i <= n; ++i)
  {
    cin >> pre >> nums[i];
    graph[pre].push_back(i);
  }

  cout << compute() << endl;

  return 0;
}
