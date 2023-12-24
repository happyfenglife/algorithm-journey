#include <algorithm>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;

  TreeNode(int v)
    : val(v), left(nullptr), right(nullptr) {
  }
};

struct Info {
  int diameter;
  int height;
};

// 二叉树的直径
// 给你一棵二叉树的根节点，返回该树的直径
// 二叉树的 直径 是指树中任意两个节点之间最长路径的长度
// 这条路径可能经过也可能不经过根节点 root
// 两节点之间路径的 长度 由它们之间边数表示
// 测试链接 : https://leetcode.cn/problems/diameter-of-binary-tree/
class Solution {
  public:
    int diameterOfBinaryTree(TreeNode *root) {
      return f(root).diameter;
    }

  private:
    Info f(TreeNode *x) {
      if (!x) {
        return {0, 0};
      }

      Info lInfo = f(x->left);
      Info rInfo = f(x->right);
      int height = max(lInfo.height, rInfo.height) + 1;
      int diameter = max(lInfo.diameter, rInfo.diameter);
      diameter = max(diameter, lInfo.height + rInfo.height);
      return {diameter, height};
    }
};
