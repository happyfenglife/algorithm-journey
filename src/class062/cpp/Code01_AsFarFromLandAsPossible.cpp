#include <iostream>
#include <vector>

using namespace std;

auto __FAST_IO__ = []() noexcept {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  return 0;
}();

// 地图分析
// 你现在手里有一份大小为 n x n 的 网格 grid
// 上面的每个 单元格 都用 0 和 1 标记好了其中 0 代表海洋，1 代表陆地。
// 请你找出一个海洋单元格，这个海洋单元格到离它最近的陆地单元格的距离是最大的
// 并返回该距离。如果网格上只有陆地或者海洋，请返回 -1。
// 我们这里说的距离是「曼哈顿距离」（ Manhattan Distance）：
// (x0, y0) 和 (x1, y1) 这两个单元格之间的距离是 |x0 - x1| + |y0 - y1| 。
// 测试链接 : https://leetcode.cn/problems/as-far-from-land-as-possible/
class Solution {
 public:
  int maxDistance(vector<vector<int>> &grid) {
    int l, r;
    l = r = 0;

    int n = grid.size();
    int seas = 0;
    vector<vector<bool>> visited(n, vector<bool>(n));
    vector<int> move{-1, 0, 1, 0, -1};
    vector<vector<int>> queue;

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 1) {
          visited[i][j] = true;
          queue.push_back({i, j});
          ++r;
        } else {
          seas++;
        }
      }
    }

    if (seas == 0 || seas == n * n) {
      return -1;
    }

    int level = 0;
    while (l < r) {
      level++;
      int size = r - l;

      for (int k = 0, x, y, nx, ny; k < size; ++k) {
        x = queue[l][0];
        y = queue[l++][1];

        for (int i = 0; i < 4; ++i) {
          nx = x + move[i];
          ny = y + move[i + 1];

          if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[nx][ny]) {
            visited[nx][ny] = true;
            queue.push_back({nx, ny});
            ++r;
          }
        }
      }
    }

    return level - 1;
  }
};
