import java.util.ArrayList;
import java.util.Comparator;
import java.util.PriorityQueue;

// 合并K个有序链表
// 测试链接：https://www.nowcoder.com/practice/65cfde9e5b9b4cf2b6bafa5f3ef33fa6
public class Solution {
    public static class ListNode {
        public int val;

        public ListNode next;

        public ListNode(int val) {
            this.val = val;
        }
    }

    // 提交以下的方法
    public static ListNode mergeKLists(ArrayList<ListNode> arr) {
        // 小根堆
        PriorityQueue<ListNode> heap = new PriorityQueue<>(Comparator.comparingInt(a -> a.val));
        for (ListNode h : arr) {
            // 遍历所有的头！
            if (h != null) {
                heap.add(h);
            }
        }

        if (heap.isEmpty()) {
            return null;
        }

        // 先弹出一个节点，做总头部
        ListNode h = heap.poll();
        ListNode pre = h;
        if (pre.next != null) {
            heap.add(pre.next);
        }

        while (!heap.isEmpty()) {
            ListNode cur = heap.poll();
            pre.next = cur;
            pre = cur;

            if (cur.next != null) {
                heap.add(cur.next);
            }
        }

        return h;
    }
}