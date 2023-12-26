#include <iostream>
#include <vector>

using namespace std;

struct Info {
  int maxPathFromHead; // 一定要从头节点出发的情况下，相邻字符不等的最长路径长度
  int maxPath; // 整棵树上，相邻字符不等的最长路径长度
};

// 相邻字符不同的最长路径
// 给你一棵 树（即一个连通、无向、无环图），根节点是节点 0
// 这棵树由编号从 0 到 n - 1 的 n 个节点组成
// 用下标从 0 开始、长度为 n 的数组 parent 来表示这棵树
// 其中 parent[i] 是节点 i 的父节点
// 由于节点 0 是根节点，所以 parent[0] == -1
// 另给你一个字符串 s ，长度也是 n ，其中 s[i] 表示分配给节点 i 的字符
// 请你找出路径上任意一对相邻节点都没有分配到相同字符的 最长路径
// 并返回该路径的长度
// 测试链接 : https://leetcode.cn/problems/longest-path-with-different-adjacent-characters/
class Solution {
  public:
    int longestPath(vector<int> &parent, const string &s) {
      int n = parent.size();
      vector<vector<int> > graph(n);
      for (int i = 1; i < n; ++i) {
        graph[parent[i]].push_back(i);
      }

      return dfs(s, graph, 0).maxPath;
    }

  private:
    Info dfs(const string &s, vector<vector<int> > &graph, int u) {
      if (graph[u].empty()) {
        return {1, 1};
      }

      int max1 = 0, max2 = 0; // 下方最长链与次长链
      int maxPath = 1;
      for (auto v : graph[u]) {
        Info nextInfo = dfs(s, graph, v);
        maxPath = max(maxPath, nextInfo.maxPath);

        if (s[u] != s[v]) {
          if (nextInfo.maxPathFromHead > max1) {
            max2 = max1;
            max1 = nextInfo.maxPathFromHead;
          } else if (nextInfo.maxPathFromHead > max2) {
            max2 = nextInfo.maxPathFromHead;
          }
        }
      }

      maxPath = max(maxPath, max1 + max2 + 1);
      return {max1 + 1, maxPath};
    }
};
