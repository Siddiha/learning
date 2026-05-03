// ─────────────────────────────────────────
//  FILE HANDLING
// ─────────────────────────────────────────

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class FileHandling {
    public static void main(String[] args) throws IOException {

        // ── Write to file (NIO — modern way) ──────
        Path path = Path.of("example.txt");
        Files.writeString(path, "Hello, World!\nLine 2\nLine 3\n");

        // Write list of lines
        Files.write(Path.of("lines.txt"),
            List.of("Line 1", "Line 2", "Line 3"));

        // Append
        Files.writeString(path, "Appended line\n", StandardOpenOption.APPEND);

        // ── Read entire file ──────────────────────
        String content = Files.readString(path);
        System.out.println(content);

        // Read all lines into list
        List<String> lines = Files.readAllLines(path);
        lines.forEach(System.out::println);

        // ── BufferedReader — line by line ─────────
        try (BufferedReader reader = Files.newBufferedReader(path)) {
            String line;
            while ((line = reader.readLine()) != null)
                System.out.println(line);
        }

        // ── BufferedWriter ────────────────────────
        try (BufferedWriter writer = Files.newBufferedWriter(Path.of("output.txt"))) {
            writer.write("First line");
            writer.newLine();
            writer.write("Second line");
        }

        // ── Check existence & file info ───────────
        System.out.println(Files.exists(path));           // true
        System.out.println(Files.exists(Path.of("x")));  // false
        System.out.println(Files.size(path));             // size in bytes
        System.out.println(Files.isDirectory(path));      // false

        // ── Copy / Move / Delete ──────────────────
        Files.copy(path, Path.of("copy.txt"), StandardCopyOption.REPLACE_EXISTING);
        Files.move(Path.of("copy.txt"), Path.of("moved.txt"), StandardCopyOption.REPLACE_EXISTING);
        Files.delete(Path.of("moved.txt"));
        Files.deleteIfExists(Path.of("nonexistent.txt")); // no exception if missing

        // ── Directory operations ──────────────────
        Path dir = Path.of("test_dir");
        Files.createDirectories(dir);                     // create including parents
        System.out.println(Files.isDirectory(dir));       // true

        // Create a file inside dir
        Files.writeString(dir.resolve("file1.txt"), "content");

        // List files in directory
        try (var stream = Files.list(dir)) {
            stream.forEach(System.out::println);
        }

        // List all .txt files recursively
        try (var stream = Files.walk(Path.of("."))) {
            stream.filter(p -> p.toString().endsWith(".txt"))
                  .forEach(System.out::println);
        }

        // ── Path manipulation ─────────────────────
        Path p = Path.of("folder", "sub", "file.txt");
        System.out.println(p);                        // folder\sub\file.txt
        System.out.println(p.getFileName());          // file.txt
        System.out.println(p.getParent());            // folder\sub
        System.out.println(p.getRoot());              // null (relative path)
        System.out.println(p.toAbsolutePath());       // full absolute path
        System.out.println(p.resolve("other.txt"));   // folder\sub\other.txt
        System.out.println(p.normalize());            // cleans up . and ..

        // ── File attributes ───────────────────────
        var attrs = Files.readAttributes(path, java.nio.file.attribute.BasicFileAttributes.class);
        System.out.println(attrs.creationTime());
        System.out.println(attrs.lastModifiedTime());
        System.out.println(attrs.size());

        // ── Scanner — read user input / file ──────
        try (Scanner scanner = new Scanner(path)) {
            while (scanner.hasNextLine())
                System.out.println(scanner.nextLine());
        }

        // ── PrintWriter — formatted output ────────
        try (PrintWriter pw = new PrintWriter("formatted.txt")) {
            pw.printf("Name: %s, Age: %d%n", "Alice", 25);
            pw.println("Second line");
        }

        // ── Cleanup ───────────────────────────────
        for (String f : new String[]{"example.txt", "lines.txt", "output.txt", "formatted.txt"})
            Files.deleteIfExists(Path.of(f));

        Files.deleteIfExists(dir.resolve("file1.txt"));
        Files.deleteIfExists(dir);
    }
}
