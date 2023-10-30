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

// 到达角落需要移除障碍物的最小数目
// 给你一个下标从 0 开始的二维整数数组 grid ，数组大小为 m x n
// 每个单元格都是两个值之一：
// 0 表示一个 空 单元格，
// 1 表示一个可以移除的 障碍物
// 你可以向上、下、左、右移动，从一个空单元格移动到另一个空单元格。
// 现在你需要从左上角 (0, 0) 移动到右下角 (m - 1, n - 1)
// 返回需要移除的障碍物的最小数目
// 测试链接 : https://leetcode.cn/problems/minimum-obstacle-removal-to-reach-corner/
class Solution {
 public:
  int minimumObstacles(vector<vector<int>> &grid) {
    int move[] = {-1, 0, 1, 0, -1};
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

      for (int i = 0; i < 4; ++i) {
        int nx = x + move[i];
        int ny = y + move[i + 1];

        if (nx >= 0 && nx < m && ny >= 0 && ny < n
            && dist[x][y] + grid[nx][ny] < dist[nx][ny]) {
          dist[nx][ny] = dist[x][y] + grid[nx][ny];

          if (grid[nx][ny] == 0) {
            q.emplace_front(nx, ny);
          } else {
            q.emplace_back(nx, ny);
          }
        }
      }
    }

    return -1;
  }
};
