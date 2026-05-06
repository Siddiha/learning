// ─────────────────────────────────────────
//  LOOPS
// ─────────────────────────────────────────

#include <stdio.h>
#include <string.h>   // strlen

int main(void) {

    // ── for loop ──────────────────────────────
    for (int i = 0; i < 5; i++)
        printf("%d ", i);   // 0 1 2 3 4
    printf("\n");

    // Count down
    for (int i = 5; i > 0; i--)
        printf("%d ", i);   // 5 4 3 2 1
    printf("\n");

    // Step by 2
    for (int i = 0; i < 10; i += 2)
        printf("%d ", i);   // 0 2 4 6 8
    printf("\n");

    // Multiple variables
    for (int i = 0, j = 10; i < j; i++, j--)
        printf("(%d,%d) ", i, j);
    printf("\n");

    // ── Iterate over array (no range-based for in C) ─
    const char* fruits[] = {"apple", "banana", "cherry"};
    int fruits_len = 3;

    for (int i = 0; i < fruits_len; i++)
        printf("%s ", fruits[i]);
    printf("\n");

    // ── while loop ────────────────────────────
    int count = 0;
    while (count < 5) {
        printf("%d ", count);
        count++;
    }
    printf("\n");

    // ── do-while — runs at least once ─────────
    int x = 10;
    do {
        printf("%d ", x);
        x++;
    } while (x < 5);    // false immediately, but ran once
    printf("\n");

    // ── break — exit loop early ───────────────
    for (int i = 0; i < 10; i++) {
        if (i == 5) break;
        printf("%d ", i);   // 0 1 2 3 4
    }
    printf("\n");

    // ── continue — skip current iteration ─────
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) continue;
        printf("%d ", i);   // 1 3 5 7 9
    }
    printf("\n");

    // ── Nested loops with goto (avoid — demo only) ─
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 1 && j == 1) goto exitLoop;
            printf("(%d,%d) ", i, j);
        }
    }
    exitLoop:
    printf("\nExited nested loop\n");

    // Better: use a flag variable
    int done = 0;
    for (int i = 0; i < 3 && !done; i++) {
        for (int j = 0; j < 3 && !done; j++) {
            if (i == 1 && j == 1) { done = 1; break; }
            printf("(%d,%d) ", i, j);
        }
    }
    printf("\n");

    // ── Loop over string characters ───────────
    const char* word = "hello";
    for (int i = 0; word[i] != '\0'; i++)
        printf("%c-", word[i]);
    printf("\n");

    // Pointer-style iteration
    for (const char* p = word; *p; p++)
        printf("%c ", *p);
    printf("\n");

    // ── Pointer arithmetic over array ─────────
    int data[] = {5, 2, 8, 1, 9, 3};
    int n = (int)(sizeof(data) / sizeof(data[0]));

    for (int* p = data; p < data + n; p++)
        printf("%d ", *p);
    printf("\n");

    // ── Infinite loop ─────────────────────────
    int num = 1;
    while (1) {       // or: for (;;)
        printf("%d ", num);
        num *= 2;
        if (num > 64) break;
    }
    printf("\n");

    // ── Nested loops — multiplication table ───
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++)
            printf("%3d", i * j);
        printf("\n");
    }

    // ── Loop with index ───────────────────────
    const char* items[] = {"a", "b", "c"};
    int items_len = 3;
    for (int i = 0; i < items_len; i++)
        printf("%d: %s\n", i, items[i]);

    return 0;
}
