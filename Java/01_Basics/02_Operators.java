// ─────────────────────────────────────────
//  OPERATORS
// ─────────────────────────────────────────

public class Operators {
    public static void main(String[] args) {

        // ── Arithmetic ────────────────────────────
        System.out.println(10 + 3);    // 13
        System.out.println(10 - 3);    // 7
        System.out.println(10 * 3);    // 30
        System.out.println(10 / 3);    // 3   — integer division (truncates!)
        System.out.println(10.0 / 3);  // 3.333... — float division
        System.out.println(10 % 3);    // 1   — modulus (remainder)

        // ── Increment / Decrement ─────────────────
        int x = 5;
        System.out.println(x++);  // 5 — post-increment: use THEN increment
        System.out.println(x);    // 6
        System.out.println(++x);  // 7 — pre-increment: increment THEN use
        System.out.println(x--);  // 7 — post-decrement
        System.out.println(--x);  // 5 — pre-decrement

        // ── Assignment shortcuts ──────────────────
        int a = 10;
        a += 5;   // a = 15
        a -= 3;   // a = 12
        a *= 2;   // a = 24
        a /= 4;   // a = 6
        a %= 4;   // a = 2
        System.out.println(a);

        // ── Comparison ────────────────────────────
        System.out.println(5 == 5);   // true
        System.out.println(5 != 3);   // true
        System.out.println(5 > 3);    // true
        System.out.println(5 < 3);    // false
        System.out.println(5 >= 5);   // true
        System.out.println(5 <= 4);   // false

        // WARNING: == on objects compares reference, not value!
        String s1 = new String("hello");
        String s2 = new String("hello");
        System.out.println(s1 == s2);          // false — different objects
        System.out.println(s1.equals(s2));     // true  — same content

        // String literals are interned, so == works (don't rely on this)
        String s3 = "hello";
        String s4 = "hello";
        System.out.println(s3 == s4);   // true (pooled), but use .equals()

        // ── Logical ───────────────────────────────
        System.out.println(true && false);   // false (AND)
        System.out.println(true || false);   // true  (OR)
        System.out.println(!true);           // false (NOT)

        // Short-circuit: right side not evaluated if result is known
        int n = 0;
        System.out.println(n != 0 && 10 / n > 1);  // false — no ArithmeticException!

        // ── Bitwise ───────────────────────────────
        System.out.println(0b1010 & 0b1100);   // 8  (AND)
        System.out.println(0b1010 | 0b1100);   // 14 (OR)
        System.out.println(0b1010 ^ 0b1100);   // 6  (XOR)
        System.out.println(~0b1010);            // -11 (NOT)
        System.out.println(1 << 3);             // 8  (left shift)
        System.out.println(8 >> 2);             // 2  (signed right shift)
        System.out.println(-1 >>> 1);           // unsigned right shift

        // ── Ternary operator ──────────────────────
        int age = 20;
        String status = age >= 18 ? "Adult" : "Minor";
        System.out.println(status);   // Adult

        // ── instanceof ────────────────────────────
        Object obj = "hello";
        System.out.println(obj instanceof String);   // true
        System.out.println(obj instanceof Integer);  // false

        // ── Math operations ───────────────────────
        System.out.println(Math.abs(-5));        // 5
        System.out.println(Math.max(10, 20));    // 20
        System.out.println(Math.min(10, 20));    // 10
        System.out.println(Math.pow(2, 10));     // 1024.0
        System.out.println(Math.sqrt(25));       // 5.0
        System.out.println(Math.floor(4.9));     // 4.0
        System.out.println(Math.ceil(4.1));      // 5.0
        System.out.println(Math.round(4.5));     // 5
        System.out.println(Math.PI);             // 3.14159...
        System.out.println(Math.random());       // 0.0 to 1.0
    }
}
