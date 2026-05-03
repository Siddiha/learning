// ─────────────────────────────────────────
//  ITERATORS & COMPARATORS
// ─────────────────────────────────────────

import java.util.*;
import java.util.stream.*;

public class IteratorsAndComparators {

    // ════════════════════════════════════
    //  ITERATOR & ITERABLE
    // ════════════════════════════════════

    // Make a class iterable so it works in for-each loops
    static class NumberRange implements Iterable<Integer> {
        private final int start;
        private final int end;
        private final int step;

        NumberRange(int start, int end, int step) {
            this.start = start;
            this.end   = end;
            this.step  = step;
        }

        @Override
        public Iterator<Integer> iterator() {
            return new Iterator<>() {
                private int current = start;

                @Override
                public boolean hasNext() { return current < end; }

                @Override
                public Integer next() {
                    if (!hasNext()) throw new NoSuchElementException();
                    int value = current;
                    current += step;
                    return value;
                }
            };
        }
    }

    // Generic iterable stack
    static class Stack<T> implements Iterable<T> {
        private final List<T> items = new ArrayList<>();

        public void push(T item) { items.add(item); }
        public T pop()           { return items.remove(items.size() - 1); }
        public boolean isEmpty() { return items.isEmpty(); }
        public int size()        { return items.size(); }

        @Override
        public Iterator<T> iterator() {
            // iterate from top to bottom
            return new Iterator<>() {
                int index = items.size() - 1;

                @Override public boolean hasNext() { return index >= 0; }
                @Override public Integer next()    { return (Integer) items.get(index--); }
            };
        }
    }

    // ════════════════════════════════════
    //  COMPARABLE vs COMPARATOR
    // ════════════════════════════════════

    // Comparable — natural ordering built into the class
    static class Student implements Comparable<Student> {
        String name;
        double gpa;
        int age;

        Student(String name, double gpa, int age) {
            this.name = name;
            this.gpa  = gpa;
            this.age  = age;
        }

        // Natural order — by GPA descending
        @Override
        public int compareTo(Student other) {
            return Double.compare(other.gpa, this.gpa);  // descending
        }

        @Override
        public String toString() {
            return String.format("Student(%s, GPA=%.1f, age=%d)", name, gpa, age);
        }
    }

    public static void main(String[] args) {

        // ── Iterable & Iterator ───────────────────
        NumberRange evens = new NumberRange(0, 20, 2);
        for (int n : evens)
            System.out.print(n + " ");   // 0 2 4 6 8 10 12 14 16 18
        System.out.println();

        // Manual iteration
        Iterator<Integer> it = evens.iterator();
        while (it.hasNext())
            System.out.print(it.next() + " ");
        System.out.println();

        Stack<String> stack = new Stack<>();
        stack.push("a"); stack.push("b"); stack.push("c");
        for (Object s : stack)
            System.out.print(s + " ");   // c b a (top to bottom)
        System.out.println();

        // ── Iterator on built-in collections ──────
        List<String> list = new ArrayList<>(List.of("apple", "banana", "cherry", "fig"));
        Iterator<String> listIt = list.iterator();
        while (listIt.hasNext()) {
            String item = listIt.next();
            if (item.length() <= 3) listIt.remove();   // safe removal during iteration
        }
        System.out.println(list);   // [apple, banana, cherry]

        // ── ListIterator — bidirectional ──────────
        ListIterator<String> lit = list.listIterator(list.size());  // start at end
        while (lit.hasPrevious())
            System.out.print(lit.previous() + " ");   // cherry banana apple
        System.out.println();

        // ── Comparable ────────────────────────────
        List<Student> students = new ArrayList<>(List.of(
            new Student("Alice", 3.8, 20),
            new Student("Bob",   3.5, 22),
            new Student("Carol", 3.9, 19),
            new Student("Dave",  3.5, 21)
        ));

        Collections.sort(students);   // uses compareTo (GPA descending)
        students.forEach(System.out::println);
        System.out.println();

        // ── Comparator — external ordering ────────
        // By name alphabetically
        Comparator<Student> byName = Comparator.comparing(s -> s.name);
        students.sort(byName);
        students.forEach(System.out::println);
        System.out.println();

        // By age ascending
        students.sort(Comparator.comparingInt(s -> s.age));
        students.forEach(System.out::println);
        System.out.println();

        // Chained: primary by GPA desc, secondary by name asc
        Comparator<Student> complex =
            Comparator.comparingDouble((Student s) -> s.gpa)
                      .reversed()
                      .thenComparing(s -> s.name);
        students.sort(complex);
        students.forEach(System.out::println);
        System.out.println();

        // Reverse a comparator
        Comparator<String> byLength = Comparator.comparingInt(String::length);
        Comparator<String> byLengthDesc = byLength.reversed();

        List<String> words = new ArrayList<>(List.of("banana", "fig", "apple", "kiwi"));
        words.sort(byLengthDesc);
        System.out.println(words);   // [banana, apple, kiwi, fig]

        // Null-safe comparators
        List<String> withNulls = new ArrayList<>(Arrays.asList("b", null, "a", null, "c"));
        withNulls.sort(Comparator.nullsFirst(Comparator.naturalOrder()));
        System.out.println(withNulls);   // [null, null, a, b, c]

        withNulls.sort(Comparator.nullsLast(Comparator.naturalOrder()));
        System.out.println(withNulls);   // [a, b, c, null, null]

        // ── TreeMap with custom comparator ────────
        TreeMap<String, Integer> map = new TreeMap<>(Comparator.reverseOrder());
        map.put("banana", 1); map.put("apple", 2); map.put("cherry", 3);
        System.out.println(map);   // {cherry=3, banana=1, apple=2}

        // ── PriorityQueue with comparator ─────────
        // Min-heap by default
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();
        minHeap.addAll(List.of(5, 2, 8, 1, 9));
        System.out.print("Min-heap poll order: ");
        while (!minHeap.isEmpty())
            System.out.print(minHeap.poll() + " ");   // 1 2 5 8 9
        System.out.println();

        // Max-heap using reverseOrder
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Comparator.reverseOrder());
        maxHeap.addAll(List.of(5, 2, 8, 1, 9));
        System.out.print("Max-heap poll order: ");
        while (!maxHeap.isEmpty())
            System.out.print(maxHeap.poll() + " ");   // 9 8 5 2 1
        System.out.println();
    }
}
