#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

auto __FAST_IO__ = []() noexcept {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  return 0;
}();

// Bellman-Ford算法应用（不是模版）
// k站中转内最便宜的航班
// 有 n 个城市通过一些航班连接。给你一个数组 flights
// 其中 flights[i] = [fromi, toi, pricei]
// 表示该航班都从城市 fromi 开始，以价格 pricei 抵达 toi。
// 现在给定所有的城市和航班，以及出发城市 src 和目的地 dst，你的任务是找到出一条最多经过 k 站中转的路线
// 使得从 src 到 dst 的 价格最便宜 ，并返回该价格。 如果不存在这样的路线，则输出 -1。
// 测试链接 : https://leetcode.cn/problems/cheapest-flights-within-k-stops/
class Solution {
 public:
  int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k) {
    int dist[n];
    memset(dist, 0x3f, sizeof(dist));
    dist[src] = 0;

    for (int i = 0; i <= k; ++i) {
      int newDist[n];
      copy(dist, dist + n, newDist);

      for (auto &e : flights) {
        if (dist[e[0]] != 0x3f3f3f3f) {
          newDist[e[1]] = min(newDist[e[1]], dist[e[0]] + e[2]);
        }
      }

      copy(newDist, newDist + n, dist);
    }

    return dist[dst] == 0x3f3f3f3f ? -1 : dist[dst];
  }
};
