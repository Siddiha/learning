// ─────────────────────────────────────────
//  OPERATORS
// ─────────────────────────────────────────

#include <stdio.h>
#include <math.h>    // pow, sqrt, fabs, ceil, floor, round, log, sin, M_PI

int main(void) {

    // ── Arithmetic ────────────────────────────
    printf("%d\n",  10 + 3);    // 13
    printf("%d\n",  10 - 3);    // 7
    printf("%d\n",  10 * 3);    // 30
    printf("%d\n",  10 / 3);    // 3   — integer division (truncates!)
    printf("%f\n",  10.0/3);    // 3.333... — float division
    printf("%d\n",  10 % 3);    // 1   — modulus (integers only)
    printf("%f\n",  pow(2,10)); // 1024 (from <math.h>)

    // ── Increment / Decrement ─────────────────
    int x = 5;
    printf("%d\n", x++);  // 5 — post: use THEN increment
    printf("%d\n", x);    // 6
    printf("%d\n", ++x);  // 7 — pre: increment THEN use
    printf("%d\n", x--);  // 7 — post-decrement
    printf("%d\n", --x);  // 5 — pre-decrement

    // ── Assignment shortcuts ──────────────────
    int a = 10;
    a += 5;   // 15
    a -= 3;   // 12
    a *= 2;   // 24
    a /= 4;   // 6
    a %= 4;   // 2
    printf("%d\n", a);

    // ── Comparison ────────────────────────────
    printf("%d\n", 5 == 5);  // 1 (true)
    printf("%d\n", 5 != 3);  // 1 (true)
    printf("%d\n", 5 > 3);   // 1
    printf("%d\n", 5 < 3);   // 0 (false)
    printf("%d\n", 5 >= 5);  // 1
    printf("%d\n", 5 <= 4);  // 0
    // C has no boolalpha — comparisons always print 0 or 1

    // ── Logical ───────────────────────────────
    printf("%d\n", 1 && 0);   // 0 (false)
    printf("%d\n", 1 || 0);   // 1 (true)
    printf("%d\n", !1);       // 0 (false)

    // Short-circuit
    int n = 0;
    printf("%d\n", n != 0 && 10/n > 1);  // 0 — no division by zero!

    // ── Bitwise ───────────────────────────────
    printf("%d\n", 0xA & 0xC);   // 8  (AND)
    printf("%d\n", 0xA | 0xC);   // 14 (OR)
    printf("%d\n", 0xA ^ 0xC);   // 6  (XOR)
    printf("%d\n", ~0xA);         // -11 (NOT — flips all bits)
    printf("%d\n", 1 << 3);       // 8  (left shift)
    printf("%d\n", 8 >> 2);       // 2  (right shift)

    // ── Ternary operator ──────────────────────
    int age = 20;
    const char* status = age >= 18 ? "Adult" : "Minor";
    printf("%s\n", status);

    // ── sizeof operator ───────────────────────
    printf("%zu bytes\n", sizeof(int));
    printf("%zu bytes\n", sizeof(double));
    printf("%zu bytes\n", sizeof(a));

    // ── Pointer operators ─────────────────────
    int val = 42;
    int* ptr = &val;   // & = address-of
    printf("%p\n",  (void*)ptr);   // memory address
    printf("%d\n",  *ptr);         // 42 — * = dereference

    // ── Math functions (from <math.h>) ────────
    printf("%d\n",   abs(-5));         // 5  (from <stdlib.h>)
    printf("%f\n",   fabs(-3.14));     // 3.14 (float abs)
    printf("%f\n",   sqrt(25.0));      // 5
    printf("%f\n",   pow(3, 4));       // 81
    printf("%f\n",   ceil(4.2));       // 5
    printf("%f\n",   floor(4.8));      // 4
    printf("%f\n",   round(4.5));      // 5
    printf("%f\n",   log(M_E));        // 1 (natural log)
    printf("%f\n",   log10(1000));     // 3
    printf("%f\n",   sin(M_PI / 2));   // 1

    // max/min — no built-in in C, use macros or ternary
    int p = 3, q = 7;
    int maximum = p > q ? p : q;
    int minimum = p < q ? p : q;
    printf("max: %d, min: %d\n", maximum, minimum);

    // ── Comma operator (rare, but valid C) ────
    int b = (1, 2, 3);   // evaluates all, returns last
    printf("%d\n", b);   // 3

    return 0;
}
