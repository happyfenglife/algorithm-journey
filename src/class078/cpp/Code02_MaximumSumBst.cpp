#include <algorithm>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;

  TreeNode() : val(-1), left(nullptr), right(nullptr) {
  }

  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
  }

  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {
  }
};

struct Info {
  int upper;
  int lower;
  int sum;
  bool isBst;
  int maxBstSum;
};

// 二叉搜索子树的最大键值和
// 给你一棵以 root 为根的二叉树
// 请你返回 任意 二叉搜索子树的最大键值和
// 二叉搜索树的定义如下：
// 任意节点的左子树中的键值都 小于 此节点的键值
// 任意节点的右子树中的键值都 大于 此节点的键值
// 任意节点的左子树和右子树都是二叉搜索树
// 测试链接 : https://leetcode.cn/problems/maximum-sum-bst-in-binary-tree/
class Solution {
  public:
    int maxSumBST(TreeNode *root) {
      return f(root).maxBstSum;
    }

  private:
    Info f(TreeNode *x) {
      if (!x) {
        return {INT_MIN, INT_MAX, 0, true, 0};
      }

      Info lInfo = f(x->left);
      Info rInfo = f(x->right);
      int upper = max({x->val, lInfo.upper, rInfo.upper});
      int lower = min({x->val, lInfo.lower, rInfo.lower});
      int sum = lInfo.sum + rInfo.sum + x->val;
      bool isBst = lInfo.isBst && rInfo.isBst && x->val > lInfo.upper && x->val < rInfo.lower;
      int maxBstSum = max(lInfo.maxBstSum, rInfo.maxBstSum);

      if (isBst) {
        maxBstSum = max(maxBstSum, sum);
      }

      return {upper, lower, sum, isBst, maxBstSum};
    }
};
