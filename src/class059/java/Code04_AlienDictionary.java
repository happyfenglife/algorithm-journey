import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;

// 外星人字典
// 测试链接 : https://www.lintcode.com/problem/892/description?showListFe=true&page=1&submissionStatus=ACCEPTED&pageSize=50
public class Code04_AlienDictionary {
    public static String alienOrder(String[] words) {
        int[] indegree = new int[26];
        Arrays.fill(indegree, -1);
        for (String w : words) {
            for (int i = 0; i < w.length(); i++) {
                indegree[w.charAt(i) - 'a'] = 0;
            }
        }

        // 'a' -> 0
        // 'b' -> 1
        // 'z' -> 25
        // x -> x - 'a'
        ArrayList<ArrayList<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < 26; i++) {
            graph.add(new ArrayList<>());
        }

        for (int i = 0, j, len; i < words.length - 1; i++) {
            String cur = words[i];
            String next = words[i + 1];
            j = 0;
            len = Math.min(cur.length(), next.length());
            for (; j < len; ++j) {
                if (cur.charAt(j) != next.charAt(j)) {
                    graph.get(cur.charAt(j) - 'a').add(next.charAt(j) - 'a');
                    indegree[next.charAt(j) - 'a']++;
                    break;
                }
            }

            if (j < cur.length() && j == next.length()) {
                return "";
            }
        }

        PriorityQueue<Integer> heap = new PriorityQueue<>();
        int kinds = 0;
        for (int i = 0; i < 26; i++) {
            if (indegree[i] != -1) {
                ++kinds;
            }
            if (indegree[i] == 0) {
                heap.add(i);
            }
        }

        StringBuilder ans = new StringBuilder();
        while (!heap.isEmpty()) {
            int cur = heap.poll();
            ans.append((char) (cur + 'a'));
            for (int next : graph.get(cur)) {
                if (--indegree[next] == 0) {
                    heap.add(next);
                }
            }
        }

        return ans.length() == kinds ? ans.toString() : "";
    }
}