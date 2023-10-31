#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

auto __FAST_IO_ = []() noexcept {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  return 0;
}();

// 二维接雨水
// 给你一个 m * n 的矩阵，其中的值均为非负整数，代表二维高度图每个单元的高度
// 请计算图中形状最多能接多少体积的雨水。
// 测试链接 : https://leetcode.cn/problems/trapping-rain-water-ii/
class Solution {
 public:
  int trapRainWater(vector<vector<int>> &heightMap) {
    int move[] = {-1, 0, 1, 0, -1};
    int n = heightMap.size();
    int m = heightMap[0].size();

    // 0 : 行
    // 1 : 列
    // 2 : 水线
    auto comp = [&](vector<int> &v1, vector<int> &v2) noexcept {
      return v1[2] > v2[2];
    };
    priority_queue<vector<int>, vector<vector<int>>, decltype(comp)> heap(comp);
    bool visited[n][m];
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
          heap.push({i, j, heightMap[i][j]});
          visited[i][j] = true;
        }
      }
    }

    int ans = 0;
    while (!heap.empty()) {
      vector<int> record = heap.top();
      heap.pop();

      int r = record[0];
      int c = record[1];
      int w = record[2];
      ans += w - heightMap[r][c];

      for (int i = 0, nr, nc; i < 4; ++i) {
        nr = r + move[i];
        nc = c + move[i + 1];

        if (nr >= 0 && nr < n && nc >= 0 && nc < m
            && !visited[nr][nc]) {
          heap.push({nr, nc, max(heightMap[nr][nc], w)});
          visited[nr][nc] = true;
        }
      }
    }

    return ans;
  }
};
