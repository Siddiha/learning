// ─────────────────────────────────────────
//  FILE HANDLING
//  (FILE*, fopen, fclose, fprintf, fscanf,
//   fgets, fread, fwrite, fseek, ftell)
// ─────────────────────────────────────────

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

    // ════════════════════════════════════
    //  WRITE TO FILE
    // ════════════════════════════════════

    // "w" — create/truncate for writing
    FILE* out = fopen("example.txt", "w");
    if (!out) { perror("fopen"); return 1; }

    fprintf(out, "Hello, World!\n");
    fprintf(out, "Line 2\n");
    fprintf(out, "Line 3\n");
    fclose(out);   // always close when done

    // Append mode — "a"
    FILE* app = fopen("example.txt", "a");
    if (!app) { perror("fopen"); return 1; }
    fprintf(app, "Appended line\n");
    fclose(app);

    // ════════════════════════════════════
    //  READ FROM FILE
    // ════════════════════════════════════

    // "r" — open for reading
    FILE* in = fopen("example.txt", "r");
    if (!in) { perror("fopen"); return 1; }

    // Read line by line with fgets
    char line[256];
    while (fgets(line, sizeof(line), in))
        printf("%s", line);   // fgets keeps the '\n'
    fclose(in);

    // Read word by word with fscanf
    FILE* in2 = fopen("example.txt", "r");
    if (!in2) { perror("fopen"); return 1; }
    char word[64];
    while (fscanf(in2, "%63s", word) == 1)
        printf("[%s] ", word);
    printf("\n");
    fclose(in2);

    // Read entire file into a buffer
    FILE* in3 = fopen("example.txt", "r");
    if (!in3) { perror("fopen"); return 1; }
    fseek(in3, 0, SEEK_END);           // go to end
    long fileSize = ftell(in3);        // get size
    rewind(in3);                       // back to start

    char* content = (char*)malloc(fileSize + 1);
    if (!content) { fclose(in3); perror("malloc"); return 1; }
    fread(content, 1, fileSize, in3);
    content[fileSize] = '\0';
    printf("--- full content ---\n%s\n", content);
    free(content);
    fclose(in3);

    // Count lines
    FILE* in4 = fopen("example.txt", "r");
    if (!in4) { perror("fopen"); return 1; }
    int lineCount = 0;
    char buf[256];
    while (fgets(buf, sizeof(buf), in4)) lineCount++;
    printf("Total lines: %d\n", lineCount);
    fclose(in4);

    // ════════════════════════════════════
    //  READ & WRITE (r+)
    // ════════════════════════════════════

    FILE* rw = fopen("rw.txt", "w+");   // "w+" creates & allows both
    if (!rw) { perror("fopen"); return 1; }
    fprintf(rw, "Hello from fopen r+\n");
    rewind(rw);
    fgets(buf, sizeof(buf), rw);
    printf("Read back: %s", buf);
    fclose(rw);

    // ════════════════════════════════════
    //  FILE MODES
    // ════════════════════════════════════
    // "r"  — read (file must exist)
    // "w"  — write (create or truncate)
    // "a"  — append (create if needed)
    // "r+" — read & write (file must exist)
    // "w+" — read & write (create or truncate)
    // "a+" — read & append
    // "rb","wb","ab" — binary variants of above

    // ════════════════════════════════════
    //  BINARY FILES
    // ════════════════════════════════════

    typedef struct { int x; int y; } Point;

    // Write binary
    Point p = {10, 20};
    FILE* binOut = fopen("data.bin", "wb");
    if (!binOut) { perror("fopen"); return 1; }
    fwrite(&p, sizeof(Point), 1, binOut);
    fclose(binOut);

    // Read binary
    Point p2;
    FILE* binIn = fopen("data.bin", "rb");
    if (!binIn) { perror("fopen"); return 1; }
    fread(&p2, sizeof(Point), 1, binIn);
    printf("Binary read: %d, %d\n", p2.x, p2.y);   // 10, 20
    fclose(binIn);

    // ════════════════════════════════════
    //  fseek / ftell / rewind
    // ════════════════════════════════════
    FILE* seek = fopen("example.txt", "r");
    if (!seek) { perror("fopen"); return 1; }

    fseek(seek, 7, SEEK_SET);   // move to byte 7 from start
    fgets(buf, sizeof(buf), seek);
    printf("From byte 7: %s", buf);

    fseek(seek, -5, SEEK_END);  // 5 bytes before end
    long pos = ftell(seek);
    printf("Position: %ld\n", pos);

    rewind(seek);               // back to beginning
    fgets(buf, sizeof(buf), seek);
    printf("First line: %s", buf);
    fclose(seek);

    // ════════════════════════════════════
    //  TEMP FILES & RENAME / REMOVE
    // ════════════════════════════════════

    // tmpfile() — create anonymous temp file (auto-deleted on close)
    FILE* tmp = tmpfile();
    if (tmp) {
        fprintf(tmp, "temp data");
        fclose(tmp);   // deleted here
    }

    // rename / remove
    FILE* src = fopen("copy_src.txt", "w");
    if (src) { fprintf(src, "copy me\n"); fclose(src); }

    rename("copy_src.txt", "copy_dst.txt");    // rename / move
    remove("copy_dst.txt");                    // delete

    // ── Cleanup ───────────────────────────────
    remove("example.txt");
    remove("rw.txt");
    remove("data.bin");

    return 0;
}
