// ─────────────────────────────────────────
//  ARRAYS
// ─────────────────────────────────────────

using System;

class Arrays
{
    static void Main()
    {
        // ── Declare & Initialize ──────────────────
        int[] nums = { 3, 1, 4, 1, 5, 9, 2, 6 };
        string[] fruits = new string[3];   // fixed size, defaults to null
        fruits[0] = "apple";
        fruits[1] = "banana";
        fruits[2] = "cherry";

        int[] zeros = new int[5];           // all zeros
        bool[] flags = new bool[3];         // all false

        // ── Access ────────────────────────────────
        Console.WriteLine(nums[0]);         // 3
        Console.WriteLine(nums[^1]);        // 6 (last element, C# 8+)
        Console.WriteLine(nums.Length);     // 8

        // ── Slices (C# 8+) ────────────────────────
        int[] slice = nums[2..5];           // [4, 1, 5]
        int[] last3 = nums[^3..];           // [2, 6] — wait, last 3: [9, 2, 6]
        foreach (var n in last3) Console.Write(n + " ");
        Console.WriteLine();

        // ── Iterate ───────────────────────────────
        foreach (int n in nums)
            Console.Write(n + " ");
        Console.WriteLine();

        for (int i = 0; i < nums.Length; i++)
            Console.Write($"[{i}]={nums[i]} ");
        Console.WriteLine();

        // ── Sort & Reverse ────────────────────────
        int[] copy = (int[])nums.Clone();
        Array.Sort(copy);
        Console.WriteLine(string.Join(", ", copy));   // 1, 1, 2, 3, 4, 5, 6, 9

        Array.Reverse(copy);
        Console.WriteLine(string.Join(", ", copy));   // 9, 6, 5, 4, 3, 2, 1, 1

        // ── Search ────────────────────────────────
        Array.Sort(nums);
        int idx = Array.BinarySearch(nums, 5);        // sorted array required
        Console.WriteLine(idx);

        int idx2 = Array.IndexOf(fruits, "banana");   // 1
        Console.WriteLine(idx2);

        // ── Fill & Copy ───────────────────────────
        int[] fives = new int[5];
        Array.Fill(fives, 5);
        Console.WriteLine(string.Join(", ", fives));  // 5, 5, 5, 5, 5

        int[] dest = new int[5];
        Array.Copy(nums, dest, 5);    // copy first 5 elements
        Console.WriteLine(string.Join(", ", dest));

        // ── 2D Arrays ─────────────────────────────
        int[,] matrix = {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };

        Console.WriteLine(matrix[1, 2]);   // 6
        Console.WriteLine(matrix.GetLength(0));  // 3 rows
        Console.WriteLine(matrix.GetLength(1));  // 3 cols

        for (int row = 0; row < matrix.GetLength(0); row++)
        {
            for (int col = 0; col < matrix.GetLength(1); col++)
                Console.Write(matrix[row, col] + " ");
            Console.WriteLine();
        }

        // ── Jagged Array (array of arrays) ────────
        int[][] jagged = new int[3][];
        jagged[0] = new int[] { 1, 2 };
        jagged[1] = new int[] { 3, 4, 5 };
        jagged[2] = new int[] { 6 };

        foreach (var row in jagged)
        {
            foreach (var val in row)
                Console.Write(val + " ");
            Console.WriteLine();
        }

        // ── Useful with LINQ (System.Linq) ────────
        using System.Linq;
        int[] data = { 5, 2, 8, 1, 9, 3 };

        Console.WriteLine(data.Min());             // 1
        Console.WriteLine(data.Max());             // 9
        Console.WriteLine(data.Sum());             // 28
        Console.WriteLine(data.Average());         // 4.666...
        Console.WriteLine(data.Count());           // 6

        int[] sorted = data.OrderBy(x => x).ToArray();
        int[] evens = data.Where(x => x % 2 == 0).ToArray();
        int[] doubled = data.Select(x => x * 2).ToArray();

        Console.WriteLine(string.Join(", ", sorted));   // 1, 2, 3, 5, 8, 9
        Console.WriteLine(string.Join(", ", evens));    // 2, 8
        Console.WriteLine(string.Join(", ", doubled));  // 10, 4, 16, 2, 18, 6
    }
}
