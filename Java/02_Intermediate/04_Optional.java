// ─────────────────────────────────────────
//  OPTIONAL<T>
// ─────────────────────────────────────────
// A container that may or may not hold a value.
// Forces you to handle the "no value" case explicitly — avoids NullPointerException.
// Think of it as a box that's either empty or has one item inside.

import java.util.*;
import java.util.stream.*;

public class OptionalDemo {
    public static void main(String[] args) {

        // ── Creating Optionals ────────────────────
        Optional<String> withValue = Optional.of("hello");       // non-null only
        Optional<String> empty     = Optional.empty();
        Optional<String> nullable  = Optional.ofNullable(null);  // null → empty

        // Optional.of(null) → NullPointerException — use ofNullable for unknown values

        // ── Check if present ──────────────────────
        System.out.println(withValue.isPresent());  // true
        System.out.println(empty.isPresent());       // false
        System.out.println(empty.isEmpty());         // true (Java 11+)

        // ── Get value ─────────────────────────────
        System.out.println(withValue.get());   // hello
        // empty.get()  → NoSuchElementException — always check first!

        // ── Safe retrieval ────────────────────────
        System.out.println(empty.orElse("default"));             // default
        System.out.println(empty.orElseGet(() -> "computed"));   // computed (lazy)
        System.out.println(withValue.orElse("default"));         // hello

        // orElseThrow — throw if empty
        try {
            empty.orElseThrow(() -> new IllegalStateException("No value!"));
        } catch (IllegalStateException e) {
            System.out.println(e.getMessage());
        }

        // ── ifPresent — run code only if value exists ─
        withValue.ifPresent(v -> System.out.println("Value: " + v));
        empty.ifPresent(v -> System.out.println("This won't print"));

        // ifPresentOrElse (Java 9+)
        withValue.ifPresentOrElse(
            v -> System.out.println("Got: " + v),
            () -> System.out.println("Was empty")
        );
        empty.ifPresentOrElse(
            v -> System.out.println("Got: " + v),
            () -> System.out.println("Was empty")
        );

        // ── map — transform the value if present ──
        Optional<Integer> length = withValue.map(String::length);
        System.out.println(length);   // Optional[5]

        Optional<Integer> emptyLen = empty.map(String::length);
        System.out.println(emptyLen); // Optional.empty

        // ── flatMap — for methods that also return Optional ─
        Optional<String> name = Optional.of("  Alice  ");

        Optional<String> trimmed = name.flatMap(n -> {
            String t = n.strip();
            return t.isEmpty() ? Optional.empty() : Optional.of(t);
        });
        System.out.println(trimmed);   // Optional[Alice]

        // ── filter — keep value only if condition is true ─
        Optional<Integer> number = Optional.of(42);
        Optional<Integer> evenNum = number.filter(n -> n % 2 == 0);
        Optional<Integer> oddNum  = number.filter(n -> n % 2 != 0);
        System.out.println(evenNum);   // Optional[42]
        System.out.println(oddNum);    // Optional.empty

        // ── or — provide alternative Optional (Java 9+) ─
        Optional<String> result = empty.or(() -> Optional.of("fallback"));
        System.out.println(result);    // Optional[fallback]

        // ── stream — treat Optional as 0 or 1 element stream ─
        long count = withValue.stream().count();  // 1
        long countE = empty.stream().count();      // 0
        System.out.println(count + " " + countE);

        // ── Real-world patterns ───────────────────

        // 1. Repository method that may not find a record
        record User(String name, String email) {}

        Map<Integer, User> db = Map.of(
            1, new User("Alice", "alice@example.com"),
            2, new User("Bob", null)
        );

        Optional<User> findById(int id) { return Optional.ofNullable(db.get(id)); }

        // Using the result
        findById(1)
            .map(User::email)
            .filter(e -> e != null && e.contains("@"))
            .ifPresentOrElse(
                e -> System.out.println("Valid email: " + e),
                () -> System.out.println("No valid email")
            );

        findById(99)   // not in db
            .ifPresentOrElse(
                u -> System.out.println("Found: " + u.name()),
                () -> System.out.println("User not found")
            );

        // 2. Chain of optional lookups (avoid null checks)
        Optional<String> email = findById(1)
            .map(User::email);
        String display = email.orElse("no-email@unknown.com");
        System.out.println(display);

        // 3. Collecting present optionals from a stream
        List<Optional<String>> optionals = List.of(
            Optional.of("a"),
            Optional.empty(),
            Optional.of("b"),
            Optional.empty(),
            Optional.of("c")
        );

        List<String> presentValues = optionals.stream()
            .flatMap(Optional::stream)   // unwrap — keeps only present values
            .collect(Collectors.toList());
        System.out.println(presentValues);   // [a, b, c]
    }
}
