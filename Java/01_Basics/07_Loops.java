// ─────────────────────────────────────────
//  LOOPS
// ─────────────────────────────────────────

import java.util.*;

public class Loops {
    public static void main(String[] args) {

        // ── for loop ──────────────────────────────
        for (int i = 0; i < 5; i++)
            System.out.print(i + " ");   // 0 1 2 3 4
        System.out.println();

        // Count down
        for (int i = 5; i > 0; i--)
            System.out.print(i + " ");   // 5 4 3 2 1
        System.out.println();

        // Step by 2
        for (int i = 0; i < 10; i += 2)
            System.out.print(i + " ");   // 0 2 4 6 8
        System.out.println();

        // ── enhanced for (for-each) ───────────────
        String[] fruits = {"apple", "banana", "cherry"};
        for (String fruit : fruits)
            System.out.print(fruit + " ");
        System.out.println();

        List<Integer> nums = List.of(1, 2, 3, 4, 5);
        for (int n : nums)
            System.out.print(n + " ");
        System.out.println();

        // ── forEach with lambda ───────────────────
        nums.forEach(n -> System.out.print(n + " "));
        System.out.println();

        // ── while loop ────────────────────────────
        int count = 0;
        while (count < 5) {
            System.out.print(count + " ");
            count++;
        }
        System.out.println();

        // ── do-while — runs at least once ─────────
        int x = 10;
        do {
            System.out.print(x + " ");
            x++;
        } while (x < 5);    // false immediately, but ran once
        System.out.println();

        // ── break — exit loop ─────────────────────
        for (int i = 0; i < 10; i++) {
            if (i == 5) break;
            System.out.print(i + " ");   // 0 1 2 3 4
        }
        System.out.println();

        // ── continue — skip iteration ─────────────
        for (int i = 0; i < 10; i++) {
            if (i % 2 == 0) continue;
            System.out.print(i + " ");   // 1 3 5 7 9
        }
        System.out.println();

        // ── Labeled break (exit nested loop) ──────
        outer:
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i == 1 && j == 1) break outer;
                System.out.print("(" + i + "," + j + ") ");
            }
        }
        System.out.println("\nExited with labeled break");

        // ── Labeled continue ──────────────────────
        outer2:
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (j == 1) continue outer2;   // skip to next i
                System.out.print("(" + i + "," + j + ") ");
            }
        }
        System.out.println();

        // ── Nested loops ──────────────────────────
        for (int i = 1; i <= 3; i++) {
            for (int j = 1; j <= 3; j++)
                System.out.printf("%dx%d=%-3d", i, j, i * j);
            System.out.println();
        }

        // ── Iterate over Map ──────────────────────
        Map<String, Integer> scores = Map.of("Alice", 90, "Bob", 85);
        for (Map.Entry<String, Integer> entry : scores.entrySet())
            System.out.println(entry.getKey() + ": " + entry.getValue());

        // ── Iterate with index (no built-in enumerate) ─
        List<String> items = List.of("a", "b", "c");
        for (int i = 0; i < items.size(); i++)
            System.out.println(i + ": " + items.get(i));

        // ── Infinite loop ─────────────────────────
        int n = 1;
        while (true) {
            System.out.print(n + " ");
            n *= 2;
            if (n > 64) break;
        }
        System.out.println();
    }
}
