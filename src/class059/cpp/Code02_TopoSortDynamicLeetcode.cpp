#include <iostream>
#include <vector>

using namespace std;

// 拓扑排序模版（Leetcode）
// 邻接表建图（动态方式）
// 课程表II
// 现在你总共有 numCourses 门课需要选，记为 0 到 numCourses - 1
// 给你一个数组 prerequisites ，其中 prerequisites[i] = [ai, bi]
// 表示在选修课程 ai 前 必须 先选修 bi
// 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示：[0,1]
// 返回你为了学完所有课程所安排的学习顺序。可能会有多个正确的顺序
// 你只要返回 任意一种 就可以了。如果不可能完成所有课程，返回 一个空数组
// 测试链接 : https://leetcode.cn/problems/course-schedule-ii/
class Solution {
 public:
  vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
    vector<vector<int>> graph(numCourses);
    vector<int> indegree(numCourses);
    for (auto &edge : prerequisites) {
      graph[edge[1]].push_back(edge[0]);
      indegree[edge[0]]++;
    }

    vector<int> queue(numCourses);
    int l = 0;
    int r = 0;
    for (int i = 0; i < numCourses; ++i) {
      if (indegree[i] == 0) {
        queue[r++] = i;
      }
    }

    int cnt = 0;
    while (l < r) {
      int cur = queue[l++];
      ++cnt;

      for (int next : graph[cur]) {
        if (--indegree[next] == 0) {
          queue[r++] = next;
        }
      }
    }

    if (cnt != numCourses) {
      return {};
    }

    return queue;
  }
};

auto __FAST_IO__ = []() noexcept -> int {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();
