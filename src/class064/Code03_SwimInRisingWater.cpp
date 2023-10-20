#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 水位上升的泳池中游泳
// 在一个 n x n 的整数矩阵 grid 中
// 每一个方格的值 grid[i][j] 表示位置 (i, j) 的平台高度
// 当开始下雨时，在时间为 t 时，水池中的水位为 t
// 你可以从一个平台游向四周相邻的任意一个平台，但是前提是此时水位必须同时淹没这两个平台
// 假定你可以瞬间移动无限距离，也就是默认在方格内部游动是不耗时的
// 当然，在你游泳的时候你必须待在坐标方格里面。
// 你从坐标方格的左上平台 (0，0) 出发
// 返回 你到达坐标方格的右下平台 (n-1, n-1) 所需的最少时间
// 测试链接 : https://leetcode.cn/problems/swim-in-rising-water/
class Solution {
  int move[5] = {-1, 0, 1, 0, -1};

 public:
  int swimInWater(vector<vector<int>> &grid) {
    int n = grid.size();

    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    dist[0][0] = grid[0][0];
    vector<vector<bool>> visited(n, vector<bool>(n));

    auto comp = [&](auto &v1, auto &v2) noexcept {
      return v1[2] > v2[2];
    };
    priority_queue<vector<int>, vector<vector<int>>, decltype(comp)> heap(comp);

    heap.push({0, 0, grid[0][0]});
    while (!heap.empty()) {
      int x = heap.top()[0];
      int y = heap.top()[1];
      int c = heap.top()[2];
      heap.pop();

      if (visited[x][y]) {
        continue;
      }

      visited[x][y] = true;
      if (x == n - 1 && y == n - 1) {
        // 常见剪枝
        // 发现终点直接返回
        // 不用等都结束
        return c;
      }

      for (int i = 0, nx, ny, nc; i < 4; ++i) {
        nx = x + move[i];
        ny = y + move[i + 1];

        if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[nx][ny]) {
          nc = max(c, grid[nx][ny]);

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
