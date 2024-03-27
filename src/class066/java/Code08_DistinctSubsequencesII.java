// 不同的子序列 II
// 给定一个字符串 s，计算 s 的 不同非空子序列 的个数
// 因为结果可能很大，所以返回答案需要对 10^9 + 7 取余
// 字符串的 子序列 是经由原字符串删除一些（也可能不删除）
// 字符但不改变剩余字符相对位置的一个新字符串
// 例如，"ace" 是 "abcde" 的一个子序列，但 "aec" 不是
// 测试链接 : https://leetcode.cn/problems/distinct-subsequences-ii/
public class Solution {
    public static int MOD = 1000000007;

    // 时间复杂度O(n)，n是字符串s的长度
    public static int distinctSubseqII(String s) {
        char[] str = s.toCharArray();
        int[] cnt = new int[26];
        int all = 1, newAdd;
        for (char c : str) {
            newAdd = (all - cnt[c - 'a'] + MOD) % MOD;
            cnt[c - 'a'] = (cnt[c - 'a'] + newAdd) % MOD;
            all = (all + newAdd) % MOD;
        }

        return (all - 1 + MOD) % MOD;
    }
}