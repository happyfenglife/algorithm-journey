// 测试链接 : https://leetcode.cn/problems/maximum-width-of-binary-tree/
public class Solution {
    public static class TreeNode {
        public int val;
        public TreeNode left;
        public TreeNode right;
    }

    public static int MAXN = 3001;

    public static TreeNode[] nq = new TreeNode[MAXN];

    public static int[] iq = new int[MAXN];

    public static int l, r;

    public static int widthOfBinaryTree(TreeNode root) {
        int ans = 1;
        l = r = 0;
        nq[r] = root;
        iq[r++] = 1;
        while (l < r) {
            int size = r - l;
            ans = Math.max(ans, iq[r - 1] - iq[l] + 1);
            for (int i = 0; i < size; i++) {
                TreeNode node = nq[l];
                int id = iq[l++];
                if (node.left != null) {
                    nq[r] = node.left;
                    iq[r++] = id * 2;
                }
                if (node.right != null) {
                    nq[r] = node.right;
                    iq[r++] = id * 2 + 1;
                }
            }
        }

        return ans;
    }
}