// ─────────────────────────────────────────
//  ERROR HANDLING
//  (C has no exceptions — uses return codes,
//   errno, perror, assert, and setjmp/longjmp)
// ─────────────────────────────────────────

#include <stdio.h>
#include <stdlib.h>   // exit, EXIT_FAILURE, EXIT_SUCCESS, malloc
#include <errno.h>    // errno, error codes (ENOENT, EINVAL, etc.)
#include <string.h>   // strerror
#include <assert.h>   // assert (debug-mode checks)
#include <setjmp.h>   // setjmp, longjmp (non-local jump — rare)

// ── Return code convention ────────────────
// 0 = success, non-zero = error (POSIX style)
typedef enum {
    ERR_OK       = 0,
    ERR_INVALID  = 1,
    ERR_OVERFLOW = 2,
    ERR_NOMEM    = 3
} ErrorCode;

const char* errMsg(ErrorCode code) {
    switch (code) {
        case ERR_OK:       return "Success";
        case ERR_INVALID:  return "Invalid argument";
        case ERR_OVERFLOW: return "Value out of range";
        case ERR_NOMEM:    return "Out of memory";
        default:           return "Unknown error";
    }
}

// ── Function that returns an error code ───
ErrorCode divide(int a, int b, int* out) {
    if (b == 0)   return ERR_INVALID;
    if (out == NULL) return ERR_INVALID;
    *out = a / b;
    return ERR_OK;
}

// ── Output parameter pattern ──────────────
// Pass a pointer where the result/error goes
ErrorCode parseInt(const char* str, int* out) {
    if (!str || !out) return ERR_INVALID;
    errno = 0;
    char* endptr;
    long val = strtol(str, &endptr, 10);
    if (errno != 0 || endptr == str)
        return ERR_INVALID;
    *out = (int)val;
    return ERR_OK;
}

// ── setjmp buffer for non-local jumps ─────
static jmp_buf jumpBuffer;

void riskyOperation(int trigger) {
    if (trigger)
        longjmp(jumpBuffer, 42);   // jump back to setjmp, returning 42
    printf("Risky operation succeeded\n");
}

int main(void) {

    // ════════════════════════════════════
    //  RETURN CODES
    // ════════════════════════════════════

    int result;
    ErrorCode err = divide(10, 2, &result);
    if (err == ERR_OK)
        printf("10 / 2 = %d\n", result);
    else
        printf("Error: %s\n", errMsg(err));

    err = divide(10, 0, &result);
    if (err != ERR_OK)
        printf("Error: %s\n", errMsg(err));   // Error: Invalid argument

    int parsed;
    err = parseInt("123", &parsed);
    printf("Parsed: %d (err=%d)\n", parsed, err);

    err = parseInt("abc", &parsed);
    printf("Parse error: %s\n", errMsg(err));

    // ════════════════════════════════════
    //  errno — system error codes
    // ════════════════════════════════════

    FILE* f = fopen("nonexistent_file.txt", "r");
    if (!f) {
        // errno is set by fopen on failure
        printf("fopen failed: %s (errno %d)\n", strerror(errno), errno);
        perror("fopen");   // prints: "fopen: No such file or directory"
    }

    // Common errno values:
    // ENOENT  (2)  — no such file or directory
    // EACCES  (13) — permission denied
    // EINVAL  (22) — invalid argument
    // ENOMEM  (12) — out of memory
    // EEXIST  (17) — file exists

    // ════════════════════════════════════
    //  perror / strerror
    // ════════════════════════════════════

    errno = EINVAL;
    printf("strerror: %s\n", strerror(errno));   // Invalid argument
    perror("my_func");   // my_func: Invalid argument

    // ════════════════════════════════════
    //  assert — debug-time checks
    //  (disabled when NDEBUG is defined)
    // ════════════════════════════════════

    int x = 5;
    assert(x > 0);            // passes silently
    assert(x == 5);           // passes silently
    // assert(x == 99);       // would abort with message — uncomment to test

    // Static assert (C11) — checked at compile time
    _Static_assert(sizeof(int) >= 2, "int must be at least 2 bytes");

    // ════════════════════════════════════
    //  malloc failure check
    // ════════════════════════════════════

    size_t bigSize = (size_t)-1;   // deliberately huge
    void* mem = malloc(bigSize);
    if (!mem) {
        perror("malloc");          // prints the OS error
        // In a real program: return ERR_NOMEM or exit(EXIT_FAILURE)
    }
    free(mem);   // NULL-safe: free(NULL) is always valid

    // ════════════════════════════════════
    //  setjmp / longjmp — non-local jump
    //  (last resort; avoid in new code)
    // ════════════════════════════════════

    int jumpVal = setjmp(jumpBuffer);   // returns 0 first time
    if (jumpVal == 0) {
        printf("Calling risky operation (no trigger)...\n");
        riskyOperation(0);   // succeeds

        printf("Calling risky operation (with trigger)...\n");
        riskyOperation(1);   // longjmp — skips rest of block

        printf("This line is never reached\n");
    } else {
        printf("Caught jump with value: %d\n", jumpVal);   // 42
    }

    // ════════════════════════════════════
    //  Clean exit
    // ════════════════════════════════════

    // exit(EXIT_FAILURE)  — terminate with failure (1)
    // exit(EXIT_SUCCESS)  — terminate with success (0)
    // abort()             — abnormal termination (SIGABRT, no cleanup)
    // atexit(fn)          — register cleanup function called at exit

    return EXIT_SUCCESS;
}
