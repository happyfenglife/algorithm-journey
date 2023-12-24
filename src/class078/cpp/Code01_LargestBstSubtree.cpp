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
  long long upper;
  long long lower;
  bool isBst;
  int maxBstSize;
};

// 最大BST子树
// 给定一个二叉树，找到其中最大的二叉搜索树（BST）子树，并返回该子树的大小
// 其中，最大指的是子树节点数最多的
// 二叉搜索树（BST）中的所有节点都具备以下属性：
// 左子树的值小于其父（根）节点的值
// 右子树的值大于其父（根）节点的值
// 注意：子树必须包含其所有后代
// 测试链接 : https://leetcode.cn/problems/largest-bst-subtree/
class Solution {
  public:
    int largestBSTSubtree(TreeNode *root) {
      return f(root).maxBstSize;
    }

  private:
    Info f(TreeNode *x) {
      if (!x) {
        return {LONG_LONG_MIN, LONG_LONG_MAX, true, 0};
      }

      Info lInfo = f(x->left);
      Info rInfo = f(x->right);
      long long maxVal = max({(long long) x->val, lInfo.upper, rInfo.upper});
      long long minVal = min({(long long) x->val, lInfo.upper, rInfo.upper});
      bool isBst = lInfo.isBst && rInfo.isBst && lInfo.upper < x->val && x->val < rInfo.lower;
      int maxBstSize;

      if (isBst) {
        maxBstSize = lInfo.maxBstSize + rInfo.maxBstSize + 1;
      } else {
        maxBstSize = max(lInfo.maxBstSize, rInfo.maxBstSize);
      }

      return {maxVal, minVal, isBst, maxBstSize};
    }
};
