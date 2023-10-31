#include <iostream>
#include <vector>
#include <cstring>
#include <deque>

using namespace std;

auto __FAST_IO_ = []() noexcept {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  return 0;
}();

// 使网格图至少有一条有效路径的最小代价
// 给你一个 m * n 的网格图 grid 。 grid 中每个格子都有一个数字
// 对应着从该格子出发下一步走的方向。 grid[i][j] 中的数字可能为以下几种情况：
// 1 ，下一步往右走，也就是你会从 grid[i][j] 走到 grid[i][j + 1]
// 2 ，下一步往左走，也就是你会从 grid[i][j] 走到 grid[i][j - 1]
// 3 ，下一步往下走，也就是你会从 grid[i][j] 走到 grid[i + 1][j]
// 4 ，下一步往上走，也就是你会从 grid[i][j] 走到 grid[i - 1][j]
// 注意网格图中可能会有 无效数字 ，因为它们可能指向 grid 以外的区域
// 一开始，你会从最左上角的格子 (0,0) 出发
// 我们定义一条 有效路径 为从格子 (0,0) 出发，每一步都顺着数字对应方向走
// 最终在最右下角的格子 (m - 1, n - 1) 结束的路径
// 有效路径 不需要是最短路径
// 你可以花费1的代价修改一个格子中的数字，但每个格子中的数字 只能修改一次
// 请你返回让网格图至少有一条有效路径的最小代价
// 测试链接 : https://leetcode.cn/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/
class Solution {
 public:
  int minCost(vector<vector<int>> &grid) {
    int move[][2] = {{}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int m = grid.size();
    int n = grid[0].size();

    int dist[m][n];
    memset(dist, 0x3f, sizeof(dist));

    deque<pair<int, int>> q;
    q.emplace_back(0, 0);
    dist[0][0] = 0;

    while (!q.empty()) {
      pair<int, int> e = q.front();
      q.pop_front();

      int x = e.first;
      int y = e.second;
      if (x == m - 1 && y == n - 1) {
        return dist[x][y];
      }

      for (int i = 1; i <= 4; ++i) {
        int nx = x + move[i][0];
        int ny = y + move[i][1];
        int w = grid[x][y] != i;

        if (nx >= 0 && nx < m && ny >= 0 && ny < n
            && dist[x][y] + w < dist[nx][ny]) {
          dist[nx][ny] = w + dist[x][y];

          if (w) {
            q.emplace_back(nx, ny);
          } else {
            q.emplace_front(nx, ny);
          }
        }
      }
    }

    return -1;
  }
};
