// ─────────────────────────────────────────
//  COLLECTIONS  (ArrayList, HashMap, HashSet, Queue, Stack)
// ─────────────────────────────────────────

import java.util.*;
import java.util.stream.*;

public class Collections {
    public static void main(String[] args) {

        // ════════════════════════════════════
        //  ArrayList<T>  — dynamic array, ordered, allows duplicates
        // ════════════════════════════════════
        List<String> fruits = new ArrayList<>(List.of("apple", "banana", "cherry"));

        // Add
        fruits.add("mango");
        fruits.add(1, "avocado");            // insert at index
        fruits.addAll(List.of("kiwi", "plum"));

        // Access
        System.out.println(fruits.get(0));   // apple
        System.out.println(fruits.size());   // 7
        System.out.println(fruits.get(fruits.size() - 1));  // last element

        // Update
        fruits.set(0, "APPLE");             // replace at index

        // Remove
        fruits.remove("mango");             // by value
        fruits.remove(0);                   // by index

        // Search
        System.out.println(fruits.contains("banana"));  // true
        System.out.println(fruits.indexOf("banana"));   // index or -1

        // Sort
        Collections.sort(fruits);           // ascending
        fruits.sort(Comparator.reverseOrder());         // descending
        fruits.sort(Comparator.comparingInt(String::length)); // by length

        // Iterate
        for (String fruit : fruits)
            System.out.print(fruit + " ");
        System.out.println();

        fruits.forEach(f -> System.out.print(f + " "));
        System.out.println();

        // ════════════════════════════════════
        //  HashMap<K,V>  — key-value pairs, no guaranteed order
        // ════════════════════════════════════
        Map<String, Integer> scores = new HashMap<>();
        scores.put("Alice", 90);
        scores.put("Bob", 85);
        scores.put("Carol", 92);

        // Access
        System.out.println(scores.get("Alice"));         // 90
        System.out.println(scores.get("Dave"));          // null — no exception
        System.out.println(scores.getOrDefault("Dave", 0)); // 0

        // Add / Update
        scores.put("Dave", 78);            // add
        scores.put("Alice", 95);           // update
        scores.putIfAbsent("Bob", 99);     // only if key doesn't exist

        // Remove
        scores.remove("Dave");

        // Check
        System.out.println(scores.containsKey("Bob"));     // true
        System.out.println(scores.containsValue(95));      // true

        // Iterate
        for (Map.Entry<String, Integer> entry : scores.entrySet())
            System.out.println(entry.getKey() + ": " + entry.getValue());

        scores.forEach((k, v) -> System.out.println(k + " → " + v));

        System.out.println(scores.keySet());    // Set of keys
        System.out.println(scores.values());    // Collection of values

        // LinkedHashMap — preserves insertion order
        Map<String, Integer> ordered = new LinkedHashMap<>();
        ordered.put("z", 1); ordered.put("a", 2); ordered.put("m", 3);
        System.out.println(ordered);  // {z=1, a=2, m=3} — insertion order kept

        // TreeMap — sorted by key
        Map<String, Integer> sorted = new TreeMap<>(scores);
        System.out.println(sorted);   // alphabetical order

        // ════════════════════════════════════
        //  HashSet<T>  — unique values, no order
        // ════════════════════════════════════
        Set<Integer> setA = new HashSet<>(Set.of(1, 2, 3, 4, 5));
        Set<Integer> setB = new HashSet<>(Set.of(4, 5, 6, 7, 8));

        setA.add(6);
        setA.remove(1);
        System.out.println(setA.contains(3));   // true

        // Set operations (need copies — these modify in place)
        Set<Integer> union = new HashSet<>(setA);
        union.addAll(setB);
        System.out.println(union);

        Set<Integer> intersection = new HashSet<>(setA);
        intersection.retainAll(setB);
        System.out.println(intersection);

        Set<Integer> diff = new HashSet<>(setA);
        diff.removeAll(setB);
        System.out.println(diff);

        // LinkedHashSet — preserves insertion order
        Set<String> linked = new LinkedHashSet<>(List.of("banana", "apple", "cherry"));
        System.out.println(linked);   // [banana, apple, cherry] — order kept

        // TreeSet — sorted
        Set<String> tree = new TreeSet<>(linked);
        System.out.println(tree);    // [apple, banana, cherry]

        // ════════════════════════════════════
        //  Queue<T>  — FIFO (first in, first out)
        // ════════════════════════════════════
        Queue<String> queue = new LinkedList<>();
        queue.offer("first");
        queue.offer("second");
        queue.offer("third");

        System.out.println(queue.peek());    // first — doesn't remove
        System.out.println(queue.poll());    // first — removes it
        System.out.println(queue.size());    // 2

        // ════════════════════════════════════
        //  Deque  — double-ended queue (Stack + Queue)
        // ════════════════════════════════════
        Deque<Integer> stack = new ArrayDeque<>();
        stack.push(1);   // push to front
        stack.push(2);
        stack.push(3);

        System.out.println(stack.peek());    // 3 — top of stack
        System.out.println(stack.pop());     // 3 — removes from front
        System.out.println(stack.size());    // 2

        // ════════════════════════════════════
        //  Unmodifiable collections (Java 9+)
        // ════════════════════════════════════
        List<String> immutableList = List.of("a", "b", "c");
        Map<String, Integer> immutableMap = Map.of("x", 1, "y", 2);
        Set<Integer> immutableSet = Set.of(1, 2, 3);
        // immutableList.add("d");  // UnsupportedOperationException
    }
}
