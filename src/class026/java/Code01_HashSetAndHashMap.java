import java.util.HashMap;
import java.util.HashSet;

public class Solution {
    public static void main(String[] args) {
        // Integer、Long、Double、Float
        // Byte、Short、Character、Boolean
        // String等都有这个特征
        String str1 = new String("Hello");
        String str2 = new String("Hello");

        // false，因为不同的内存地址
        System.out.println(str1 == str2);
        // true，因为它们的值是相同的
        System.out.println(str1.equals(str2));

        HashSet<String> set = new HashSet<>();
        set.add(str1);
        System.out.println(set.contains("Hello"));
        System.out.println(set.contains(str2));
        set.add(str2);
        System.out.println(set.size());
        set.remove(str2);
        System.out.println(set.isEmpty());

        System.out.println("===========");

        HashMap<String, String> map1 = new HashMap<>();
        map1.put(str1, "World");
        System.out.println(map1.containsKey("Hello"));
        System.out.println(map1.containsKey(str2));
        System.out.println(map1.get(str2));
        System.out.println(map1.get("你好") == null);
        map1.remove("Hello");
        System.out.println(map1.size());

        System.out.println("===========");

        Student s1 = new Student(17, "张三");
        Student s2 = new Student(17, "张三");
        HashMap<Student, String> map3 = new HashMap<>();
        map3.put(s1, "这是张三");
        System.out.println(map3.containsKey(s1));
        System.out.println(map3.containsKey(s2));
        map3.put(s2, "这是另一个张三");
        System.out.println(map3.size());
        System.out.println(map3.get(s1));
        System.out.println(map3.get(s2));
    }

    public static class Student {
        public int age;
        public String name;

        public Student(int a, String b) {
            age = a;
            name = b;
        }
    }
}