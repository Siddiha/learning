// ─────────────────────────────────────────
//  METHODS
// ─────────────────────────────────────────

import java.util.*;
import java.util.function.*;

public class Methods {

    // ── Basic method ──────────────────────────
    static String greet(String name) {
        return "Hello, " + name + "!";
    }

    // ── void — no return value ────────────────
    static void printLine(String text) {
        System.out.println(text);
    }

    // ── Return multiple values — use array, list, or record ─
    static int[] minMax(int[] nums) {
        int min = nums[0], max = nums[0];
        for (int n : nums) {
            if (n < min) min = n;
            if (n > max) max = n;
        }
        return new int[]{min, max};
    }

    // ── Varargs — variable number of arguments ─
    static int sum(int... numbers) {
        int total = 0;
        for (int n : numbers) total += n;
        return total;
    }

    // Can combine with regular params (varargs must be last)
    static String join(String sep, String... words) {
        return String.join(sep, words);
    }

    // ── Method overloading ────────────────────
    static int add(int a, int b)          { return a + b; }
    static double add(double a, double b) { return a + b; }
    static String add(String a, String b) { return a + b; }

    // ── Recursive methods ─────────────────────
    static long factorial(int n) {
        if (n <= 1) return 1;
        return n * factorial(n - 1);
    }

    static int fibonacci(int n) {
        if (n <= 1) return n;
        return fibonacci(n - 1) + fibonacci(n - 2);
    }

    // ── Generic method ────────────────────────
    static <T> void printArray(T[] arr) {
        System.out.print("[");
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i]);
            if (i < arr.length - 1) System.out.print(", ");
        }
        System.out.println("]");
    }

    static <T extends Comparable<T>> T findMax(T[] arr) {
        T max = arr[0];
        for (T item : arr)
            if (item.compareTo(max) > 0) max = item;
        return max;
    }

    public static void main(String[] args) {

        // Basic calls
        System.out.println(greet("Alice"));    // Hello, Alice!
        printLine("printed");

        // Multiple return
        int[] result = minMax(new int[]{3, 1, 7, 2, 9});
        System.out.println("min=" + result[0] + ", max=" + result[1]);

        // Varargs
        System.out.println(sum(1, 2, 3));          // 6
        System.out.println(sum(1, 2, 3, 4, 5));    // 15
        System.out.println(join("-", "a", "b", "c")); // a-b-c

        // Overloading
        System.out.println(add(2, 3));             // 5 (int)
        System.out.println(add(2.5, 3.5));         // 6.0 (double)
        System.out.println(add("Hello", " Java")); // Hello Java

        // Recursion
        System.out.println(factorial(5));  // 120
        System.out.println(factorial(10)); // 3628800

        for (int i = 0; i < 8; i++)
            System.out.print(fibonacci(i) + " ");  // 0 1 1 2 3 5 8 13
        System.out.println();

        // Generics
        Integer[] ints = {3, 1, 7, 2};
        String[] strs = {"banana", "apple", "cherry"};
        printArray(ints);
        printArray(strs);
        System.out.println(findMax(ints));   // 7
        System.out.println(findMax(strs));   // cherry

        // ── Functional interfaces & lambdas ───────
        // Function<T, R> — takes T, returns R
        Function<String, Integer> strLen = s -> s.length();
        System.out.println(strLen.apply("hello"));   // 5

        // BiFunction<T, U, R> — takes T and U, returns R
        BiFunction<Integer, Integer, Integer> multiply = (a, b) -> a * b;
        System.out.println(multiply.apply(3, 4));    // 12

        // Consumer<T> — takes T, returns void
        Consumer<String> shout = s -> System.out.println(s.toUpperCase());
        shout.accept("hello");   // HELLO

        // Supplier<T> — takes nothing, returns T
        Supplier<String> greeting = () -> "Hello, World!";
        System.out.println(greeting.get());

        // Predicate<T> — takes T, returns boolean
        Predicate<Integer> isEven = n -> n % 2 == 0;
        System.out.println(isEven.test(4));   // true
        System.out.println(isEven.test(7));   // false

        // Predicate chaining
        Predicate<Integer> isPositive = n -> n > 0;
        Predicate<Integer> isPositiveEven = isEven.and(isPositive);
        System.out.println(isPositiveEven.test(4));   // true
        System.out.println(isPositiveEven.test(-4));  // false

        // ── Method references ──────────────────────
        Function<String, String> upper = String::toUpperCase;  // instance method
        System.out.println(upper.apply("hello"));   // HELLO

        Consumer<String> printer = System.out::println;        // static method ref
        printer.accept("Printed via method ref");

        List<String> words = List.of("banana", "apple", "cherry");
        words.stream()
             .map(String::toUpperCase)
             .forEach(System.out::println);
    }
}
