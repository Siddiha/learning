// ─────────────────────────────────────────
//  STREAMS API
// ─────────────────────────────────────────
// A stream is a sequence of elements that can be processed with
// operations like filter, map, reduce — without modifying the source.
// Streams are lazy: intermediate ops run only when a terminal op is called.

import java.util.*;
import java.util.stream.*;

public class StreamsAPI {
    public static void main(String[] args) {

        List<Integer> nums = List.of(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

        // ── Creating streams ──────────────────────
        Stream<String> fromList = List.of("a", "b", "c").stream();
        Stream<Integer> fromArray = Arrays.stream(new Integer[]{1, 2, 3});
        Stream<String> ofValues = Stream.of("x", "y", "z");
        Stream<Integer> generated = Stream.generate(() -> 0).limit(5);  // infinite
        Stream<Integer> iterated = Stream.iterate(0, n -> n + 2).limit(5); // 0,2,4,6,8

        IntStream range = IntStream.range(1, 6);       // 1 to 5 (exclusive end)
        IntStream rangeClosed = IntStream.rangeClosed(1, 5); // 1 to 5 (inclusive)

        // ── INTERMEDIATE OPERATIONS (lazy, return a Stream) ──

        // filter — keep elements matching condition
        List<Integer> evens = nums.stream()
            .filter(n -> n % 2 == 0)
            .collect(Collectors.toList());
        System.out.println(evens);   // [2, 4, 6, 8, 10]

        // map — transform each element
        List<Integer> squares = nums.stream()
            .map(n -> n * n)
            .collect(Collectors.toList());
        System.out.println(squares);

        // map to a different type
        List<String> words = List.of("hello", "world", "java");
        List<String> upper = words.stream()
            .map(String::toUpperCase)
            .collect(Collectors.toList());
        System.out.println(upper);

        // flatMap — flatten nested collections
        List<List<Integer>> nested = List.of(List.of(1, 2), List.of(3, 4), List.of(5));
        List<Integer> flat = nested.stream()
            .flatMap(Collection::stream)
            .collect(Collectors.toList());
        System.out.println(flat);   // [1, 2, 3, 4, 5]

        // sorted — natural or custom order
        List<Integer> sorted = List.of(3, 1, 4, 1, 5, 9).stream()
            .sorted()
            .collect(Collectors.toList());
        System.out.println(sorted);

        List<String> sortedByLen = words.stream()
            .sorted(Comparator.comparingInt(String::length))
            .collect(Collectors.toList());
        System.out.println(sortedByLen);

        // distinct — remove duplicates
        List<Integer> unique = List.of(1, 2, 2, 3, 3, 3).stream()
            .distinct()
            .collect(Collectors.toList());
        System.out.println(unique);   // [1, 2, 3]

        // limit / skip
        List<Integer> first3 = nums.stream().limit(3).collect(Collectors.toList());
        List<Integer> skip3  = nums.stream().skip(3).collect(Collectors.toList());
        System.out.println(first3);   // [1, 2, 3]
        System.out.println(skip3);    // [4, 5, 6, 7, 8, 9, 10]

        // peek — debug/side effects without breaking chain
        List<Integer> result = nums.stream()
            .filter(n -> n % 2 == 0)
            .peek(n -> System.out.print("after filter: " + n + " "))
            .map(n -> n * 10)
            .collect(Collectors.toList());
        System.out.println("\n" + result);

        // ── TERMINAL OPERATIONS (trigger execution) ──

        // forEach
        nums.stream().forEach(n -> System.out.print(n + " "));
        System.out.println();

        // collect — gather into a collection
        List<Integer> list = nums.stream().collect(Collectors.toList());
        Set<Integer> set   = nums.stream().collect(Collectors.toSet());
        String joined = words.stream().collect(Collectors.joining(", ", "[", "]"));
        System.out.println(joined);   // [hello, world, java]

        // count
        long count = nums.stream().filter(n -> n > 5).count();
        System.out.println(count);   // 5

        // min / max
        Optional<Integer> min = nums.stream().min(Integer::compareTo);
        Optional<Integer> max = nums.stream().max(Integer::compareTo);
        System.out.println(min.get() + " " + max.get());   // 1 10

        // sum / average / statistics (IntStream)
        int sum = nums.stream().mapToInt(Integer::intValue).sum();
        double avg = nums.stream().mapToInt(Integer::intValue).average().orElse(0);
        System.out.println(sum + " " + avg);   // 55  5.5

        IntSummaryStatistics stats = nums.stream().mapToInt(Integer::intValue).summaryStatistics();
        System.out.println("Min=" + stats.getMin() + " Max=" + stats.getMax() +
                           " Sum=" + stats.getSum() + " Avg=" + stats.getAverage());

        // reduce — fold to a single value
        int product = nums.stream().reduce(1, (acc, n) -> acc * n);
        System.out.println(product);   // 3628800

        Optional<Integer> total = nums.stream().reduce((a, b) -> a + b);
        System.out.println(total.get());   // 55

        // anyMatch / allMatch / noneMatch
        System.out.println(nums.stream().anyMatch(n -> n > 9));   // true
        System.out.println(nums.stream().allMatch(n -> n > 0));   // true
        System.out.println(nums.stream().noneMatch(n -> n < 0));  // true

        // findFirst / findAny
        Optional<Integer> first = nums.stream().filter(n -> n > 5).findFirst();
        System.out.println(first.get());   // 6

        // toMap
        Map<String, Integer> wordLengths = words.stream()
            .collect(Collectors.toMap(w -> w, String::length));
        System.out.println(wordLengths);

        // groupingBy
        Map<Integer, List<String>> byLength = words.stream()
            .collect(Collectors.groupingBy(String::length));
        System.out.println(byLength);

        // partitioningBy — splits into true/false groups
        Map<Boolean, List<Integer>> evenOdd = nums.stream()
            .collect(Collectors.partitioningBy(n -> n % 2 == 0));
        System.out.println("Even: " + evenOdd.get(true));
        System.out.println("Odd:  " + evenOdd.get(false));

        // ── Chaining example — real use case ──────
        record Person(String name, int age, String city) {}

        List<Person> people = List.of(
            new Person("Alice", 30, "NYC"),
            new Person("Bob", 17, "LA"),
            new Person("Carol", 25, "NYC"),
            new Person("Dave", 15, "NYC"),
            new Person("Eve", 22, "LA")
        );

        // Get names of adults in NYC, sorted alphabetically
        List<String> nycAdults = people.stream()
            .filter(p -> p.city().equals("NYC"))
            .filter(p -> p.age() >= 18)
            .sorted(Comparator.comparing(Person::name))
            .map(Person::name)
            .collect(Collectors.toList());
        System.out.println(nycAdults);   // [Alice, Carol]

        // Average age by city
        Map<String, Double> avgAgeByCity = people.stream()
            .collect(Collectors.groupingBy(Person::city,
                     Collectors.averagingInt(Person::age)));
        System.out.println(avgAgeByCity);
    }
}
