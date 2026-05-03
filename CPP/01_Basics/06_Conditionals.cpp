// ─────────────────────────────────────────
//  CONDITIONALS
// ─────────────────────────────────────────

#include <iostream>
#include <string>
using namespace std;

int main() {

    int age = 20;

    // ── if / else if / else ───────────────────
    if (age < 13) {
        cout << "Child" << endl;
    } else if (age < 18) {
        cout << "Teenager" << endl;
    } else if (age < 60) {
        cout << "Adult" << endl;
    } else {
        cout << "Senior" << endl;
    }

    // ── Ternary operator ──────────────────────
    string status = age >= 18 ? "Adult" : "Minor";
    cout << status << endl;

    // Nested ternary
    int score = 75;
    string grade = score >= 90 ? "A"
                 : score >= 75 ? "B"
                 : score >= 60 ? "C"
                 : "F";
    cout << grade << endl;   // B

    // ── switch statement ──────────────────────
    int day = 3;
    switch (day) {
        case 1:
            cout << "Monday" << endl;
            break;
        case 2:
            cout << "Tuesday" << endl;
            break;
        case 3:
        case 4:                          // fall-through (multiple cases)
            cout << "Mid-week" << endl;
            break;
        case 5:
            cout << "Friday!" << endl;
            break;
        case 6:
        case 7:
            cout << "Weekend" << endl;
            break;
        default:
            cout << "Invalid" << endl;
    }

    // switch on char
    char choice = 'y';
    switch (choice) {
        case 'y':
        case 'Y':
            cout << "Yes!" << endl;
            break;
        case 'n':
        case 'N':
            cout << "No!" << endl;
            break;
        default:
            cout << "Unknown" << endl;
    }

    // ── if with initializer (C++17) ──────────
    // Declare and check in one statement
    if (int result = score - 50; result > 0) {
        cout << "Passed by " << result << " points" << endl;
    } else {
        cout << "Failed by " << -result << " points" << endl;
    }
    // 'result' is only in scope inside the if/else

    // ── switch with initializer (C++17) ───────
    switch (int val = score / 10; val) {
        case 10:
        case 9:  cout << "A" << endl; break;
        case 8:  cout << "B" << endl; break;
        case 7:  cout << "B" << endl; break;
        case 6:  cout << "C" << endl; break;
        default: cout << "F" << endl;
    }

    // ── Logical operators in conditions ───────
    int x = 15;
    if (x > 10 && x < 20)
        cout << "Between 10 and 20" << endl;

    if (x < 0 || x > 100)
        cout << "Out of range" << endl;
    else
        cout << "In range" << endl;

    // ── Null / pointer checks ─────────────────
    int* ptr = nullptr;
    if (ptr == nullptr)
        cout << "Pointer is null" << endl;

    if (!ptr)              // same as ptr == nullptr
        cout << "Also null" << endl;

    int val = 42;
    ptr = &val;
    if (ptr)               // non-null pointer is truthy
        cout << "Pointer has value: " << *ptr << endl;

    // ── Compile-time conditionals ─────────────
    // constexpr if (C++17) — branch evaluated at compile time
    auto checkType = [](auto value) {
        if constexpr (is_integral_v<decltype(value)>)
            cout << value << " is an integer type" << endl;
        else if constexpr (is_floating_point_v<decltype(value)>)
            cout << value << " is a floating point type" << endl;
        else
            cout << "Some other type" << endl;
    };

    checkType(42);      // integer
    checkType(3.14);    // floating point
    checkType("hi");    // some other type

    return 0;
}
