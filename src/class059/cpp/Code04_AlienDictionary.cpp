#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 火星词典
// 现有一种使用英语字母的火星语言
// 这门语言的字母顺序对你来说是未知的。
// 给你一个来自这种外星语言字典的字符串列表 words
// words 中的字符串已经 按这门新语言的字母顺序进行了排序 。
// 如果这种说法是错误的，并且给出的 words 不能对应任何字母的顺序，则返回 ""
// 否则，返回一个按新语言规则的 字典递增顺序 排序的独特字符串
// 如果有多个解决方案，则返回正常字典序最小的那个
// words中的单词一定都是小写英文字母组成的
// 测试链接 : https://www.lintcode.com/problem/892/
class Solution {
 public:
  string alienOrder(vector<string> &words) {
    vector<int> indegree(26, -1);
    for (string &w : words) {
      for (char c : w) {
        indegree[c - 'a'] = 0;
      }
    }

    vector<vector<int>> graph(26);

    for (int i = 0, j, len; i < words.size() - 1; ++i) {
      string &cur = words[i];
      string &next = words[i + 1];
      j = 0;
      len = min(cur.size(), next.size());

      for (; j < len; ++j) {
        if (cur[j] != next[j]) {
          graph[cur[j] - 'a'].push_back(next[j] - 'a');
          indegree[next[j] - 'a']++;
          break;
        }
      }

      if (j < cur.size() && j == next.size()) {
        return "";
      }
    }

    priority_queue<int, vector<int>, greater<>> queue;
    int kinds = 0;
    for (int i = 0; i < 26; ++i) {
      if (indegree[i] != -1) {
        kinds++;
      }

      if (indegree[i] == 0) {
        queue.push(i);
      }
    }

    string ans;
    while (!queue.empty()) {
      int cur = queue.top();
      queue.pop();
      ans.push_back(cur + 'a');

      for (int next : graph[cur]) {
        if (--indegree[next] == 0) {
          queue.push(next);
        }
      }
    }

    return ans.length() == kinds ? ans : "";
  }
};

auto __FAST_IO__ = []() noexcept -> int {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
};
