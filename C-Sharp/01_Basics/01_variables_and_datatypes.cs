// ─────────────────────────────────────────
//  VARIABLES & DATA TYPES
// ─────────────────────────────────────────

using System;

class VariablesAndDataTypes
{
    static void Main()
    {
        // ── Value Types ───────────────────────────
        int age = 25;
        long bigNumber = 9_000_000_000L;   // underscore for readability
        float pi = 3.14f;                  // 'f' suffix required
        double precise = 3.14159265358979;
        decimal money = 99.99m;            // 'm' suffix — best for currency
        bool isStudent = true;
        char grade = 'A';                  // single quotes for char
        byte small = 255;                  // 0 to 255
        short s = 32767;

        // ── Reference Types ───────────────────────
        string name = "Alice";
        string? nullableName = null;       // nullable reference (C# 8+)
        object anything = 42;             // can hold any type
        int[] numbers = { 1, 2, 3, 4, 5 };

        // ── var — type inferred by compiler ───────
        var city = "New York";        // compiler knows it's string
        var count = 10;               // compiler knows it's int
        var ratio = 3.14;             // compiler knows it's double
        // var x;                     // ERROR — needs initial value

        // ── const & readonly ──────────────────────
        const double PI = 3.14159;         // compile-time constant
        // PI = 3;                         // ERROR — cannot reassign

        // readonly is set in constructor only (see classes section)

        // ── Type conversion ───────────────────────
        // Implicit (safe, no data loss)
        int i = 100;
        long l = i;        // int → long (safe)
        double d = i;      // int → double (safe)

        // Explicit cast (may lose data)
        double dbl = 9.99;
        int fromDouble = (int)dbl;    // 9 — truncated!
        Console.WriteLine(fromDouble);

        // Convert class — handles string conversions
        string numStr = "42";
        int parsed = Convert.ToInt32(numStr);
        double parsedD = Convert.ToDouble("3.14");
        string fromInt = Convert.ToString(100);

        // int.Parse / int.TryParse
        int x = int.Parse("123");

        bool success = int.TryParse("abc", out int result);
        Console.WriteLine(success);   // False — didn't crash!
        Console.WriteLine(result);    // 0 — default value

        // ── String interpolation ──────────────────
        Console.WriteLine($"Name: {name}, Age: {age}");
        Console.WriteLine($"PI = {PI:F4}");      // format to 4 decimal places
        Console.WriteLine($"Money: {money:C}");  // currency format

        // ── Type checking ─────────────────────────
        Console.WriteLine(age.GetType());         // System.Int32
        Console.WriteLine(name.GetType());        // System.String
        Console.WriteLine(age is int);            // True
        Console.WriteLine(anything is string);    // False

        // as — safe cast, returns null if fails (no exception)
        object obj = "hello";
        string? str = obj as string;
        Console.WriteLine(str);   // hello

        object obj2 = 42;
        string? str2 = obj2 as string;
        Console.WriteLine(str2 ?? "null");  // null — didn't crash

        // ── Nullable value types ──────────────────
        int? maybeNumber = null;
        Console.WriteLine(maybeNumber.HasValue);    // False
        Console.WriteLine(maybeNumber ?? -1);       // -1 (null-coalescing)

        maybeNumber = 42;
        Console.WriteLine(maybeNumber.Value);       // 42
        Console.WriteLine(maybeNumber.GetValueOrDefault());  // 42
    }
}
