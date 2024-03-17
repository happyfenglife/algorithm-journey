import java.util.ArrayList;
import java.util.List;

// 测试链接 : https://leetcode.cn/problems/binary-tree-level-order-traversal/
public class Solution {
    public static class TreeNode {
        public int val;
        public TreeNode left;
        public TreeNode right;
    }

    public static int MAXN = 2001;

    public static TreeNode[] queue = new TreeNode[MAXN];

    public static int l, r;

    public static List<List<Integer>> levelOrder(TreeNode root) {
        List<List<Integer>> ans = new ArrayList<>();
        if (root != null) {
            l = r = 0;
            queue[r++] = root;

            while (l < r) {
                int size = r - l;
                ArrayList<Integer> list = new ArrayList<>();
                for (int i = 0; i < size; i++) {
                    TreeNode cur = queue[l++];
                    list.add(cur.val);
                    if (cur.left != null) {
                        queue[r++] = cur.left;
                    }
                    if (cur.right != null) {
                        queue[r++] = cur.right;
                    }
                }

                ans.add(list);
            }
        }

        return ans;
    }
}