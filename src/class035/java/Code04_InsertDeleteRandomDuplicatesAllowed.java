import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;

// https://leetcode.cn/problems/insert-delete-getrandom-o1-duplicates-allowed/
public class Solution {
    class RandomizedCollection {
        public HashMap<Integer, HashSet<Integer>> map;

        public ArrayList<Integer> arr;

        public RandomizedCollection() {
            map = new HashMap<>();
            arr = new ArrayList<>();
        }

        public boolean insert(int val) {
            arr.add(val);
            HashSet<Integer> set = map.getOrDefault(val, new HashSet<>());
            set.add(arr.size() - 1);
            map.put(val, set);

            return set.size() == 1;
        }

        public boolean remove(int val) {
            if (!map.containsKey(val)) {
                return false;
            }

            HashSet<Integer> valSet = map.get(val);
            Integer valAnyIndex = valSet.iterator().next();
            int endValue = arr.get(arr.size() - 1);
            if (val == endValue) {
                valSet.remove(arr.size() - 1);
            } else {
                HashSet<Integer> endValueSet = map.get(endValue);
                endValueSet.add(valAnyIndex);
                arr.set(valAnyIndex, endValue);
                endValueSet.remove(arr.size() - 1);
                valSet.remove(valAnyIndex);
            }

            arr.remove(arr.size() - 1);
            if (valSet.isEmpty()) {
                map.remove(val);
            }

            return true;
        }

        public int getRandom() {
            return arr.get((int) (Math.random() * arr.size()));
        }
    }
}