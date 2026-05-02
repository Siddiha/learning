// ─────────────────────────────────────────
//  EXCEPTION HANDLING
// ─────────────────────────────────────────

using System;
using System.IO;

class ExceptionHandling
{
    // ── Custom exception ──────────────────────
    class InsufficientFundsException : Exception
    {
        public decimal Amount { get; }
        public decimal Balance { get; }

        public InsufficientFundsException(decimal amount, decimal balance)
            : base($"Cannot withdraw {amount:C}. Balance is only {balance:C}.")
        {
            Amount = amount;
            Balance = balance;
        }
    }

    static decimal Withdraw(decimal balance, decimal amount)
    {
        if (amount <= 0)
            throw new ArgumentException("Amount must be positive", nameof(amount));
        if (amount > balance)
            throw new InsufficientFundsException(amount, balance);
        return balance - amount;
    }

    static void Main()
    {
        // ── Basic try/catch ───────────────────────
        try
        {
            int result = 10 / 0;
        }
        catch (DivideByZeroException ex)
        {
            Console.WriteLine($"Error: {ex.Message}");
        }

        // ── Catch multiple exceptions ─────────────
        try
        {
            int[] arr = { 1, 2, 3 };
            Console.WriteLine(arr[10]);
        }
        catch (IndexOutOfRangeException)
        {
            Console.WriteLine("Index out of range!");
        }
        catch (Exception ex)   // catch-all (put last)
        {
            Console.WriteLine($"Unexpected: {ex.Message}");
        }

        // ── finally — always runs ─────────────────
        try
        {
            int.Parse("abc");
        }
        catch (FormatException ex)
        {
            Console.WriteLine($"Parse error: {ex.Message}");
        }
        finally
        {
            Console.WriteLine("Finally always runs — good for cleanup");
        }

        // ── when filter on catch ──────────────────
        for (int i = -1; i <= 1; i++)
        {
            try
            {
                if (i == 0) throw new DivideByZeroException();
                Console.WriteLine($"10 / {i} = {10 / i}");
            }
            catch (DivideByZeroException) when (i == 0)
            {
                Console.WriteLine("Division by zero caught with filter");
            }
        }

        // ── Custom exception ──────────────────────
        try
        {
            decimal balance = Withdraw(100m, 150m);
        }
        catch (InsufficientFundsException ex)
        {
            Console.WriteLine(ex.Message);
            Console.WriteLine($"Tried: {ex.Amount:C}, Had: {ex.Balance:C}");
        }

        try
        {
            Withdraw(100m, -50m);
        }
        catch (ArgumentException ex)
        {
            Console.WriteLine($"Argument error: {ex.Message}");
        }

        // ── Re-throw exception ────────────────────
        void Risky()
        {
            try { int.Parse("bad"); }
            catch (FormatException)
            {
                Console.WriteLine("Logging...");
                throw;   // re-throw without losing stack trace
            }
        }

        try { Risky(); }
        catch (FormatException ex) { Console.WriteLine($"Re-caught: {ex.Message}"); }

        // ── Common exception types ─────────────────
        // ArgumentException       — bad argument value
        // ArgumentNullException   — null argument not allowed
        // InvalidOperationException — wrong state
        // NotImplementedException — method not implemented
        // NullReferenceException  — null dereference
        // IndexOutOfRangeException — array index bad
        // OverflowException       — numeric overflow
        // DivideByZeroException   — division by zero
        // FormatException         — wrong string format
        // IOException             — I/O error
        // FileNotFoundException   — file missing
        // TimeoutException        — operation timed out
        // UnauthorizedAccessException — no permission

        // ── TryParse pattern — avoid exceptions ───
        string input = "abc";
        if (int.TryParse(input, out int parsed))
            Console.WriteLine($"Parsed: {parsed}");
        else
            Console.WriteLine("Not a valid number — no exception thrown!");
    }
}
