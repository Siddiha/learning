// ─────────────────────────────────────────
//  STRINGS
// ─────────────────────────────────────────

using System;

class Strings
{
    static void Main()
    {
        string s = "Hello, World!";

        // ── Basic properties ──────────────────────
        Console.WriteLine(s.Length);          // 13
        Console.WriteLine(s[0]);              // H  (char indexing)
        Console.WriteLine(s[^1]);             // !  (index from end, C# 8+)

        // ── Substrings ────────────────────────────
        Console.WriteLine(s.Substring(7));        // World!
        Console.WriteLine(s.Substring(7, 5));     // World
        Console.WriteLine(s[7..]);                // World!    (range, C# 8+)
        Console.WriteLine(s[..5]);                // Hello
        Console.WriteLine(s[7..12]);              // World

        // ── Common Methods ────────────────────────
        Console.WriteLine(s.ToUpper());           // HELLO, WORLD!
        Console.WriteLine(s.ToLower());           // hello, world!
        Console.WriteLine("  hello  ".Trim());    // hello
        Console.WriteLine("  hello  ".TrimStart()); // "hello  "
        Console.WriteLine("  hello  ".TrimEnd());   // "  hello"
        Console.WriteLine(s.Replace("World", "C#"));  // Hello, C#!
        Console.WriteLine(s.Contains("World"));   // True
        Console.WriteLine(s.StartsWith("Hello")); // True
        Console.WriteLine(s.EndsWith("!"));       // True
        Console.WriteLine(s.IndexOf("World"));    // 7
        Console.WriteLine(s.LastIndexOf("l"));    // 10

        // ── Split & Join ──────────────────────────
        string csv = "apple,banana,cherry";
        string[] fruits = csv.Split(',');
        foreach (var fruit in fruits)
            Console.WriteLine(fruit);

        string joined = string.Join(" | ", fruits);
        Console.WriteLine(joined);   // apple | banana | cherry

        // ── String formatting ─────────────────────
        string name = "Alice";
        int age = 25;
        double salary = 75000.5;

        // f-string style (interpolation) — recommended
        Console.WriteLine($"Name: {name}, Age: {age}");

        // Format specifiers inside interpolation
        Console.WriteLine($"Salary: {salary:C}");       // $75,000.50
        Console.WriteLine($"Salary: {salary:N2}");      // 75,000.50
        Console.WriteLine($"Pi: {Math.PI:F4}");         // 3.1416
        Console.WriteLine($"Hex: {255:X}");             // FF
        Console.WriteLine($"Percent: {0.85:P}");        // 85.00%

        // Padding / alignment
        Console.WriteLine($"{"Left",-10}|");    // "Left      |"
        Console.WriteLine($"{"Right",10}|");   // "     Right|"

        // string.Format (older style)
        string msg = string.Format("Name: {0}, Age: {1}", name, age);
        Console.WriteLine(msg);

        // ── Verbatim string (@) ───────────────────
        string path = @"C:\Users\Alice\Documents";   // no need to escape \
        Console.WriteLine(path);

        // ── Raw string literal (C# 11+) ───────────
        string raw = """
            This is a "raw string"
            No escaping needed \ here
            """;
        Console.WriteLine(raw);

        // ── Multiline string ──────────────────────
        string multiline = "Line 1\n" +
                           "Line 2\n" +
                           "Line 3";
        Console.WriteLine(multiline);

        // ── StringBuilder — for heavy string building ─
        using System.Text;
        var sb = new StringBuilder();
        sb.Append("Hello");
        sb.Append(", ");
        sb.Append("World");
        sb.AppendLine("!");
        sb.Insert(0, ">>> ");
        sb.Replace("World", "C#");
        Console.WriteLine(sb.ToString());
        Console.WriteLine($"Length: {sb.Length}");

        // ── Checking content ──────────────────────
        Console.WriteLine(string.IsNullOrEmpty(""));       // True
        Console.WriteLine(string.IsNullOrEmpty(null));     // True
        Console.WriteLine(string.IsNullOrWhiteSpace("  ")); // True

        // ── Compare strings ───────────────────────
        Console.WriteLine("abc".CompareTo("abd"));   // -1 (less than)
        Console.WriteLine("hello".Equals("HELLO", StringComparison.OrdinalIgnoreCase)); // True
    }
}
