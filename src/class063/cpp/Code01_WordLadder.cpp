#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

auto __FAST_IO_ = []() noexcept {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  return 0;
}();

// 单词接龙
// 字典 wordList 中从单词 beginWord 和 endWord 的 转换序列
// 是一个按下述规格形成的序列 beginWord -> s1 -> s2 -> ... -> sk ：
// 每一对相邻的单词只差一个字母。
// 对于 1 <= i <= k 时，每个 si 都在 wordList 中
// 注意， beginWord 不需要在 wordList 中。sk == endWord
// 给你两个单词 beginWord 和 endWord 和一个字典 wordList
// 返回 从 beginWord 到 endWord 的 最短转换序列 中的 单词数目
// 如果不存在这样的转换序列，返回 0 。
// 测试链接 : https://leetcode.cn/problems/word-ladder/
class Solution {
 public:
  int ladderLength(const string &beginWord, const string &endWord, vector<string> &wordList) {
    unordered_set<string> dict(wordList.begin(), wordList.end());

    if (!dict.count(endWord)) {
      return 0;
    }

    // 数量小的一侧
    unordered_set<string> small;
    // 数量大的一侧
    unordered_set<string> big;
    // 由数量小的一侧，所扩展出的下一层列表
    unordered_set<string> nextLevel;

    small.insert(beginWord);
    big.insert(endWord);

    for (int len = 2; !small.empty(); ++len) {
      for (const string &word : small) {
        string str = word;

        // 从小侧扩展
        for (int j = 0; j < str.size(); ++j) {
          // 每一位字符都试
          char old = str[j];

          for (char c = 'a'; c <= 'z'; ++c) {
            // 每一位字符都从a到z换一遍
            if (c == old) {
              continue;
            }

            str[j] = c;
            if (big.count(str)) {
              return len;
            }

            if (dict.count(str)) {
              dict.erase(str);
              nextLevel.insert(str);
            }
          }

          str[j] = old;
        }
      }

      if (nextLevel.size() <= big.size()) {
        small = nextLevel;
      } else {
        small = big;
        big = nextLevel;
      }

      nextLevel.clear();
    }

    return 0;
  }
};
