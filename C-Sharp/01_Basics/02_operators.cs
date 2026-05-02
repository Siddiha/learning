// ─────────────────────────────────────────
//  OPERATORS
// ─────────────────────────────────────────

using System;

class Operators
{
    static void Main()
    {
        // ── Arithmetic ────────────────────────────
        Console.WriteLine(10 + 3);    // 13
        Console.WriteLine(10 - 3);    // 7
        Console.WriteLine(10 * 3);    // 30
        Console.WriteLine(10 / 3);    // 3   — integer division!
        Console.WriteLine(10.0 / 3);  // 3.333... — float division
        Console.WriteLine(10 % 3);    // 1   — modulus (remainder)

        // ── Increment / Decrement ─────────────────
        int x = 5;
        Console.WriteLine(x++);   // 5 — post-increment: use THEN increment
        Console.WriteLine(x);     // 6
        Console.WriteLine(++x);   // 7 — pre-increment: increment THEN use
        Console.WriteLine(x--);   // 7 — post-decrement
        Console.WriteLine(--x);   // 5 — pre-decrement

        // ── Comparison ────────────────────────────
        Console.WriteLine(5 == 5);   // True
        Console.WriteLine(5 != 3);   // True
        Console.WriteLine(5 > 3);    // True
        Console.WriteLine(5 < 3);    // False
        Console.WriteLine(5 >= 5);   // True
        Console.WriteLine(5 <= 4);   // False

        // ── Logical ───────────────────────────────
        Console.WriteLine(true && false);   // False  (AND)
        Console.WriteLine(true || false);   // True   (OR)
        Console.WriteLine(!true);           // False  (NOT)

        // Short-circuit: second part skipped if result is determined
        int n = 0;
        Console.WriteLine(n != 0 && 10 / n > 1);  // False — no DivideByZero!

        // ── Assignment shortcuts ──────────────────
        int a = 10;
        a += 5;    // a = 15
        a -= 3;    // a = 12
        a *= 2;    // a = 24
        a /= 4;    // a = 6
        a %= 4;    // a = 2
        Console.WriteLine(a);

        // ── Bitwise ───────────────────────────────
        Console.WriteLine(0b1010 & 0b1100);   // 8  (AND)
        Console.WriteLine(0b1010 | 0b1100);   // 14 (OR)
        Console.WriteLine(0b1010 ^ 0b1100);   // 6  (XOR)
        Console.WriteLine(~0b1010);            // -11 (NOT)
        Console.WriteLine(1 << 3);             // 8  (left shift)
        Console.WriteLine(8 >> 2);             // 2  (right shift)

        // ── Ternary operator ──────────────────────
        int age = 20;
        string status = age >= 18 ? "Adult" : "Minor";
        Console.WriteLine(status);   // Adult

        // nested ternary (keep simple)
        int score = 75;
        string grade = score >= 90 ? "A" : score >= 75 ? "B" : score >= 60 ? "C" : "F";
        Console.WriteLine(grade);    // B

        // ── Null-coalescing (??) ──────────────────
        string? name = null;
        string display = name ?? "Anonymous";
        Console.WriteLine(display);   // Anonymous

        // Null-coalescing assignment (??=)
        string? config = null;
        config ??= "default";
        Console.WriteLine(config);    // default

        // ── Null-conditional (?.) ─────────────────
        string? s = null;
        int? length = s?.Length;   // null instead of NullReferenceException
        Console.WriteLine(length ?? -1);   // -1

        string text = "hello";
        Console.WriteLine(text?.ToUpper());   // HELLO
    }
}
