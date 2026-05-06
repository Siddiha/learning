// ─────────────────────────────────────────
//  STRINGS  (char arrays + <string.h>)
// ─────────────────────────────────────────

#include <stdio.h>
#include <string.h>  // strlen, strcpy, strcat, strcmp, strchr, strstr, strtok
#include <ctype.h>   // toupper, tolower, isalpha, isdigit, isspace
#include <stdlib.h>  // atoi, atof

int main(void) {

    char s[] = "Hello, World!";

    // ── Basic ─────────────────────────────────
    printf("length:  %zu\n",  strlen(s));           // 13
    printf("first:   %c\n",   s[0]);                // H
    printf("last:    %c\n",   s[strlen(s)-1]);      // !
    printf("empty?   %d\n",   s[0] == '\0');        // 0 (not empty)

    // ── Copy ──────────────────────────────────
    char copy[50];
    strcpy(copy, s);                        // copy s into copy (unsafe — no bounds check)
    printf("copy:    %s\n", copy);

    strncpy(copy, "Hi", sizeof(copy)-1);    // safe: copy at most n chars
    copy[sizeof(copy)-1] = '\0';            // ensure null termination
    printf("strncpy: %s\n", copy);

    // Safer idiom via snprintf
    snprintf(copy, sizeof(copy), "%s", s);
    printf("snprintf copy: %s\n", copy);

    // ── Concatenate ───────────────────────────
    char greeting[50] = "Hello";
    strcat(greeting, ", World!");           // appends — watch buffer size!
    printf("strcat:  %s\n", greeting);

    strncat(greeting, " !!!", 4);           // safe: append at most 4 chars
    printf("strncat: %s\n", greeting);

    // ── Compare ───────────────────────────────
    char a[] = "apple", b[] = "banana";
    printf("strcmp:  %d\n", strcmp(a, b));   // negative (a < b)
    printf("equal?   %d\n", strcmp(a, a));   // 0

    printf("strncmp: %d\n", strncmp("abcXX", "abcYY", 3));  // 0 (first 3 match)

    // ── Search ────────────────────────────────
    char* pos = strstr(s, "World");
    if (pos)
        printf("'World' at index: %td\n", pos - s);   // 7

    char* chr = strchr(s, 'o');
    if (chr)
        printf("first 'o' at: %td\n", chr - s);       // 4

    char* rchr = strrchr(s, 'l');
    if (rchr)
        printf("last 'l' at:  %td\n", rchr - s);      // 10

    // ── Substring (manual — no built-in) ─────
    char sub[10];
    strncpy(sub, s + 7, 5);   // start at index 7, take 5 chars
    sub[5] = '\0';             // must null-terminate manually
    printf("substr: %s\n", sub);   // World

    // ── Case conversion (manual) ──────────────
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
    *(end + 1) = '\0';
    printf("[%s]\n", start);   // [hello]

    // ── Split — strtok (modifies original!) ───
    char csv[] = "apple,banana,cherry";
    char* token = strtok(csv, ",");
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, ",");
    }

    // ── Reverse (manual) ─────────────────────
    char rev[] = "hello";
    int len = (int)strlen(rev);
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        char tmp = rev[i];
        rev[i]   = rev[j];
        rev[j]   = tmp;
    }
    printf("reversed: %s\n", rev);   // olleh

    // ── Char classification (ctype.h) ────────
    for (int i = 0; s[i]; i++) {
        if (isalpha((unsigned char)s[i]))
            putchar(s[i]);   // letters only
    }
    putchar('\n');

    // isalpha — letter         isdigit — digit
    // isspace — whitespace     isupper — uppercase
    // islower — lowercase      isalnum — letter or digit
    // ispunct — punctuation    isprint — printable

    // ── String ↔ number conversion ────────────
    char numStr[] = "42";
    int    parsed  = atoi(numStr);       // "42" → 42
    double parsedD = atof("3.14");       // "3.14" → 3.14
    long   parsedL = atol("9000000");    // → long

    printf("%d %f %ld\n", parsed, parsedD, parsedL);

    // Number → string via snprintf
    char fromNum[20];
    snprintf(fromNum, sizeof(fromNum), "%d", parsed);
    printf("fromNum: %s\n", fromNum);

    // ── Formatted string building ─────────────
    char result[100];
    snprintf(result, sizeof(result), "Name: %s, Age: %d", "Alice", 30);
    printf("%s\n", result);

    // ── C string function summary ──────────────
    // strlen(s)             — character count (not counting '\0')
    // strcpy(dst, src)      — copy (no bounds check!)
    // strncpy(dst, src, n)  — safer copy (always null-terminate after)
    // strcat(dst, src)      — append (no bounds check!)
    // strncat(dst, src, n)  — safer append
    // strcmp(a, b)          — 0 if equal, <0 if a<b, >0 if a>b
    // strncmp(a, b, n)      — compare first n chars
    // strstr(s, needle)     — pointer to first match, or NULL
    // strchr(s, c)          — pointer to first char c, or NULL
    // strrchr(s, c)         — pointer to last char c, or NULL
    // strtok(s, delim)      — tokenize (modifies string!)
    // snprintf(buf,n,fmt)   — safe formatted string build

    return 0;
}
