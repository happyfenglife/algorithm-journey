#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Dijkstra算法模版（Leetcode）
// 网络延迟时间
// 有 n 个网络节点，标记为 1 到 n
// 给你一个列表 times，表示信号经过 有向 边的传递时间
// times[i] = (ui, vi, wi)，表示从ui到vi传递信号的时间是wi
// 现在，从某个节点 s 发出一个信号
// 需要多久才能使所有节点都收到信号
// 如果不能使所有节点收到信号，返回 -1
// 测试链接 : https://leetcode.cn/problems/network-delay-time
class Solution {
 public:
  int networkDelayTime(vector<vector<int>> &times, int n, int k) {
    // 动态建图+普通堆的实现
    vector<vector<pair<int, int>>> graph(n + 1);

    for (auto &edge : times) {
      graph[edge[0]].emplace_back(edge[1], edge[2]);
    }

    vector<int> dist(n + 1, INT_MAX);
    dist[k] = 0;
    vector<bool> visited(n + 1);

    //
    auto comp = [&](auto &o1, auto &o2) noexcept {
      return o1.second > o2.second;
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> heap(comp);
    heap.emplace(k, 0);

    while (!heap.empty()) {
      int u = heap.top().first;
      heap.pop();

      if (visited[u]) {
        continue;
      }

      visited[u] = true;
      for (auto &edge : graph[u]) {
        int v = edge.first;
        int w = edge.second;

        if (!visited[v] && dist[u] + w < dist[v]) {
          dist[v] = dist[u] + w;
          heap.emplace(v, dist[v]);
        }
      }
    }

    int ans = INT_MIN;
    for (int i = 1; i <= n; ++i) {
      if (dist[i] == INT_MAX) {
        return -1;
      }

      ans = max(ans, dist[i]);
    }

    return ans;
  }
};

auto __FAST_IO__ = []() noexcept -> int {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  return 0;
}();
