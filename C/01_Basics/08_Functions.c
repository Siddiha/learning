// ─────────────────────────────────────────
//  FUNCTIONS
// ─────────────────────────────────────────

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>   // variadic functions

// ── Basic function ────────────────────────
void greet(const char* name) {
    printf("Hello, %s!\n", name);
}

// ── Return value ──────────────────────────
int add(int a, int b) {
    return a + b;
}

// ── void — no return ──────────────────────
void printLine(const char* text) {
    printf("%s\n", text);
}

// ── Pass by value (copy) ──────────────────
void doubleVal(int x) {
    x *= 2;   // local copy — original unchanged
}

// ── Pass by pointer — modifies original ──
void doublePtr(int* x) {
    *x *= 2;
}

// ── Const pointer — read-only ─────────────
void printArr(const int* arr, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// ── Return heap pointer (caller must free) ─
int* makeArray(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) arr[i] = i + 1;
    return arr;
}

// ── No overloading in C — use distinct names ─
int    addInt   (int a, int b)          { return a + b; }
double addDouble(double a, double b)    { return a + b; }

// _Generic (C11) — compile-time type dispatch
#define ADD(a, b) _Generic((a), int: addInt, double: addDouble)(a, b)

// ── Recursion ─────────────────────────────
long long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// ── Variadic function ─────────────────────
int sumN(int count, ...) {
    va_list args;
    va_start(args, count);
    int total = 0;
    for (int i = 0; i < count; i++)
        total += va_arg(args, int);
    va_end(args);
    return total;
}

// ── Function pointers ─────────────────────
int multiply(int a, int b) { return a * b; }

int applyOp(int a, int b, int (*op)(int, int)) {
    return op(a, b);
}

// ── typedef for function pointer ──────────
typedef int (*BinaryOp)(int, int);

BinaryOp getOp(char opChar) {
    switch (opChar) {
        case '+': return add;
        case '*': return multiply;
        default:  return NULL;
    }
}

// ── static — private to this translation unit ─
static void helper(void) {
    printf("Private helper\n");
}

// ── inline — hint to compiler to inline the call ─
static inline int square(int x) {
    return x * x;
}

// ── Forward declaration ───────────────────
void laterFunction(void);

int main(void) {

    // Basic calls
    greet("Alice");
    printLine("No return here");

    // Pass by value vs pointer
    int a = 10;
    doubleVal(a);
    printf("%d\n", a);   // 10 — unchanged

    doublePtr(&a);
    printf("%d\n", a);   // 20 — changed!

    // Array decays to pointer automatically
    int data[] = {1, 2, 3, 4, 5};
    printArr(data, 5);

    // Heap-allocated array
    int* arr = makeArray(5);
    printArr(arr, 5);   // 1 2 3 4 5
    free(arr);

    // _Generic dispatch (C11)
    printf("%d\n",   ADD(2, 3));       // 5     (int)
    printf("%f\n",   ADD(2.5, 3.5));   // 6.0   (double)

    // Recursion
    printf("%lld\n", factorial(5));    // 120
    printf("%lld\n", factorial(10));   // 3628800

    for (int i = 0; i < 8; i++)
        printf("%d ", fibonacci(i));   // 0 1 1 2 3 5 8 13
    printf("\n");

    // Variadic
    printf("%d\n", sumN(5, 1, 2, 3, 4, 5));    // 15
    printf("%d\n", sumN(3, 10, 20, 30));        // 60

    // Function pointers
    printf("%d\n", applyOp(3, 4, multiply));    // 12
    printf("%d\n", applyOp(3, 4, add));         // 7

    BinaryOp op = getOp('+');
    if (op) printf("%d\n", op(5, 3));   // 8
    op = getOp('*');
    if (op) printf("%d\n", op(5, 3));   // 15

    // Array of function pointers
    BinaryOp ops[] = {add, multiply};
    printf("%d %d\n", ops[0](4, 5), ops[1](4, 5));   // 9 20

    printf("%d\n", square(7));   // 49

    helper();
    laterFunction();

    return 0;
}

void laterFunction(void) {
    printf("Called later function!\n");
}
