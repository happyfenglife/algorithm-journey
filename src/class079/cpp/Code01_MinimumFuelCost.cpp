#include <iostream>
#include <vector>

using namespace std;

// 到达首都的最少油耗
// 给你一棵 n 个节点的树（一个无向、连通、无环图）
// 每个节点表示一个城市，编号从 0 到 n - 1 ，且恰好有 n - 1 条路
// 0 是首都。给你一个二维整数数组 roads
// 其中 roads[i] = [ai, bi] ，表示城市 ai 和 bi 之间有一条 双向路
// 每个城市里有一个代表，他们都要去首都参加一个会议
// 每座城市里有一辆车。给你一个整数 seats 表示每辆车里面座位的数目
// 城市里的代表可以选择乘坐所在城市的车，或者乘坐其他城市的车
// 相邻城市之间一辆车的油耗是一升汽油
// 请你返回到达首都最少需要多少升汽油
// 测试链接 : https://leetcode.cn/problems/minimum-fuel-cost-to-report-to-the-capital/
class Solution {
  public:
    long long minimumFuelCost(vector<vector<int> > &roads, int seats) {
      int n = roads.size() + 1;
      vector<vector<int> > graph(n);

      for (auto &road : roads) {
        graph[road[0]].push_back(road[1]);
        graph[road[1]].push_back(road[0]);
      }

      vector<int> cnt(n);
      vector<long long> cost(n);
      dfs(graph, seats, 0, -1, cnt, cost);

      return cost[0];
    }

  private:
    // 根据图，当前来到u，u的父节点是p
    // 遍历完成后，请填好size[u]、cost[u]
    void dfs(vector<vector<int> > &graph, int seats, int u, int p, vector<int> &cnt, vector<long long> &cost) {
      cnt[u] = 1;
      for (auto v : graph[u]) {
        if (v == p) {
          continue;
        }

        dfs(graph, seats, v, u, cnt, cost);

        cnt[u] += cnt[v];
        cost[u] += cost[v];
        // a/b向上取整，可以写成(a+b-1)/b
        // (size[v]+seats-1) / seats = size[v] / seats 向上取整
        cost[u] += (cnt[v] + seats - 1) / seats;
      }
    }
};
