// ─────────────────────────────────────────
//  VARIABLES & DATA TYPES
// ─────────────────────────────────────────

#include <stdio.h>
#include <stdlib.h>   // atoi, atof, malloc
#include <string.h>   // strlen
#include <stdbool.h>  // bool, true, false (C99)
#include <limits.h>   // INT_MAX, INT_MIN, etc.
#include <float.h>    // DBL_MAX, FLT_MAX, etc.

int main(void) {

    // ── Fundamental Types ─────────────────────
    int age = 25;
    long bigNum = 9000000L;           // 'L' suffix
    long long huge = 9000000000LL;    // 'LL' suffix
    float pi = 3.14f;                 // 'f' suffix required
    double precise = 3.14159265358979;
    long double bigger = 3.14159265358979323846L;
    bool isStudent = true;            // from <stdbool.h> (C99)
    char grade = 'A';                 // single character, single quotes
    unsigned int positive = 42;       // no negatives
    short small = 32000;

    printf("int:    %d\n",  age);
    printf("long:   %ld\n", bigNum);
    printf("double: %f\n",  precise);
    printf("char:   %c\n",  grade);
    printf("bool:   %d\n",  isStudent);   // prints 1 (true) — no boolalpha in C

    // ── Strings — char arrays (no std::string in C) ───
    char name[] = "Alice";            // null-terminated char array
    char empty[1] = "";
    char city[20] = "New York";       // fixed buffer

    printf("Name: %s\n", name);
    printf("Length: %zu\n", strlen(name));   // 5

    // ── const ─────────────────────────────────
    const double PI = 3.14159;
    const int MAX_SIZE = 100;
    // PI = 3;   // error: assignment of read-only variable

    // ── #define — compile-time constants (pre-processor) ─
    #define BUFFER_SIZE 1024
    #define TAX_RATE    0.15

    // ── Type sizes (platform dependent) ──────
    printf("sizeof(int)    = %zu bytes\n", sizeof(int));
    printf("sizeof(double) = %zu bytes\n", sizeof(double));
    printf("sizeof(char)   = %zu bytes\n", sizeof(char));
    printf("sizeof(bool)   = %zu bytes\n", sizeof(bool));
    printf("sizeof(long)   = %zu bytes\n", sizeof(long));

    // ── Numeric limits ────────────────────────
    printf("INT_MAX = %d\n",  INT_MAX);   // 2147483647
    printf("INT_MIN = %d\n",  INT_MIN);   // -2147483648
    printf("DBL_MAX = %e\n",  DBL_MAX);

    // ── Type casting ──────────────────────────
    double d = 9.99;
    int fromDouble = (int)d;   // 9 — truncated
    printf("%d\n", fromDouble);

    int i = 65;
    char ch = (char)i;   // 'A'
    printf("%c\n", ch);

    // ── String to number (C-style) ────────────
    char numStr[] = "42";
    int parsed    = atoi(numStr);       // string → int
    double parsedD = atof("3.14");      // string → double
    long parsedL   = atol("9000");      // string → long

    printf("atoi: %d\n", parsed + 1);  // 43
    printf("atof: %f\n", parsedD);

    // Number → string: use snprintf
    char fromInt[20];
    snprintf(fromInt, sizeof(fromInt), "%d", 100);
    printf("fromInt: %s\n", fromInt);

    char fromDbl[20];
    snprintf(fromDbl, sizeof(fromDbl), "%.2f", 3.14);
    printf("fromDbl: %s\n", fromDbl);

    // ── Multiple declarations ──────────────────
    int x = 1, y = 2, z = 3;
    printf("%d %d %d\n", x, y, z);

    // ── Pointers ─────────────────────────────
    int num = 42;
    int* ptr = &num;   // ptr holds the address of num
    printf("Address: %p\n",  (void*)ptr);
    printf("Value:   %d\n",  *ptr);    // 42 — dereference
    *ptr = 100;
    printf("num is now: %d\n", num);   // 100

    int* nullPtr = NULL;   // use NULL (not nullptr — that's C++)

    // ── Output formatting ─────────────────────
    printf("Name: %s, Age: %d\n", name, age);
    printf("Pi: %.4f\n", PI);
    printf("Sci:  %.4e\n", PI);
    printf("Hex:  %x\n", 255);     // ff
    printf("Oct:  %o\n", 8);       // 10
    printf("Pad:  %05d\n", 42);    // 00042

    // ── _Bool without stdbool.h (C99 primitive) ─
    _Bool flag = 1;
    printf("_Bool: %d\n", flag);

    (void)empty; (void)city; (void)bigger; (void)small;
    (void)positive; (void)pi; (void)huge; (void)MAX_SIZE;
    (void)parsedL; (void)nullPtr;

    return 0;
}
