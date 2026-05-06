// ─────────────────────────────────────────
//  CONDITIONALS
// ─────────────────────────────────────────

#include <stdio.h>
#include <stdbool.h>   // bool, true, false (C99)

int main(void) {

    int age = 20;

    // ── if / else if / else ───────────────────
    if (age < 13) {
        printf("Child\n");
    } else if (age < 18) {
        printf("Teenager\n");
    } else if (age < 60) {
        printf("Adult\n");
    } else {
        printf("Senior\n");
    }

    // ── Ternary operator ──────────────────────
    const char* status = age >= 18 ? "Adult" : "Minor";
    printf("%s\n", status);

    // Nested ternary
    int score = 75;
    const char* grade = score >= 90 ? "A"
                      : score >= 75 ? "B"
                      : score >= 60 ? "C"
                      : "F";
    printf("%s\n", grade);   // B

    // ── switch statement ──────────────────────
    int day = 3;
    switch (day) {
        case 1:
            printf("Monday\n");
            break;
        case 2:
            printf("Tuesday\n");
            break;
        case 3:
        case 4:                         // fall-through (multiple cases)
            printf("Mid-week\n");
            break;
        case 5:
            printf("Friday!\n");
            break;
        case 6:
        case 7:
            printf("Weekend\n");
            break;
        default:
            printf("Invalid\n");
    }

    // switch on char
    char choice = 'y';
    switch (choice) {
        case 'y':
        case 'Y':
            printf("Yes!\n");
            break;
        case 'n':
        case 'N':
            printf("No!\n");
            break;
        default:
            printf("Unknown\n");
    }

    // ── No if-initializer in C — declare before ─
    int result = score - 50;
    if (result > 0) {
        printf("Passed by %d points\n", result);
    } else {
        printf("Failed by %d points\n", -result);
    }

    // ── Logical operators ─────────────────────
    int x = 15;
    if (x > 10 && x < 20)
        printf("Between 10 and 20\n");

    if (x < 0 || x > 100)
        printf("Out of range\n");
    else
        printf("In range\n");

    // ── Null / pointer checks ─────────────────
    int* ptr = NULL;
    if (ptr == NULL)
        printf("Pointer is null\n");

    if (!ptr)              // same as ptr == NULL
        printf("Also null\n");

    int val = 42;
    ptr = &val;
    if (ptr)               // non-null pointer is truthy
        printf("Pointer has value: %d\n", *ptr);

    // ── Compile-time conditionals ─────────────
    #define DEBUG 1

    #if DEBUG
        printf("Debug mode ON\n");
    #else
        printf("Release mode\n");
    #endif

    // #ifdef — check if a macro is defined at all
    #ifdef _WIN32
        printf("Running on Windows\n");
    #elif defined(__linux__)
        printf("Running on Linux\n");
    #elif defined(__APPLE__)
        printf("Running on macOS\n");
    #else
        printf("Unknown platform\n");
    #endif

    // ── bool (C99 stdbool.h) ──────────────────
    bool isValid = true;
    bool isEmpty = false;

    if (isValid && !isEmpty)
        printf("Valid and not empty\n");

    // Without stdbool.h — just use int (0 = false, non-zero = true)
    int ok = 1;
    if (ok)
        printf("ok is truthy\n");

    // ── switch on enum ────────────────────────
    typedef enum { NORTH, SOUTH, EAST, WEST } Direction;
    Direction dir = EAST;

    switch (dir) {
        case NORTH: printf("Going north\n"); break;
        case SOUTH: printf("Going south\n"); break;
        case EAST:  printf("Going east\n");  break;
        case WEST:  printf("Going west\n");  break;
    }

    return 0;
}
