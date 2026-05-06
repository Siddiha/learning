// ─────────────────────────────────────────
//  ARRAYS  (static + dynamic via malloc)
// ─────────────────────────────────────────

#include <stdio.h>
#include <stdlib.h>  // malloc, calloc, realloc, free
#include <string.h>  // memset, memcpy, memmove

// Helper — compare ints for qsort
int cmpAsc(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}
int cmpDesc(const void* a, const void* b) {
    return *(int*)b - *(int*)a;
}

int main(void) {

    // ════════════════════════════════════
    //  STATIC ARRAYS
    // ════════════════════════════════════

    int nums[5] = {3, 1, 4, 1, 5};
    int zeros[5] = {0};          // all zeros (first 0 fills the rest too)
    int partial[5] = {1, 2};     // {1, 2, 0, 0, 0}

    printf("%d\n", nums[0]);     // 3
    printf("%d\n", nums[4]);     // 5
    // No bounds checking! nums[10] is undefined behavior

    int size = (int)(sizeof(nums) / sizeof(nums[0]));   // length
    printf("size: %d\n", size);   // 5

    for (int i = 0; i < 5; i++)
        printf("%d ", nums[i]);
    printf("\n");

    // ── 2D array ──────────────────────────────
    int matrix[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    printf("%d\n", matrix[1][2]);   // 6

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }

    // ── memset — fill with a byte value ───────
    int arr[5];
    memset(arr, 0, sizeof(arr));   // fill with 0
    for (int i = 0; i < 5; i++)
        printf("%d ", arr[i]);   // 0 0 0 0 0
    printf("\n");

    // ── memcpy — copy bytes ───────────────────
    int src[5] = {1, 2, 3, 4, 5};
    int dst[5];
    memcpy(dst, src, sizeof(src));
    printf("%d\n", dst[2]);   // 3

    // ── memmove — safe overlapping copy ───────
    int buf[8] = {1, 2, 3, 4, 5, 0, 0, 0};
    memmove(buf + 2, buf, 5 * sizeof(int));   // shift right by 2
    printf("%d\n", buf[4]);   // 3

    // ── Sort with qsort ───────────────────────
    int data[] = {5, 2, 8, 1, 9, 3};
    int n = (int)(sizeof(data) / sizeof(data[0]));

    qsort(data, n, sizeof(int), cmpAsc);
    for (int i = 0; i < n; i++)
        printf("%d ", data[i]);   // 1 2 3 5 8 9
    printf("\n");

    qsort(data, n, sizeof(int), cmpDesc);
    for (int i = 0; i < n; i++)
        printf("%d ", data[i]);   // 9 8 5 3 2 1
    printf("\n");

    // ── Binary search with bsearch ────────────
    int sorted[] = {1, 2, 3, 4, 5};
    int key = 3;
    int* found = (int*)bsearch(&key, sorted, 5, sizeof(int), cmpAsc);
    if (found)
        printf("Found %d at index %td\n", *found, found - sorted);

    // ── Min / Max (manual — no built-in for arrays) ─
    int minVal = data[0], maxVal = data[0];
    for (int i = 1; i < n; i++) {
        if (data[i] < minVal) minVal = data[i];
        if (data[i] > maxVal) maxVal = data[i];
    }
    printf("min: %d, max: %d\n", minVal, maxVal);

    // Sum
    int total = 0;
    for (int i = 0; i < n; i++) total += data[i];
    printf("sum: %d\n", total);

    // ════════════════════════════════════
    //  DYNAMIC ARRAYS — malloc / calloc / realloc
    // ════════════════════════════════════

    // malloc — allocate uninitialized memory
    int* heap = (int*)malloc(5 * sizeof(int));
    if (!heap) { perror("malloc failed"); return 1; }
    for (int i = 0; i < 5; i++) heap[i] = i + 1;
    printf("%d\n", heap[2]);   // 3
    free(heap);
    heap = NULL;   // avoid dangling pointer

    // calloc — allocate and zero-initialize
    int* zeros2 = (int*)calloc(5, sizeof(int));
    if (!zeros2) { perror("calloc failed"); return 1; }
    printf("%d\n", zeros2[0]);   // 0
    free(zeros2);

    // realloc — resize existing allocation
    int* dyn = (int*)malloc(3 * sizeof(int));
    if (!dyn) { perror("malloc failed"); return 1; }
    dyn[0] = 1; dyn[1] = 2; dyn[2] = 3;

    int* tmp = (int*)realloc(dyn, 6 * sizeof(int));
    if (!tmp) { free(dyn); perror("realloc failed"); return 1; }
    dyn = tmp;
    dyn[3] = 4; dyn[4] = 5; dyn[5] = 6;

    for (int i = 0; i < 6; i++) printf("%d ", dyn[i]);
    printf("\n");
    free(dyn);

    // ── Pointer arithmetic ────────────────────
    int vals[] = {10, 20, 30, 40, 50};
    int* p = vals;
    printf("%d\n", *p);      // 10
    printf("%d\n", *(p+2));  // 30
    p += 3;
    printf("%d\n", *p);      // 40

    // Array name IS a pointer to first element
    printf("same: %d %d\n", vals[2], *(vals + 2));   // 30 30

    // ── Dynamic 2D array ──────────────────────
    int rows = 3, cols = 3;
    int** grid = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++)
        grid[i] = (int*)malloc(cols * sizeof(int));

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            grid[i][j] = i * cols + j;

    printf("grid[1][2] = %d\n", grid[1][2]);   // 5

    for (int i = 0; i < rows; i++) free(grid[i]);
    free(grid);

    // ── VLA — variable-length array (C99) ─────
    int len;
    printf("Enter array size (try 4): ");
    len = 4;   // hardcoded for demo
    int vla[len];   // size known only at runtime (stack allocation)
    for (int i = 0; i < len; i++) vla[i] = i * 10;
    printf("vla[2] = %d\n", vla[2]);   // 20

    return 0;
}
