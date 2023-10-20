#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 最小体力消耗路径
// 你准备参加一场远足活动。给你一个二维 rows x columns 的地图 heights
// 其中 heights[row][col] 表示格子 (row, col) 的高度
// 一开始你在最左上角的格子 (0, 0) ，且你希望去最右下角的格子 (rows-1, columns-1)
// （注意下标从 0 开始编号）。你每次可以往 上，下，左，右 四个方向之一移动
// 你想要找到耗费 体力 最小的一条路径
// 一条路径耗费的体力值是路径上，相邻格子之间高度差绝对值的最大值
// 请你返回从左上角走到右下角的最小 体力消耗值
// 测试链接 ：https://leetcode.cn/problems/path-with-minimum-effort/
class Solution {
  int move[5] = {-1, 0, 1, 0, -1};

 public:
  int minimumEffortPath(vector<vector<int>> &heights) {
    // (0,0)源点
    // -> (x,y)
    int n = heights.size();
    int m = heights[0].size();
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));

    dist[0][0] = 0;
    vector<vector<bool>> visited(n, vector<bool>(m));
    // 0 : 格子的行
    // 1 : 格子的列
    // 2 : 源点到当前格子的代价
    auto comp = [](auto &v1, auto &v2) noexcept {
      return v1[2] > v2[2];
    };
    priority_queue<vector<int>, vector<vector<int>>, decltype(comp)> heap(comp);
    heap.push({0, 0, 0});

    while (!heap.empty()) {
      vector<int> record = heap.top();
      heap.pop();

      int x = record[0];
      int y = record[1];
      int c = record[2];

      if (visited[x][y]) {
        continue;
      }

      if (x == n - 1 && y == m - 1) {
        // 常见剪枝
        // 发现终点直接返回
        // 不用等都结束
        return c;
      }

      visited[x][y] = true;
      for (int i = 0; i < 4; ++i) {
        int nx = x + move[i];
        int ny = y + move[i + 1];

        if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny]) {
          int nc = max(c, abs(heights[x][y] - heights[nx][ny]));

          if (nc < dist[nx][ny]) {
            dist[nx][ny] = nc;
            heap.push({nx, ny, nc});
          }
        }
      }
    }

    return -1;
  }
};

auto __FAST_IO__ = []() noexcept -> int {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  return 0;
}();
