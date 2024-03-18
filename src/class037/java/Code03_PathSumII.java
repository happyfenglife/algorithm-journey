import java.util.ArrayList;
import java.util.List;

// 测试链接 : https://leetcode.cn/problems/path-sum-ii/
public class Solution {
    public static class TreeNode {
        public int val;
        public TreeNode left;
        public TreeNode right;
    }

    public List<List<Integer>> pathSum(TreeNode root, int targetSum) {
        List<List<Integer>> ans = new ArrayList<>();
        if (root != null) {
            List<Integer> path = new ArrayList<>();
            f(root, targetSum, 0, path, ans);
        }

        return ans;
    }

    private static void f(TreeNode cur, int aim, int sum, List<Integer> path, List<List<Integer>> ans) {
        if (cur.left == null && cur.right == null) {
            if (cur.val + sum == aim) {
                path.add(cur.val);
                copy(path, ans);
                path.remove(path.size() - 1);
            }
        } else {
            path.add(cur.val);
            if (cur.left != null) {
                f(cur.left, aim, sum + cur.val, path, ans);
            }
            if (cur.right != null) {
                f(cur.right, aim, sum + cur.val, path, ans);
            }

            path.remove(path.size() - 1);
        }
    }

    private static void copy(List<Integer> path, List<List<Integer>> ans) {
        List<Integer> copy = new ArrayList<>(path);
        ans.add(copy);
    }
}