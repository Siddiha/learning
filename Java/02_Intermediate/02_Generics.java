// ─────────────────────────────────────────
//  GENERICS
// ─────────────────────────────────────────
// Write code that works with any type while keeping type safety.
// Catches type errors at compile time, not runtime.

import java.util.*;
import java.util.function.*;

public class Generics {

    // ── Generic class ─────────────────────────
    static class Box<T> {
        private T value;

        public Box(T value)  { this.value = value; }
        public T get()       { return value; }
        public void set(T v) { this.value = v; }

        @Override
        public String toString() { return "Box[" + value + "]"; }
    }

    // ── Multiple type parameters ───────────────
    static class Pair<A, B> {
        private final A first;
        private final B second;

        public Pair(A first, B second) {
            this.first = first;
            this.second = second;
        }

        public A first()  { return first; }
        public B second() { return second; }

        @Override
        public String toString() { return "(" + first + ", " + second + ")"; }
    }

    // ── Generic method ────────────────────────
    static <T> void swap(T[] arr, int i, int j) {
        T temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    static <T extends Comparable<T>> T max(T a, T b) {
        return a.compareTo(b) >= 0 ? a : b;
    }

    static <T> List<T> repeat(T item, int times) {
        List<T> list = new ArrayList<>();
        for (int i = 0; i < times; i++) list.add(item);
        return list;
    }

    // ── Bounded type parameters ───────────────
    // <T extends Number> — T must be Number or a subclass
    static <T extends Number> double sum(List<T> list) {
        double total = 0;
        for (T item : list) total += item.doubleValue();
        return total;
    }

    // Multiple bounds — T must extend Comparable AND be Cloneable
    static <T extends Comparable<T> & Cloneable> T clampedMax(T a, T b) {
        return a.compareTo(b) >= 0 ? a : b;
    }

    // ── Generic stack implementation ──────────
    static class Stack<T> {
        private final List<T> items = new ArrayList<>();

        public void push(T item) { items.add(item); }

        public T pop() {
            if (isEmpty()) throw new NoSuchElementException("Stack is empty");
            return items.remove(items.size() - 1);
        }

        public T peek() {
            if (isEmpty()) throw new NoSuchElementException("Stack is empty");
            return items.get(items.size() - 1);
        }

        public boolean isEmpty() { return items.isEmpty(); }
        public int size()        { return items.size(); }

        @Override
        public String toString() { return items.toString(); }
    }

    // ── Generic Result type (like Optional but with error) ──
    static class Result<T> {
        private final T value;
        private final String error;

        private Result(T value, String error) {
            this.value = value;
            this.error = error;
        }

        static <T> Result<T> success(T value) { return new Result<>(value, null); }
        static <T> Result<T> failure(String error) { return new Result<>(null, error); }

        public boolean isSuccess() { return error == null; }
        public T getValue()        { return value; }
        public String getError()   { return error; }

        @Override
        public String toString() {
            return isSuccess() ? "Success(" + value + ")" : "Failure(" + error + ")";
        }
    }

    // ── Wildcards ─────────────────────────────
    // ? — unknown type
    // ? extends T — T or any subclass (upper bounded — read only)
    // ? super T   — T or any superclass (lower bounded — write only)

    static double sumList(List<? extends Number> list) {
        // ? extends Number — accepts List<Integer>, List<Double>, etc.
        double total = 0;
        for (Number n : list) total += n.doubleValue();
        return total;
    }

    static void addNumbers(List<? super Integer> list) {
        // ? super Integer — accepts List<Integer>, List<Number>, List<Object>
        list.add(1);
        list.add(2);
        list.add(3);
    }

    public static void main(String[] args) {

        // Generic class
        Box<String> strBox = new Box<>("hello");
        Box<Integer> intBox = new Box<>(42);
        System.out.println(strBox);   // Box[hello]
        System.out.println(intBox);   // Box[42]
        strBox.set("world");
        System.out.println(strBox.get());

        // Multiple type params
        Pair<String, Integer> p = new Pair<>("Alice", 25);
        System.out.println(p);           // (Alice, 25)
        System.out.println(p.first());   // Alice
        System.out.println(p.second());  // 25

        // Generic methods
        Integer[] arr = {1, 2, 3, 4, 5};
        swap(arr, 0, 4);
        System.out.println(Arrays.toString(arr));   // [5, 2, 3, 4, 1]

        System.out.println(max(10, 20));      // 20
        System.out.println(max("apple", "mango")); // mango

        System.out.println(repeat("ha", 3));   // [ha, ha, ha]

        // Bounded generics
        System.out.println(sum(List.of(1, 2, 3)));       // 6.0
        System.out.println(sum(List.of(1.5, 2.5, 3.0))); // 7.0

        // Generic stack
        Stack<String> stack = new Stack<>();
        stack.push("first");
        stack.push("second");
        stack.push("third");
        System.out.println(stack.peek());    // third
        System.out.println(stack.pop());     // third
        System.out.println(stack.size());    // 2

        // Result type
        Result<Integer> ok = Result.success(42);
        Result<Integer> err = Result.failure("Division by zero");
        System.out.println(ok);    // Success(42)
        System.out.println(err);   // Failure(Division by zero)

        if (ok.isSuccess())
            System.out.println("Value: " + ok.getValue());

        // Wildcards
        List<Integer> ints = List.of(1, 2, 3);
        List<Double>  dbls = List.of(1.5, 2.5, 3.0);
        System.out.println(sumList(ints));   // 6.0
        System.out.println(sumList(dbls));   // 7.0

        List<Number> numbers = new ArrayList<>();
        addNumbers(numbers);
        System.out.println(numbers);   // [1, 2, 3]
    }
}
