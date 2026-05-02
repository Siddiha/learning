// ─────────────────────────────────────────
//  COLLECTIONS  (List, Dictionary, HashSet, Queue, Stack)
// ─────────────────────────────────────────

using System;
using System.Collections.Generic;
using System.Linq;

class Collections
{
    static void Main()
    {
        // ════════════════════════════════════
        //  LIST<T>  — dynamic array, ordered, allows duplicates
        // ════════════════════════════════════
        var fruits = new List<string> { "apple", "banana", "cherry" };

        // Add
        fruits.Add("mango");
        fruits.AddRange(new[] { "kiwi", "plum" });
        fruits.Insert(1, "avocado");   // insert at index

        // Access
        Console.WriteLine(fruits[0]);         // apple
        Console.WriteLine(fruits.Count);      // 7
        Console.WriteLine(fruits[^1]);        // plum (C# 8+)

        // Remove
        fruits.Remove("mango");               // by value
        fruits.RemoveAt(0);                   // by index
        fruits.RemoveAll(f => f.Length <= 4); // remove where condition is true

        // Search
        Console.WriteLine(fruits.Contains("banana"));  // True
        Console.WriteLine(fruits.IndexOf("banana"));   // index or -1
        Console.WriteLine(fruits.Find(f => f.StartsWith("b")));   // banana
        Console.WriteLine(fruits.Any(f => f.Length > 6));         // True
        Console.WriteLine(fruits.All(f => f.Length > 2));         // True

        // Sort
        fruits.Sort();
        fruits.Sort((a, b) => b.CompareTo(a));   // reverse sort
        var sorted = fruits.OrderBy(f => f).ToList();

        // Iterate
        foreach (var fruit in fruits)
            Console.Write(fruit + " ");
        Console.WriteLine();

        // Convert to array
        string[] arr = fruits.ToArray();

        // ════════════════════════════════════
        //  DICTIONARY<K,V>  — key-value pairs, unique keys
        // ════════════════════════════════════
        var scores = new Dictionary<string, int>
        {
            { "Alice", 90 },
            { "Bob", 85 },
            ["Carol"] = 92   // alternative syntax
        };

        // Access
        Console.WriteLine(scores["Alice"]);      // 90

        // Safe access (no KeyNotFoundException)
        if (scores.TryGetValue("Dave", out int daveScore))
            Console.WriteLine(daveScore);
        else
            Console.WriteLine("Dave not found");

        // Add / Update
        scores["Dave"] = 78;           // add new key
        scores["Alice"] = 95;          // update existing
        scores.TryAdd("Bob", 99);      // only adds if key doesn't exist

        // Remove
        scores.Remove("Dave");

        // Check
        Console.WriteLine(scores.ContainsKey("Bob"));     // True
        Console.WriteLine(scores.ContainsValue(95));      // True

        // Iterate
        foreach (var kvp in scores)
            Console.WriteLine($"{kvp.Key}: {kvp.Value}");

        foreach (var key in scores.Keys)
            Console.Write(key + " ");

        foreach (var val in scores.Values)
            Console.Write(val + " ");
        Console.WriteLine();

        // ════════════════════════════════════
        //  HASHSET<T>  — unique values, fast lookup
        // ════════════════════════════════════
        var setA = new HashSet<int> { 1, 2, 3, 4, 5 };
        var setB = new HashSet<int> { 4, 5, 6, 7, 8 };

        setA.Add(6);
        setA.Remove(1);
        Console.WriteLine(setA.Contains(3));   // True

        // Set operations (modify setA in place)
        var union = new HashSet<int>(setA);
        union.UnionWith(setB);
        Console.WriteLine(string.Join(", ", union));   // all unique items

        var intersection = new HashSet<int>(setA);
        intersection.IntersectWith(setB);
        Console.WriteLine(string.Join(", ", intersection));   // common items

        var diff = new HashSet<int>(setA);
        diff.ExceptWith(setB);
        Console.WriteLine(string.Join(", ", diff));   // in A but not B

        Console.WriteLine(setA.IsSubsetOf(union));     // True
        Console.WriteLine(setA.IsSupersetOf(intersection)); // True

        // ════════════════════════════════════
        //  QUEUE<T>  — FIFO (first in, first out)
        // ════════════════════════════════════
        var queue = new Queue<string>();
        queue.Enqueue("first");
        queue.Enqueue("second");
        queue.Enqueue("third");

        Console.WriteLine(queue.Peek());      // first — doesn't remove
        Console.WriteLine(queue.Dequeue());   // first — removes it
        Console.WriteLine(queue.Count);       // 2

        // ════════════════════════════════════
        //  STACK<T>  — LIFO (last in, first out)
        // ════════════════════════════════════
        var stack = new Stack<int>();
        stack.Push(1);
        stack.Push(2);
        stack.Push(3);

        Console.WriteLine(stack.Peek());    // 3 — doesn't remove
        Console.WriteLine(stack.Pop());     // 3 — removes it
        Console.WriteLine(stack.Count);     // 2

        // ════════════════════════════════════
        //  LINKEDLIST<T>  — efficient insert/remove at any position
        // ════════════════════════════════════
        var linked = new LinkedList<int>();
        linked.AddLast(1);
        linked.AddLast(2);
        linked.AddLast(3);
        linked.AddFirst(0);

        Console.WriteLine(linked.First!.Value);   // 0
        Console.WriteLine(linked.Last!.Value);    // 3
        linked.Remove(2);

        foreach (var item in linked)
            Console.Write(item + " ");
        Console.WriteLine();
    }
}
