#include <bits/stdc++.h>

using namespace std;

// 最优解，链式前向星建图 + dfn序的利用 + 巧妙定义下的尝试
// 时间复杂度O(n * m)
const int MAXN = 301;
int nums[MAXN];

// 链式前向星建图
int edgeCnt;
int head[MAXN];
int next_[MAXN];
int to[MAXN];

// dfn计数
int dfnCnt;
// 下标为dfn序号
int val[MAXN + 1];
// 下标为dfn序号
int size_[MAXN + 1];
// 动态规划表
int dp[MAXN + 2][MAXN];

int n, m;

void build(int n)
{
  edgeCnt = 1;
  dfnCnt = 0;
  memset(head, 0, sizeof(head));
  memset(dp[n + 2], 0, sizeof(dp[n + 2]));
}

void addEdge(int u, int v)
{
  next_[edgeCnt] = head[u];
  to[edgeCnt] = v;
  head[u] = edgeCnt++;
}

// u这棵子树的节点数返回
int f(int u)
{
  int i = ++dfnCnt;
  val[i] = nums[u];
  size_[i] = 1;

  for (int ei = head[u], v; ei != 0; ei = next_[ei])
  {
    v = to[ei];
    size_[i] += f(v);
  }

  return size_[i];
}

int compute()
{
  f(0);

  // 节点编号0 ~ n，dfn序号范围1 ~ n+1
  // 接下来的逻辑其实就是01背包！不过经历了很多转化
  // 整体的顺序是根据dfn序来进行的，从大的dfn序，遍历到小的dfn序
  // dp[i][j] : i ~ n+1 范围的节点，选择j个节点一定要形成有效结构的情况下，最大的累加和
  // 怎么定义有效结构？重点！重点！重点！
  // 假设i ~ n+1范围上，目前所有头节点的上方，有一个总的头节点
  // i ~ n+1范围所有节点，选出来j个节点的结构，
  // 挂在这个假想的总头节点之下，是一个连续的结构，没有断开的情况
  // 那么就说，i ~ n+1范围所有节点，选出来j个节点的结构是一个有效结构
  for (int i = n + 1; i >= 2; i--)
  {
    for (int j = 1; j <= m; j++)
    {
      dp[i][j] = max(dp[i + size_[i]][j], val[i] + dp[i + 1][j - 1]);
    }
  }

  return nums[0] + dp[2][m];
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> n >> m;
  build(n);

  for (int i = 1, u, v; i <= n; ++i)
  {
    cin >> u >> v;
    addEdge(u, i);
    nums[i] = v;
  }

  cout << compute() << endl;

  return 0;
}
