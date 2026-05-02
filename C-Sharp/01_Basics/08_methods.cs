// ─────────────────────────────────────────
//  METHODS (FUNCTIONS)
// ─────────────────────────────────────────

using System;
using System.Collections.Generic;

class Methods
{
    // ── Basic method ──────────────────────────
    static string Greet(string name)
    {
        return $"Hello, {name}!";
    }

    // ── void — no return value ────────────────
    static void PrintLine(string text)
    {
        Console.WriteLine(text);
    }

    // ── Default parameters ────────────────────
    static string Greet2(string name, string greeting = "Hello")
    {
        return $"{greeting}, {name}!";
    }

    // ── Named arguments ───────────────────────
    static void CreateUser(string name, int age, string city = "Unknown")
    {
        Console.WriteLine($"{name}, {age}, {city}");
    }

    // ── Return multiple values (tuple) ────────
    static (int Min, int Max, double Avg) GetStats(int[] nums)
    {
        return (Array.Min(nums), Array.Max(nums), nums.Average());
    }
    // helper since Array doesn't have Min/Max static — using LINQ:
    static (int min, int max) MinMax(int[] nums)
    {
        int min = nums[0], max = nums[0];
        foreach (var n in nums) { if (n < min) min = n; if (n > max) max = n; }
        return (min, max);
    }

    // ── params — variable number of arguments ─
    static int Sum(params int[] numbers)
    {
        int total = 0;
        foreach (var n in numbers) total += n;
        return total;
    }

    // ── ref — pass by reference ───────────────
    static void Increment(ref int value)
    {
        value++;   // modifies the original variable
    }

    // ── out — return via parameter ────────────
    static bool TryDivide(int a, int b, out double result)
    {
        if (b == 0) { result = 0; return false; }
        result = (double)a / b;
        return true;
    }

    // ── Expression-bodied method (C# 6+) ──────
    static int Square(int x) => x * x;
    static string Repeat(string s, int n) => string.Concat(Enumerable.Repeat(s, n));

    // ── Method overloading ────────────────────
    static int Add(int a, int b) => a + b;
    static double Add(double a, double b) => a + b;
    static string Add(string a, string b) => a + b;

    // ── Recursive method ──────────────────────
    static int Factorial(int n)
    {
        if (n <= 1) return 1;
        return n * Factorial(n - 1);
    }

    static int Fibonacci(int n)
    {
        if (n <= 1) return n;
        return Fibonacci(n - 1) + Fibonacci(n - 2);
    }

    static void Main()
    {
        // Basic call
        Console.WriteLine(Greet("Alice"));          // Hello, Alice!
        PrintLine("I print nothing back");

        // Default parameters
        Console.WriteLine(Greet2("Bob"));            // Hello, Bob!
        Console.WriteLine(Greet2("Bob", "Hi"));      // Hi, Bob!

        // Named arguments — any order
        CreateUser(age: 25, name: "Alice");
        CreateUser("Bob", city: "NYC", age: 30);

        // Multiple return
        var (min, max) = MinMax(new[] { 3, 1, 7, 2, 9 });
        Console.WriteLine($"Min={min}, Max={max}");

        // params
        Console.WriteLine(Sum(1, 2, 3));         // 6
        Console.WriteLine(Sum(1, 2, 3, 4, 5));   // 15

        // ref
        int val = 5;
        Increment(ref val);
        Console.WriteLine(val);   // 6

        // out
        if (TryDivide(10, 3, out double result))
            Console.WriteLine($"10/3 = {result:F2}");

        TryDivide(10, 0, out double r2);
        Console.WriteLine(r2);   // 0 — didn't crash

        // Expression-bodied
        Console.WriteLine(Square(7));         // 49
        Console.WriteLine(Repeat("ab", 3));   // ababab

        // Overloading
        Console.WriteLine(Add(2, 3));           // 5  (int)
        Console.WriteLine(Add(2.5, 3.5));       // 6  (double)
        Console.WriteLine(Add("Hello", " C#")); // Hello C# (string)

        // Recursion
        Console.WriteLine(Factorial(5));   // 120
        Console.WriteLine(Factorial(10));  // 3628800

        for (int i = 0; i < 8; i++)
            Console.Write(Fibonacci(i) + " ");   // 0 1 1 2 3 5 8 13
        Console.WriteLine();

        // ── Local functions ───────────────────────
        int MultiplyBy(int x, int factor) => x * factor;
        Console.WriteLine(MultiplyBy(5, 3));   // 15

        // ── Lambda / Anonymous functions ──────────
        Func<int, int> doubleIt = x => x * 2;
        Func<int, int, int> multiply = (a, b) => a * b;
        Action<string> shout = s => Console.WriteLine(s.ToUpper());

        Console.WriteLine(doubleIt(7));        // 14
        Console.WriteLine(multiply(3, 4));     // 12
        shout("hello");                        // HELLO

        // Lambdas with LINQ
        var nums = new[] { 1, 2, 3, 4, 5, 6 };
        var evens = System.Linq.Enumerable.Where(nums, x => x % 2 == 0);
        foreach (var n in evens) Console.Write(n + " ");   // 2 4 6
        Console.WriteLine();
    }
}
