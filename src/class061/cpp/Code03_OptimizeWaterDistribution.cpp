#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>

using namespace std;

// 水资源分配优化
// 村里面一共有 n 栋房子。我们希望通过建造水井和铺设管道来为所有房子供水。
// 对于每个房子 i，我们有两种可选的供水方案：一种是直接在房子内建造水井
// 成本为 wells[i - 1] （注意 -1 ，因为 索引从0开始 ）
// 另一种是从另一口井铺设管道引水，数组 pipes 给出了在房子间铺设管道的成本，
// 其中每个 pipes[j] = [house1j, house2j, costj] 
// 代表用管道将 house1j 和 house2j连接在一起的成本。连接是双向的。
// 请返回 为所有房子都供水的最低总成本
// 测试链接 : https://leetcode.cn/problems/optimize-water-distribution-in-a-village/
class Solution {
 public:
  int minCostToSupplyWater(int n, vector<int> &wells, vector<vector<int>> &pipes) {
    vector<vector<int>> edges(n + pipes.size(), vector<int>(3));
    for (int i = 0; i < n; ++i) {
      edges[i] = {0, i + 1, wells[i]};
    }

    for (int i = 0; i < pipes.size(); ++i) {
      edges[i + n][0] = pipes[i][0];
      edges[i + n][1] = pipes[i][1];
      edges[i + n][2] = pipes[i][2];
    }

    sort(edges.begin(), edges.end(), [&](auto &e1, auto &e2) noexcept {
      return e1[2] < e2[2];
    });

    vector<int> father(n);
    iota(father.begin(), father.end(), 0);

    function<int(int)> find = [&](int i) noexcept -> int {
      if (i != father[i]) {
        father[i] = find(father[i]);
      }

      return father[i];
    };

    auto conn = [&](auto &e1, auto &e2) noexcept -> bool {
      int f1 = find(e1);
      int f2 = find(e2);

      if (f1 != f2) {
        father[f1] = f2;
        return true;
      } else {
        return false;
      }
    };

    int ans = 0;
    for (int i = 0; i < n + pipes.size(); ++i) {
      if (conn(edges[i][0], edges[i][1])) {
        ans += edges[i][2];
      }
    }

    return ans;
  }
};

auto __FAST_IO__ = []()noexcept -> int {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  return 0;
};
