// ─────────────────────────────────────────
//  FUNCTIONAL INTERFACES & LAMBDAS (deep dive)
// ─────────────────────────────────────────
// A functional interface has exactly ONE abstract method.
// Lambdas are shorthand for implementing functional interfaces.
// @FunctionalInterface annotation enforces this contract.

import java.util.*;
import java.util.function.*;
import java.util.stream.*;

public class FunctionalInterfaces {

    // ── Custom functional interface ────────────
    @FunctionalInterface
    interface Transformer<T, R> {
        R transform(T input);

        // Can still have default/static methods — still functional
        default Transformer<T, String> andThenToString() {
            return input -> String.valueOf(this.transform(input));
        }
    }

    @FunctionalInterface
    interface Validator<T> {
        boolean validate(T value);

        default Validator<T> and(Validator<T> other) {
            return value -> this.validate(value) && other.validate(value);
        }

        default Validator<T> or(Validator<T> other) {
            return value -> this.validate(value) || other.validate(value);
        }

        default Validator<T> negate() {
            return value -> !this.validate(value);
        }
    }

    @FunctionalInterface
    interface TriFunction<A, B, C, R> {
        R apply(A a, B b, C c);
    }

    public static void main(String[] args) {

        // ── Built-in functional interfaces ────────

        // Function<T, R> — one input, one output
        Function<String, Integer> strToLen = String::length;
        Function<Integer, Integer> doubleIt = n -> n * 2;

        System.out.println(strToLen.apply("hello"));   // 5

        // compose: doubleIt(strToLen(x))
        Function<String, Integer> lenThenDouble = strToLen.andThen(doubleIt);
        System.out.println(lenThenDouble.apply("hello"));   // 10

        // andThen chains (left to right)
        Function<Integer, String> pipeline = doubleIt
            .andThen(n -> n + 1)
            .andThen(Object::toString);
        System.out.println(pipeline.apply(5));   // "11"

        // BiFunction<T, U, R>
        BiFunction<String, Integer, String> repeat = (s, n) -> s.repeat(n);
        System.out.println(repeat.apply("ab", 3));   // ababab

        // ── Predicate<T> ──────────────────────────
        Predicate<String> notEmpty = s -> !s.isEmpty();
        Predicate<String> isLong   = s -> s.length() > 5;
        Predicate<Integer> isEven  = n -> n % 2 == 0;
        Predicate<Integer> isPos   = n -> n > 0;

        System.out.println(notEmpty.test("hello"));       // true
        System.out.println(isLong.and(notEmpty).test("hi")); // false
        System.out.println(isEven.or(isPos).test(-3));       // false
        System.out.println(isEven.negate().test(4));         // false

        // Predicate.not() — wraps a method reference
        List<String> words = List.of("hello", "", "world", "  ", "java");
        List<String> nonEmpty = words.stream()
            .filter(Predicate.not(String::isBlank))
            .collect(Collectors.toList());
        System.out.println(nonEmpty);

        // ── Consumer<T> ───────────────────────────
        Consumer<String> print   = System.out::println;
        Consumer<String> shout   = s -> System.out.println(s.toUpperCase());
        Consumer<String> printAndShout = print.andThen(shout);  // chain consumers

        print.accept("hello");
        printAndShout.accept("world");

        BiConsumer<String, Integer> printWithIndex = (s, i) -> System.out.println(i + ": " + s);
        printWithIndex.accept("apple", 0);

        // ── Supplier<T> ───────────────────────────
        Supplier<List<String>> listFactory = ArrayList::new;
        List<String> list1 = listFactory.get();
        List<String> list2 = listFactory.get();   // new instance each time
        System.out.println(list1 == list2);        // false

        Supplier<Double> randomVal = Math::random;
        System.out.println(randomVal.get());

        // ── UnaryOperator<T> — same type in and out ─
        UnaryOperator<String> trim  = String::strip;
        UnaryOperator<String> upper = String::toUpperCase;
        UnaryOperator<String> clean = trim.andThen(upper);
        System.out.println(clean.apply("  hello world  "));   // HELLO WORLD

        // ── BinaryOperator<T> ─────────────────────
        BinaryOperator<Integer> add = Integer::sum;
        BinaryOperator<String> concat = (a, b) -> a + b;
        System.out.println(add.apply(3, 4));         // 7
        System.out.println(concat.apply("a", "b"));  // ab

        // ── Custom functional interfaces ──────────
        Transformer<String, Integer> lengthOf = String::length;
        System.out.println(lengthOf.transform("hello"));   // 5

        Validator<String> nonBlank = s -> !s.isBlank();
        Validator<String> maxLen   = s -> s.length() <= 10;
        Validator<String> nameRule = nonBlank.and(maxLen);

        System.out.println(nameRule.validate("Alice"));          // true
        System.out.println(nameRule.validate(""));               // false
        System.out.println(nameRule.validate("VeryLongNameXX")); // false

        TriFunction<Integer, Integer, Integer, Integer> clamp =
            (val, min, max) -> Math.max(min, Math.min(max, val));
        System.out.println(clamp.apply(15, 0, 10));  // 10
        System.out.println(clamp.apply(5, 0, 10));   // 5

        // ── Method references ──────────────────────
        // Type 1: Static method ref    — ClassName::staticMethod
        Function<String, Integer> parseInt = Integer::parseInt;
        System.out.println(parseInt.apply("42"));

        // Type 2: Instance method ref (on specific instance)
        String prefix = "Hello, ";
        Function<String, String> greet = prefix::concat;
        System.out.println(greet.apply("Alice"));   // Hello, Alice

        // Type 3: Instance method ref (on arbitrary instance of type)
        Function<String, String> toUpper = String::toUpperCase;
        Function<String, Integer> length  = String::length;

        // Type 4: Constructor ref
        Function<String, StringBuilder> sbFactory = StringBuilder::new;
        StringBuilder sb = sbFactory.apply("hello");
        System.out.println(sb);

        // ── Closures — capturing variables ────────
        int base = 10;   // must be effectively final
        Function<Integer, Integer> addBase = n -> n + base;
        System.out.println(addBase.apply(5));   // 15

        // ── Currying ──────────────────────────────
        // Transform a function that takes 2 args into a chain of 1-arg functions
        Function<Integer, Function<Integer, Integer>> curriedAdd = a -> b -> a + b;
        Function<Integer, Integer> add5 = curriedAdd.apply(5);
        System.out.println(add5.apply(3));    // 8
        System.out.println(add5.apply(10));   // 15
        System.out.println(curriedAdd.apply(2).apply(3));  // 5
    }
}
