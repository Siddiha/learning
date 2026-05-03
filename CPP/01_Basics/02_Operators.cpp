// ─────────────────────────────────────────
//  OPERATORS
// ─────────────────────────────────────────

#include <iostream>
#include <cmath>
using namespace std;

int main() {

    // ── Arithmetic ────────────────────────────
    cout << 10 + 3  << endl;   // 13
    cout << 10 - 3  << endl;   // 7
    cout << 10 * 3  << endl;   // 30
    cout << 10 / 3  << endl;   // 3   — integer division (truncates!)
    cout << 10.0/3  << endl;   // 3.333... — float division
    cout << 10 % 3  << endl;   // 1   — modulus (integers only)
    cout << pow(2,10) << endl; // 1024 (from <cmath>)

    // ── Increment / Decrement ─────────────────
    int x = 5;
    cout << x++ << endl;  // 5 — post: use THEN increment
    cout << x   << endl;  // 6
    cout << ++x << endl;  // 7 — pre: increment THEN use
    cout << x-- << endl;  // 7 — post-decrement
    cout << --x << endl;  // 5 — pre-decrement

    // ── Assignment shortcuts ──────────────────
    int a = 10;
    a += 5;    // 15
    a -= 3;    // 12
    a *= 2;    // 24
    a /= 4;    // 6
    a %= 4;    // 2
    cout << a << endl;

    // ── Comparison ────────────────────────────
    cout << (5 == 5) << endl;  // 1 (true)
    cout << (5 != 3) << endl;  // 1 (true)
    cout << (5 > 3)  << endl;  // 1
    cout << (5 < 3)  << endl;  // 0 (false)
    cout << (5 >= 5) << endl;  // 1
    cout << (5 <= 4) << endl;  // 0

    // print true/false instead of 1/0
    cout << boolalpha;
    cout << (5 == 5) << endl;  // true

    // ── Logical ───────────────────────────────
    cout << (true && false) << endl;  // false
    cout << (true || false) << endl;  // true
    cout << (!true)         << endl;  // false

    // Short-circuit
    int n = 0;
    cout << (n != 0 && 10/n > 1) << endl;  // false — no division by zero!

    // ── Bitwise ───────────────────────────────
    cout << (0b1010 & 0b1100) << endl;  // 8  (AND)
    cout << (0b1010 | 0b1100) << endl;  // 14 (OR)
    cout << (0b1010 ^ 0b1100) << endl;  // 6  (XOR)
    cout << (~0b1010)          << endl;  // -11 (NOT — flips all bits)
    cout << (1 << 3)           << endl;  // 8  (left shift)
    cout << (8 >> 2)           << endl;  // 2  (right shift)

    // ── Ternary operator ──────────────────────
    int age = 20;
    string status = age >= 18 ? "Adult" : "Minor";
    cout << status << endl;

    // ── sizeof operator ───────────────────────
    cout << sizeof(int)    << " bytes" << endl;
    cout << sizeof(double) << " bytes" << endl;
    cout << sizeof(a)      << " bytes" << endl;

    // ── Pointer operators ─────────────────────
    int val = 42;
    int* ptr = &val;   // & = address-of
    cout << ptr   << endl;  // memory address
    cout << *ptr  << endl;  // 42 — * = dereference (value at address)

    // ── Math functions (from <cmath>) ─────────
    cout << abs(-5)      << endl;   // 5
    cout << fabs(-3.14)  << endl;   // 3.14 (float abs)
    cout << sqrt(25.0)   << endl;   // 5
    cout << pow(3, 4)    << endl;   // 81
    cout << ceil(4.2)    << endl;   // 5
    cout << floor(4.8)   << endl;   // 4
    cout << round(4.5)   << endl;   // 5
    cout << log(M_E)     << endl;   // 1 (natural log)
    cout << log10(1000)  << endl;   // 3
    cout << sin(M_PI/2)  << endl;   // 1
    cout << max(3, 7)    << endl;   // 7
    cout << min(3, 7)    << endl;   // 3

    // ── Comma operator (rare, but exists) ─────
    int b = (1, 2, 3);  // evaluates all, returns last
    cout << b << endl;  // 3

    return 0;
}
