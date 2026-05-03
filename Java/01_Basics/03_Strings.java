// ─────────────────────────────────────────
//  STRINGS
// ─────────────────────────────────────────

public class Strings {
    public static void main(String[] args) {

        String s = "Hello, World!";

        // ── Basic ─────────────────────────────────
        System.out.println(s.length());          // 13  (method, not .Length)
        System.out.println(s.charAt(0));         // H
        System.out.println(s.charAt(s.length() - 1)); // !

        // ── Substrings ────────────────────────────
        System.out.println(s.substring(7));      // World!
        System.out.println(s.substring(7, 12));  // World  (end is exclusive)

        // ── Search ────────────────────────────────
        System.out.println(s.indexOf("World"));     // 7
        System.out.println(s.lastIndexOf("l"));     // 10
        System.out.println(s.contains("World"));    // true
        System.out.println(s.startsWith("Hello"));  // true
        System.out.println(s.endsWith("!"));        // true

        // ── Transform ─────────────────────────────
        System.out.println(s.toUpperCase());                   // HELLO, WORLD!
        System.out.println(s.toLowerCase());                   // hello, world!
        System.out.println("  hello  ".trim());                // hello
        System.out.println("  hello  ".strip());               // hello (Unicode-aware)
        System.out.println(s.replace("World", "Java"));        // Hello, Java!
        System.out.println(s.replaceAll("[aeiou]", "*"));      // H*ll*, W*rld! (regex)

        // ── Compare ───────────────────────────────
        String a = "hello";
        String b = "HELLO";
        System.out.println(a.equals(b));                       // false
        System.out.println(a.equalsIgnoreCase(b));             // true
        System.out.println(a.compareTo(b));                    // positive (a > b)

        // ── Split & Join ──────────────────────────
        String csv = "apple,banana,cherry";
        String[] parts = csv.split(",");
        for (String part : parts)
            System.out.println(part);

        // Split by regex
        String[] words = "one  two   three".split("\\s+");    // one or more spaces
        System.out.println(words.length);  // 3

        String joined = String.join(" - ", "a", "b", "c");    // a - b - c
        String joined2 = String.join(", ", parts);             // apple, banana, cherry
        System.out.println(joined);
        System.out.println(joined2);

        // ── Check content ─────────────────────────
        System.out.println("".isEmpty());        // true
        System.out.println("  ".isBlank());      // true (Java 11+)
        System.out.println("hello".isBlank());   // false

        // ── String.format ─────────────────────────
        String name = "Alice";
        int age = 25;
        String msg = String.format("Name: %s, Age: %d", name, age);
        System.out.println(msg);
        System.out.println(String.format("Pi: %.3f", Math.PI));
        System.out.println(String.format("Hex: %X", 255));

        // ── Formatted (Java 15+) — cleaner alias ──
        String formatted = "Name: %s, Age: %d".formatted(name, age);
        System.out.println(formatted);

        // ── char array ↔ String ───────────────────
        char[] chars = s.toCharArray();
        System.out.println(chars[0]);   // H

        String fromChars = new String(chars);
        System.out.println(fromChars);

        // ── Text Block (Java 15+) — multiline ─────
        String json = """
                {
                    "name": "Alice",
                    "age": 25
                }
                """;
        System.out.println(json);

        // ── StringBuilder — efficient concatenation ─
        // String is immutable — each + creates a new object!
        // Use StringBuilder when building strings in loops

        StringBuilder sb = new StringBuilder();
        sb.append("Hello");
        sb.append(", ");
        sb.append("World");
        sb.append("!");
        sb.insert(0, ">>> ");       // insert at index
        sb.replace(4, 9, "Bye");    // replace range
        sb.reverse();               // reverse
        sb.delete(0, 3);            // delete range

        System.out.println(sb.toString());
        System.out.println(sb.length());

        // StringBuilder in loop — much faster than String +
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < 5; i++) {
            result.append(i);
            if (i < 4) result.append(", ");
        }
        System.out.println(result);   // 0, 1, 2, 3, 4

        // ── Common String methods cheatsheet ──────
        // length()           → number of characters
        // charAt(i)          → char at index i
        // substring(a, b)    → from a (inclusive) to b (exclusive)
        // indexOf(str)       → first occurrence index, -1 if not found
        // contains(str)      → true/false
        // startsWith/endsWith → true/false
        // equals/equalsIgnoreCase → compare content
        // toUpperCase/toLowerCase
        // trim/strip         → remove whitespace
        // replace(old, new)  → replace all occurrences
        // split(regex)       → String array
        // String.join(sep, ...)
        // isEmpty/isBlank    → check empty
        // toCharArray()      → char[]
    }
}
