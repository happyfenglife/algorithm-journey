// 测试链接 : https://leetcode.cn/problems/validate-binary-search-tree/
public class Solution {
    public static class TreeNode {
        public int val;
        public TreeNode left;
        public TreeNode right;
    }

    public static long min, max;

    public static boolean isValidBST(TreeNode root) {
        if (root == null) {
            min = Long.MAX_VALUE;
            max = Long.MIN_VALUE;
            return true;
        }

        boolean lok = isValidBST(root.left);
        long lmin = min;
        long lmax = max;

        boolean rok = isValidBST(root.right);
        long rmin = min;
        long rmax = max;

        min = Math.min(Math.min(lmin, rmin), root.val);
        max = Math.max(Math.max(lmax, rmax), root.val);
        return lok && rok && lmax < root.val && root.val < rmin;
    }
}