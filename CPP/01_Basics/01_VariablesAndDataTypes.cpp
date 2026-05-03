// ─────────────────────────────────────────
//  VARIABLES & DATA TYPES
// ─────────────────────────────────────────

#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

int main() {

    // ── Fundamental Types ─────────────────────
    int age = 25;
    long bigNum = 9000000L;          // 'L' suffix
    long long huge = 9000000000LL;   // 'LL' suffix
    float pi = 3.14f;                // 'f' suffix required
    double precise = 3.14159265358979;
    long double bigger = 3.14159265358979323846L;
    bool isStudent = true;           // true / false (lowercase)
    char grade = 'A';               // single character, single quotes
    unsigned int positive = 42;     // no negatives
    short small = 32000;

    cout << "int: "    << age      << endl;
    cout << "double: " << precise  << endl;
    cout << "char: "   << grade    << endl;
    cout << "bool: "   << isStudent << endl;   // prints 1 (true)
    cout << boolalpha  << isStudent << endl;   // prints true

    // ── string (from <string>) ────────────────
    string name = "Alice";
    string empty = "";
    cout << "Name: " << name << endl;

    // ── auto — type inference (C++11) ─────────
    auto city    = string("New York");  // string
    auto count   = 10;                  // int
    auto ratio   = 3.14;               // double
    auto letter  = 'Z';               // char

    cout << typeid(city).name()  << endl;  // implementation-defined
    cout << typeid(count).name() << endl;

    // ── const — cannot be modified ────────────
    const double PI = 3.14159;
    const int MAX_SIZE = 100;
    // PI = 3;   // error: assignment of read-only variable

    // ── constexpr — compile-time constant (C++11) ─
    constexpr int BUFFER = 1024;
    constexpr double TAX_RATE = 0.15;

    // ── Type sizes (platform dependent) ──────
    cout << "sizeof(int)    = " << sizeof(int)    << " bytes" << endl;
    cout << "sizeof(double) = " << sizeof(double) << " bytes" << endl;
    cout << "sizeof(char)   = " << sizeof(char)   << " bytes" << endl;
    cout << "sizeof(bool)   = " << sizeof(bool)   << " bytes" << endl;
    cout << "sizeof(long)   = " << sizeof(long)   << " bytes" << endl;

    // ── Numeric limits ────────────────────────
    #include <climits>
    // INT_MAX, INT_MIN, LONG_MAX, CHAR_MAX ...
    cout << "INT_MAX = " << INT_MAX << endl;   // 2147483647
    cout << "INT_MIN = " << INT_MIN << endl;   // -2147483648

    // ── Type casting ──────────────────────────
    // C-style cast (works but avoid)
    double d = 9.99;
    int fromDouble = (int)d;    // 9 — truncated
    cout << fromDouble << endl;

    // C++ style casts (preferred)
    int fromDouble2 = static_cast<int>(d);    // 9
    cout << fromDouble2 << endl;

    int i = 65;
    char ch = static_cast<char>(i);   // 'A'
    cout << ch << endl;

    // ── String to number & back ───────────────
    #include <string>
    string numStr = "42";
    int parsed    = stoi(numStr);     // string → int
    long parsedL  = stol("9000");    // string → long
    double parsedD = stod("3.14");   // string → double

    string fromInt = to_string(100);  // int → string
    string fromDbl = to_string(3.14); // double → string

    cout << parsed + 1  << endl;   // 43
    cout << fromInt     << endl;   // "100"

    // ── Multiple declarations ──────────────────
    int x = 1, y = 2, z = 3;
    cout << x << " " << y << " " << z << endl;

    // ── References ────────────────────────────
    int original = 10;
    int& ref = original;   // ref IS original — same memory
    ref = 20;
    cout << original << endl;   // 20 — original changed!

    // ── Pointers (basics) ─────────────────────
    int num = 42;
    int* ptr = &num;   // ptr holds the address of num
    cout << ptr   << endl;    // memory address
    cout << *ptr  << endl;    // 42 — dereference: value at address
    *ptr = 100;
    cout << num   << endl;    // 100 — num changed via pointer

    int* nullPtr = nullptr;   // use nullptr (not NULL or 0)

    // ── Output formatting ─────────────────────
    cout << fixed;
    cout.precision(4);
    cout << PI << endl;    // 3.1416

    printf("Name: %s, Age: %d\n", name.c_str(), age);
    printf("Pi: %.4f\n", PI);

    return 0;
}
