#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>

using namespace std;

auto __FAST_IO__ = []() noexcept {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  return 0;
}();

// 贴纸拼词
// 我们有 n 种不同的贴纸。每个贴纸上都有一个小写的英文单词。
// 您想要拼写出给定的字符串 target ，方法是从收集的贴纸中切割单个字母并重新排列它们
// 如果你愿意，你可以多次使用每个贴纸，每个贴纸的数量是无限的。
// 返回你需要拼出 target 的最小贴纸数量。如果任务不可能，则返回 -1
// 注意：在所有的测试用例中，所有的单词都是从 1000 个最常见的美国英语单词中随机选择的
// 并且 target 被选择为两个随机单词的连接。
// 测试链接 : https://leetcode.cn/problems/stickers-to-spell-word/
class Solution {
 public:
  int minStickers(vector<string> &stickers, string &target) {
    int n = stickers.size();
    vector<vector<string>> graph(26, vector<string>());
    unordered_set<string> visited;

    sort(target.begin(), target.end());

    for (string &s : stickers) {
      sort(s.begin(), s.end());

      for (int i = 0; i < s.size(); ++i) {
        if (i == 0 || s[i] != s[i - 1]) {
          graph[s[i] - 'a'].push_back(s);
        }
      }
    }

    queue<string> q;
    q.push(target);
    visited.emplace(target);
    int level = 1;

    while (!q.empty()) {
      int size = q.size();

      for (int i = 0; i < size; ++i) {
        string cur = q.front();
        q.pop();

        for (string &s : graph[cur[0] - 'a']) {
          string next = process(cur, s);

          if (next.empty()) {
            return level;
          } else if (!visited.count(next)) {
            visited.emplace(next);
            q.push(next);
          }
        }
      }

      ++level;
    }

    return -1;
  }

 private:
  string process(const string &t, const string &s) {
    string res;
    for (int i = 0, j = 0; i < t.size();) {
      if (j == s.size()) {
        res.push_back(t[i++]);
      } else {
        if (t[i] < s[j]) {
          res.push_back(t[i++]);
        } else if (t[i] > s[j]) {
          j++;
        } else {
          i++;
          j++;
        }
      }
    }

    return res;
  }
};
