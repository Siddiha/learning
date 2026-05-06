// ─────────────────────────────────────────
//  STRINGS  (char arrays + <string.h>)
// ─────────────────────────────────────────

#include <stdio.h>
#include <string.h>  // strlen, strcpy, strcat, strcmp, strchr, strstr, etc.
#include <ctype.h>   // toupper, tolower, isalpha, isdigit, isspace
#include <stdlib.h>  // atoi, atof, snprintf

int main(void) {

    char s[] = "Hello, World!";

    // ── Basic ─────────────────────────────────
    printf("length:  %zu\n", strlen(s));    // 13
    printf("first:   %c\n",  s[0]);         // H
    printf("last:    %c\n",  s[strlen(s)-1]); // !
    printf("empty?   %d\n",  s[0] == '\0'); // 0 (not empty)

    // ── Copy ──────────────────────────────────
    char copy[50];
    strcpy(copy, s);                   // copy s into copy
    printf("copy:    %s\n", copy);

    strncpy(copy, "Hi", 3);            // safe: copy at most 3 chars + null
    printf("after strncpy: %s\n", copy);

    // Safer: strlcpy (not standard, use snprintf as alternative)
    snprintf(copy, sizeof(copy), "%s", s);   // safe copy via snprintf
    printf("snprintf copy: %s\n", copy);

    // ── Concatenate ───────────────────────────
    char greeting[50] = "Hello";
    strcat(greeting, ", World!");       // appends — watch buffer size!
    printf("concat: %s\n", greeting);

    strncat(greeting, " !!!", 4);       // safe: append at most 4 chars
    printf("strncat: %s\n", greeting);

    // ── Compare ───────────────────────────────
    char a[] = "apple", b[] = "banana";
    printf("strcmp:  %d\n", strcmp(a, b));    // negative (a < b)
    printf("equal?   %d\n", strcmp(a, a));    // 0 (equal)
    printf("strcasecmp ignored — use manually or _stricmp on MSVC\n");

    // ── Search ────────────────────────────────
    char* pos = strstr(s, "World");
    if (pos)
        printf("Found 'World' at index: %td\n", pos - s);   // 7

    char* chr = strchr(s, 'o');
    if (chr)
        printf("First 'o' at index: %td\n", chr - s);       // 4

    char* rchr = strrchr(s, 'l');
    if (rchr)
        printf("Last 'l' at index: %td\n", rchr - s);       // 10

    // ── Substring (manual — no built-in substr) ─
    char sub[10];
    strncpy(sub, s + 7, 5);   // start at index 7, take 5 chars
    sub[5] = '\0';             // must null-terminate manually
    printf("substr: %s\n", sub);   // World

    // ── Case conversion ───────────────────────
    char upper[50];
    snprintf(upper, sizeof(upper), "%s", s);
    for (int i = 0; upper[i]; i++)
        upper[i] = (char)toupper((unsigned char)upper[i]);
    printf("upper: %s\n", upper);   // HELLO, WORLD!

    char lower[50];
    snprintf(lower, sizeof(lower), "%s", s);
    for (int i = 0; lower[i]; i++)
        lower[i] = (char)tolower((unsigned char)lower[i]);
    printf("lower: %s\n", lower);

    // ── Trim whitespace (manual) ──────────────
    char padded[] = "   hello   ";
    char* start = padded;
    while (isspace((unsigned char)*start)) start++;   // skip leading spaces

    char* end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';   // null-terminate after last non-space
    printf("[%s]\n", start);   // [hello]

    // ── Split — strtok ────────────────────────
    char csv[] = "apple,banana,cherry";
    char* token = strtok(csv, ",");   // modifies csv!
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, ",");
    }

    // ── Reverse (manual — no built-in) ────────
    char rev[] = "hello";
    int len = (int)strlen(rev);
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        char tmp = rev[i];
        rev[i]   = rev[j];
        rev[j]   = tmp;
    }
    printf("reversed: %s\n", rev);   // olleh

    // ── Char operations ───────────────────────
    for (int i = 0; s[i]; i++) {
        if (isalpha((unsigned char)s[i]))
            putchar(s[i]);   // letters only
    }
    putchar('\n');

    // isalpha, isdigit, isspace, isupper, islower, toupper, tolower

    // ── String ↔ number conversion ────────────
    char numStr[] = "42";
    int  parsed    = atoi(numStr);       // "42" → 42
    double parsedD = atof("3.14");       // "3.14" → 3.14
    long parsedL   = atol("9000000");    // → long

    printf("%d %f %ld\n", parsed, parsedD, parsedL);

    // Number → string: use snprintf
    char fromNum[20];
    snprintf(fromNum, sizeof(fromNum), "%d", parsed);   // 42 → "42"
    printf("fromNum: %s\n", fromNum);

    // ── Formatted string building via snprintf ─
    char result[100];
    snprintf(result, sizeof(result), "Name: %s, Age: %d", "Alice", 30);
    printf("%s\n", result);

    // ── Read with spaces — fgets ──────────────
    // scanf("%s", name) stops at whitespace
    // fgets(fullName, sizeof(fullName), stdin) reads full line

    // ── C string summary ──────────────────────
    // strlen(s)            — character count (not counting '\0')
    // strcpy(dst, src)     — copy (unsafe — no bounds check)
    // strncpy(dst, src, n) — safer copy
    // strcat(dst, src)     — append (unsafe)
    // strncat(dst, src, n) — safer append
    // strcmp(a, b)         — 0 if equal, <0 if a<b, >0 if a>b
    // strncmp(a, b, n)     — compare first n characters
    // strstr(s, needle)    — pointer to first match, or NULL
    // strchr(s, c)         — pointer to first char c, or NULL
    // strrchr(s, c)        — pointer to last char c, or NULL
    // strtok(s, delim)     — tokenize (modifies string!)
    // snprintf(buf, n, fmt)— safe formatted string build

    return 0;
}
