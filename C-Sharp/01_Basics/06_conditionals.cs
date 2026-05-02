// ─────────────────────────────────────────
//  CONDITIONALS
// ─────────────────────────────────────────

using System;

class Conditionals
{
    static void Main()
    {
        int age = 20;

        // ── if / else if / else ───────────────────
        if (age < 13)
            Console.WriteLine("Child");
        else if (age < 18)
            Console.WriteLine("Teenager");
        else if (age < 60)
            Console.WriteLine("Adult");
        else
            Console.WriteLine("Senior");

        // ── Ternary operator ──────────────────────
        string status = age >= 18 ? "Adult" : "Minor";
        Console.WriteLine(status);

        // ── switch statement ──────────────────────
        int day = 3;
        switch (day)
        {
            case 1:
                Console.WriteLine("Monday");
                break;
            case 2:
                Console.WriteLine("Tuesday");
                break;
            case 3:
            case 4:                              // fall-through (multiple cases)
                Console.WriteLine("Mid-week");
                break;
            case 5:
                Console.WriteLine("Friday!");
                break;
            case 6:
            case 7:
                Console.WriteLine("Weekend");
                break;
            default:
                Console.WriteLine("Invalid");
                break;
        }

        // ── switch expression (C# 8+) — cleaner ──
        string dayName = day switch
        {
            1 => "Monday",
            2 => "Tuesday",
            3 => "Wednesday",
            4 => "Thursday",
            5 => "Friday",
            6 or 7 => "Weekend",
            _ => "Invalid"   // _ is the default
        };
        Console.WriteLine(dayName);

        // ── Pattern matching in switch ─────────────
        object obj = 3.14;
        string result = obj switch
        {
            int i    => $"Integer: {i}",
            double d => $"Double: {d}",
            string s => $"String: {s}",
            null     => "Null",
            _        => "Unknown"
        };
        Console.WriteLine(result);

        // ── When guards in switch ──────────────────
        int score = 85;
        string grade = score switch
        {
            >= 90 => "A",
            >= 80 => "B",
            >= 70 => "C",
            >= 60 => "D",
            _     => "F"
        };
        Console.WriteLine(grade);   // B

        // ── is pattern matching ────────────────────
        object value = "hello";
        if (value is string text)
            Console.WriteLine($"String of length {text.Length}");

        if (value is string { Length: > 3 } longText)
            Console.WriteLine($"Long string: {longText}");

        // ── Null checks ────────────────────────────
        string? name = null;
        if (name is null)
            Console.WriteLine("Name is null");

        if (name is not null)
            Console.WriteLine(name);

        // ── Logical patterns ──────────────────────
        int n = 15;
        if (n is > 10 and < 20)
            Console.WriteLine("Between 10 and 20");

        if (n is < 0 or > 100)
            Console.WriteLine("Out of range");
        else
            Console.WriteLine("In range");
    }
}
