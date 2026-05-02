// ─────────────────────────────────────────
//  FILE HANDLING
// ─────────────────────────────────────────

using System;
using System.IO;
using System.Text.Json;
using System.Collections.Generic;

class FileHandling
{
    static void Main()
    {
        // ── Write to file ─────────────────────────
        File.WriteAllText("example.txt", "Hello, World!\nLine 2\nLine 3");
        // Overwrites if exists, creates if not

        // Write multiple lines
        string[] lines = { "Line 1", "Line 2", "Line 3" };
        File.WriteAllLines("lines.txt", lines);

        // ── Read entire file ──────────────────────
        string content = File.ReadAllText("example.txt");
        Console.WriteLine(content);

        // ── Read all lines into array ─────────────
        string[] readLines = File.ReadAllLines("example.txt");
        foreach (var line in readLines)
            Console.WriteLine(line);

        // ── Append to file ────────────────────────
        File.AppendAllText("example.txt", "\nAppended line");

        // ── StreamWriter — more control ───────────
        using (var writer = new StreamWriter("stream.txt"))
        {
            writer.WriteLine("First line");
            writer.WriteLine("Second line");
            writer.Write("No newline at end");
        }   // file is closed when using block exits

        // ── StreamReader — line by line ───────────
        using (var reader = new StreamReader("stream.txt"))
        {
            string? line;
            while ((line = reader.ReadLine()) != null)
                Console.WriteLine(line);
        }

        // ── Check existence ───────────────────────
        Console.WriteLine(File.Exists("example.txt"));   // True
        Console.WriteLine(File.Exists("missing.txt"));   // False

        // ── File info ─────────────────────────────
        var info = new FileInfo("example.txt");
        Console.WriteLine(info.Name);             // example.txt
        Console.WriteLine(info.Length);           // size in bytes
        Console.WriteLine(info.Extension);        // .txt
        Console.WriteLine(info.DirectoryName);    // parent directory
        Console.WriteLine(info.CreationTime);
        Console.WriteLine(info.LastWriteTime);

        // ── Copy / Move / Delete ──────────────────
        File.Copy("example.txt", "copy.txt", overwrite: true);
        File.Move("copy.txt", "moved.txt");
        File.Delete("moved.txt");

        // ── Directory operations ──────────────────
        Directory.CreateDirectory("test_dir");
        Console.WriteLine(Directory.Exists("test_dir"));   // True

        // List files in a directory
        foreach (var file in Directory.GetFiles("."))
            Console.WriteLine(file);

        // List with pattern
        foreach (var file in Directory.GetFiles(".", "*.txt"))
            Console.WriteLine(file);

        // ── Path manipulation ─────────────────────
        string fullPath = Path.Combine("folder", "sub", "file.txt");
        Console.WriteLine(fullPath);                    // folder\sub\file.txt

        Console.WriteLine(Path.GetFileName(fullPath));  // file.txt
        Console.WriteLine(Path.GetFileNameWithoutExtension(fullPath)); // file
        Console.WriteLine(Path.GetExtension(fullPath)); // .txt
        Console.WriteLine(Path.GetDirectoryName(fullPath)); // folder\sub

        string temp = Path.GetTempFileName();
        Console.WriteLine(temp);   // temp file path

        Console.WriteLine(Directory.GetCurrentDirectory());  // working directory

        // ── JSON read/write ───────────────────────
        var person = new { Name = "Alice", Age = 25, City = "NYC" };
        string json = JsonSerializer.Serialize(person, new JsonSerializerOptions { WriteIndented = true });
        File.WriteAllText("person.json", json);
        Console.WriteLine(json);

        // Deserialize
        string jsonBack = File.ReadAllText("person.json");
        using var doc = JsonDocument.Parse(jsonBack);
        Console.WriteLine(doc.RootElement.GetProperty("Name").GetString());

        // ── Cleanup ───────────────────────────────
        foreach (var f in new[] { "example.txt", "lines.txt", "stream.txt", "person.json" })
            if (File.Exists(f)) File.Delete(f);

        Directory.Delete("test_dir");
    }
}
