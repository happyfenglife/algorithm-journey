// 归并排序，填函数练习风格
// 测试链接 : https://leetcode.cn/problems/sort-an-array/
public class Solution {
    public static int[] sortArray(int[] nums) {
        if (nums.length > 1) {
            // mergeSort1为递归方法
            // mergeSort2为非递归方法
            // 用哪个都可以
            // mergeSort1(nums);
            mergeSort2(nums);
        }

        return nums;
    }

    public static int MAXN = 50001;

    public static int[] aux = new int[MAXN];

    // 归并排序递归版
    public static void mergeSort1(int[] arr) {
        sort(arr, 0, arr.length - 1);
    }

    // 归并排序非递归版
    public static void mergeSort2(int[] arr) {
        int n = arr.length;
        for (int l, m, r, step = 1; step < n; step <<= 1) {
            l = 0;

            while (l < n) {
                m = l + step - 1;

                if (m + 1 >= n) {
                    break;
                }

                r = Math.min(l + (step << 1) - 1, n - 1);
                merge(arr, l, m, r);
                l = r + 1;
            }
        }
    }

    public static void sort(int[] arr, int l, int r) {
        if (l == r) {
            return;
        }

        int m = (l + r) / 2;
        sort(arr, l, m);
        sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }

    public static void merge(int[] arr, int l, int m, int r) {
        int i = l;
        int a = l;
        int b = m + 1;

        while (a <= m && b <= r) {
            aux[i++] = arr[a] <= arr[b] ? arr[a++] : arr[b++];
        }

        while (a <= m) {
            aux[i++] = arr[a++];
        }

        while (b <= r) {
            aux[i++] = arr[b++];
        }

        for (i = l; i <= r; ++i) {
            arr[i] = aux[i];
        }
    }
}