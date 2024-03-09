// 将数组和减半的最少操作次数
// 测试链接 : https://leetcode.cn/problems/minimum-operations-to-halve-array-sum/
public class Solution {
    public static int halveArray(int[] nums) {
        size = nums.length;
        long sum = 0;
        for (int i = size - 1; i >= 0; i--) {
            heap[i] = (long) nums[i] << 20;
            sum += heap[i];
            heapify(i);
        }

        sum /= 2;
        int ans = 0;
        for (long minus = 0; minus < sum; ++ans) {
            heap[0] /= 2;
            minus += heap[0];
            heapify(0);
        }

        return ans;
    }

    public static int MAXN = 100001;

    public static long[] heap = new long[MAXN];

    public static int size;

    public static void swap(int i, int j) {
        long tmp = heap[i];
        heap[i] = heap[j];
        heap[j] = tmp;
    }

    public static void heapify(int i) {
        int l = i * 2 + 1;
        while (l < size) {
            int best = l + 1 < size && heap[l + 1] > heap[l] ? l + 1 : l;
            best = heap[best] > heap[i] ? best : i;
            if (best == i) {
                break;
            }

            swap(best, i);
            i = best;
            l = i * 2 + 1;
        }
    }
}