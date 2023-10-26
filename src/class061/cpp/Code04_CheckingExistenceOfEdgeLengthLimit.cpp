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
  vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>> &edgeList, vector<vector<int>> &queries) {
    sort(edgeList.begin(), edgeList.end(), [&](auto &e1, auto &e2) {
      return e1[2] < e2[2];
    });

    int m = edgeList.size();
    int k = queries.size();

    vector<vector<int>> questions(k, vector<int>(4));
    for (int i = 0; i < k; ++i) {
      questions[i][0] = queries[i][0];
      questions[i][1] = queries[i][1];
      questions[i][2] = queries[i][2];
      questions[i][3] = i;
    }

    sort(questions.begin(), questions.end(), [&](auto &x, auto &y) {
      return x[2] < y[2];
    });

    vector<int> father(n);
    iota(father.begin(), father.end(), 0);

    function<int(int)> find = [&](int i) noexcept -> int {
      if (i != father[i]) {
        father[i] = find(father[i]);
      }

      return father[i];
    };

    auto conn = [&](int i, int j) noexcept {
      father[find(i)] = find(j);
    };

    auto isSameSet = [&](int i, int j) noexcept {
      return find(i) == find(j);
    };

    vector<bool> ans(k);
    for (int i = 0, j = 0; i < k; ++i) {
      for (; j < m && edgeList[j][2] < questions[i][2]; ++j) {
        conn(edgeList[j][0], edgeList[j][1]);
      }

      ans[questions[i][3]] = isSameSet(questions[i][0], questions[i][1]);
    }

    return ans;
  }
};

auto __FAST_IO__ = []() noexcept -> int {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  return 0;
};
