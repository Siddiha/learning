// ─────────────────────────────────────────
//  FUNCTIONS
// ─────────────────────────────────────────

#include <iostream>
#include <string>
#include <vector>
#include <functional>   // std::function
using namespace std;

// ── Basic function ────────────────────────
string greet(string name) {
    return "Hello, " + name + "!";
}

// ── void — no return ──────────────────────
void printLine(string text) {
    cout << text << endl;
}

// ── Default parameters ────────────────────
string greet2(string name, string greeting = "Hello") {
    return greeting + ", " + name + "!";
}

// ── Pass by value (copy) ──────────────────
void doubleVal(int x) {
    x *= 2;   // local copy — original unchanged
}

// ── Pass by reference — modifies original ─
void doubleRef(int& x) {
    x *= 2;
}

// ── Pass by const reference — read-only, no copy ─
void printVec(const vector<int>& v) {
    for (int n : v) cout << n << " ";
    cout << endl;
}

// ── Return by reference ───────────────────
int& getElement(vector<int>& v, int i) {
    return v[i];   // returns a reference to the element
}

// ── Function overloading ──────────────────
int add(int a, int b)          { return a + b; }
double add(double a, double b) { return a + b; }
string add(string a, string b) { return a + b; }

// ── Variadic template (variable args, C++11) ─
template<typename T>
T sum(T val) { return val; }

template<typename T, typename... Args>
T sum(T first, Args... rest) { return first + sum(rest...); }

// ── Recursion ─────────────────────────────
long long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// ── Template function ─────────────────────
template<typename T>
T maxOf(T a, T b) {
    return a > b ? a : b;
}

template<typename T>
void printArray(const T* arr, int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// ── Function pointer ──────────────────────
int applyOp(int a, int b, int (*op)(int, int)) {
    return op(a, b);
}
int multiply(int a, int b) { return a * b; }

// ── Forward declaration ───────────────────
void helperFunc();   // declared before main, defined after

int main() {

    // Basic calls
    cout << greet("Alice") << endl;
    printLine("I have no return");

    // Default params
    cout << greet2("Bob")         << endl;   // Hello, Bob!
    cout << greet2("Bob", "Hey")  << endl;   // Hey, Bob!

    // Pass by value vs reference
    int a = 10;
    doubleVal(a);
    cout << a << endl;   // 10 — unchanged

    doubleRef(a);
    cout << a << endl;   // 20 — changed!

    // Const reference (efficient for large objects)
    vector<int> data = {1, 2, 3, 4, 5};
    printVec(data);

    // Return by reference
    getElement(data, 2) = 99;   // modifies data[2]!
    printVec(data);

    // Overloading
    cout << add(2, 3)           << endl;   // 5 (int)
    cout << add(2.5, 3.5)       << endl;   // 6.0 (double)
    cout << add("Hello", " C++") << endl;  // Hello C++

    // Variadic sum
    cout << sum(1, 2, 3, 4, 5)       << endl;   // 15
    cout << sum(1.1, 2.2, 3.3)       << endl;   // 6.6

    // Recursion
    cout << factorial(5)  << endl;   // 120
    cout << factorial(10) << endl;   // 3628800

    for (int i = 0; i < 8; i++)
        cout << fibonacci(i) << " ";   // 0 1 1 2 3 5 8 13
    cout << endl;

    // Templates
    cout << maxOf(3, 7)           << endl;   // 7
    cout << maxOf(3.5, 2.1)       << endl;   // 3.5
    cout << maxOf(string("b"), string("a")) << endl;  // b

    int arr[] = {1, 2, 3, 4, 5};
    printArray(arr, 5);

    // Function pointers
    cout << applyOp(3, 4, multiply) << endl;   // 12
    cout << applyOp(3, 4, [](int a, int b) { return a + b; }) << endl;   // 7

    // ── Lambda functions ──────────────────────
    auto square = [](int x) { return x * x; };
    cout << square(5) << endl;   // 25

    // Capture by value [=]
    int base = 10;
    auto addBase = [base](int x) { return x + base; };  // captures base by value
    cout << addBase(5) << endl;   // 15

    // Capture by reference [&]
    int counter = 0;
    auto increment = [&counter]() { counter++; };
    increment(); increment(); increment();
    cout << counter << endl;   // 3

    // Capture all by value [=]
    auto all = [=](int x) { return x + base + counter; };
    cout << all(5) << endl;

    // Mutable lambda (modify captured value copy)
    int n = 0;
    auto mutLambda = [n]() mutable { n++; return n; };
    cout << mutLambda() << endl;   // 1
    cout << n << endl;             // 0 — original unchanged

    // Generic lambda (C++14)
    auto printAny = [](auto val) { cout << val << endl; };
    printAny(42);
    printAny("hello");
    printAny(3.14);

    // std::function — store any callable
    function<int(int, int)> op;
    op = [](int a, int b) { return a + b; };
    cout << op(3, 4) << endl;   // 7
    op = multiply;
    cout << op(3, 4) << endl;   // 12

    helperFunc();

    return 0;
}

void helperFunc() {
    cout << "Helper function called!" << endl;
}
