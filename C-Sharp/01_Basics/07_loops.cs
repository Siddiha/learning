// ─────────────────────────────────────────
//  LOOPS
// ─────────────────────────────────────────

using System;
using System.Collections.Generic;

class Loops
{
    static void Main()
    {
        // ── for loop ──────────────────────────────
        for (int i = 0; i < 5; i++)
            Console.Write(i + " ");   // 0 1 2 3 4
        Console.WriteLine();

        // Count down
        for (int i = 5; i > 0; i--)
            Console.Write(i + " ");   // 5 4 3 2 1
        Console.WriteLine();

        // Step by 2
        for (int i = 0; i < 10; i += 2)
            Console.Write(i + " ");   // 0 2 4 6 8
        Console.WriteLine();

        // ── foreach loop ──────────────────────────
        string[] fruits = { "apple", "banana", "cherry" };
        foreach (string fruit in fruits)
            Console.Write(fruit + " ");
        Console.WriteLine();

        // foreach with index — use a counter
        for (int i = 0; i < fruits.Length; i++)
            Console.Write($"[{i}]{fruits[i]} ");
        Console.WriteLine();

        // ── while loop ────────────────────────────
        int count = 0;
        while (count < 5)
        {
            Console.Write(count + " ");
            count++;
        }
        Console.WriteLine();

        // ── do-while — always runs at least once ──
        int x = 10;
        do
        {
            Console.Write(x + " ");
            x++;
        } while (x < 5);    // condition is false, but body ran once
        Console.WriteLine();

        // ── break — exit loop early ───────────────
        for (int i = 0; i < 10; i++)
        {
            if (i == 5) break;
            Console.Write(i + " ");   // 0 1 2 3 4
        }
        Console.WriteLine();

        // ── continue — skip current iteration ─────
        for (int i = 0; i < 10; i++)
        {
            if (i % 2 == 0) continue;
            Console.Write(i + " ");   // 1 3 5 7 9
        }
        Console.WriteLine();

        // ── Nested loops ──────────────────────────
        for (int i = 1; i <= 3; i++)
        {
            for (int j = 1; j <= 3; j++)
                Console.Write($"{i}x{j}={i * j}  ");
            Console.WriteLine();
        }

        // break from nested loop using goto (use sparingly)
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (i == 1 && j == 1)
                    goto exitLoop;
                Console.Write($"({i},{j}) ");
            }
        }
        exitLoop:
        Console.WriteLine("\nExited nested loop");

        // ── Loop over collections ─────────────────
        var scores = new Dictionary<string, int>
        {
            { "Alice", 90 }, { "Bob", 85 }, { "Carol", 92 }
        };

        foreach (var kvp in scores)
            Console.WriteLine($"{kvp.Key}: {kvp.Value}");

        // ── Infinite loop with break ───────────────
        int num = 1;
        while (true)
        {
            Console.Write(num + " ");
            num *= 2;
            if (num > 100) break;
        }
        Console.WriteLine();
    }
}
