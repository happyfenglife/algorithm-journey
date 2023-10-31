#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

auto __FAST_IO_ = []() noexcept {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  return 0;
}();

// 单词接龙 II
// 按字典 wordList 完成从单词 beginWord 到单词 endWord 转化
// 一个表示此过程的 转换序列 是形式上像
// beginWord -> s1 -> s2 -> ... -> sk 这样的单词序列，并满足：
// 每对相邻的单词之间仅有单个字母不同
// 转换过程中的每个单词 si（1 <= i <= k）必须是字典 wordList 中的单词
// 注意，beginWord 不必是字典 wordList 中的单词
// sk == endWord
// 给你两个单词 beginWord 和 endWord ，以及一个字典 wordList
// 请你找出并返回所有从 beginWord 到 endWord 的 最短转换序列
// 如果不存在这样的转换序列，返回一个空列表
// 每个序列都应该以单词列表 [beginWord, s1, s2, ..., sk] 的形式返回
// 测试链接 : https://leetcode.cn/problems/word-ladder-ii/
class Solution {
  unordered_set<string> dict;
  unordered_set<string> cur;
  unordered_set<string> nextLevel;
  vector<vector<string>> ans;
  deque<string> path;
  unordered_map<string, vector<string>> graph;

 public:
  vector<vector<string>> findLadders(const string &beginWord, const string &endWord, vector<string> &wordList) {
    build(wordList);

    if (!dict.count(endWord)) {
      return {};
    }

    if (bfs(beginWord, endWord)) {
      dfs(endWord, beginWord);
    }

    return ans;
  }

 private:
  bool bfs(const string &begin, const string &end) {
    bool find = false;
    cur.insert(begin);

    while (!cur.empty()) {
      for (const string &word : cur) {
        dict.erase(word);
      }

      for (string word : cur) {
        // word : 去扩
        // 每个位置，字符a~z，换一遍！检查在词表中是否存在
        // 避免，加工出自己
        string str = word;
        for (int i = 0; i < word.size(); ++i) {
          char old = word[i];

          for (char c = 'a'; c <= 'z'; ++c) {
            if (c == old) {
              continue;
            }

            word[i] = c;
            if (dict.count(word)) {
              if (word == end) {
                find = true;
              }

              graph[word].push_back(str);
              nextLevel.insert(word);
            }
          }

          word[i] = old;
        }
      }

      if (find) {
        return true;
      } else {
        cur = nextLevel;
        nextLevel.clear();
      }
    }

    return false;
  }

  void dfs(const string &begin, const string &end) {
    path.push_front(begin);

    if (begin == end) {
      ans.emplace_back(path.begin(), path.end());
    } else if (graph.count(begin)) {
      for (string &next : graph[begin]) {
        dfs(next, end);
      }
    }

    path.pop_front();
  }

  void build(vector<string> &wordList) {
    dict = unordered_set(wordList.begin(), wordList.end());
    ans.clear();
    cur.clear();
    nextLevel.clear();
    path.clear();
    graph.clear();
  }
};
