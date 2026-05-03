// ─────────────────────────────────────────
//  EXCEPTION HANDLING
// ─────────────────────────────────────────

public class ExceptionHandling {

    // ── Custom checked exception ──────────────
    static class InsufficientFundsException extends Exception {
        private final double amount;
        private final double balance;

        public InsufficientFundsException(double amount, double balance) {
            super(String.format("Cannot withdraw %.2f. Balance is only %.2f.", amount, balance));
            this.amount = amount;
            this.balance = balance;
        }

        public double getAmount()  { return amount; }
        public double getBalance() { return balance; }
    }

    // ── Custom unchecked exception ─────────────
    static class ValidationException extends RuntimeException {
        public ValidationException(String message) {
            super(message);
        }
    }

    // ── Checked exception — must declare or handle ─
    static double withdraw(double balance, double amount) throws InsufficientFundsException {
        if (amount <= 0)
            throw new ValidationException("Amount must be positive");
        if (amount > balance)
            throw new InsufficientFundsException(amount, balance);
        return balance - amount;
    }

    public static void main(String[] args) {

        // ── Basic try/catch ───────────────────────
        try {
            int result = 10 / 0;
        } catch (ArithmeticException e) {
            System.out.println("Error: " + e.getMessage());  // / by zero
        }

        // ── Catch multiple exceptions ─────────────
        try {
            int[] arr = {1, 2, 3};
            System.out.println(arr[10]);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Index out of bounds!");
        } catch (Exception e) {   // catch-all — put last
            System.out.println("Unexpected: " + e.getMessage());
        }

        // ── Multi-catch (Java 7+) ─────────────────
        try {
            String s = null;
            s.length();
        } catch (NullPointerException | IllegalArgumentException e) {
            System.out.println("Caught: " + e.getClass().getSimpleName());
        }

        // ── finally — always runs ─────────────────
        try {
            Integer.parseInt("abc");
        } catch (NumberFormatException e) {
            System.out.println("Parse error: " + e.getMessage());
        } finally {
            System.out.println("Finally always runs — use for cleanup");
        }

        // ── Custom exception ──────────────────────
        try {
            double newBalance = withdraw(100.0, 150.0);
        } catch (InsufficientFundsException e) {
            System.out.println(e.getMessage());
            System.out.printf("Tried: %.2f, Had: %.2f%n", e.getAmount(), e.getBalance());
        }

        // Unchecked — no need to declare or handle
        try {
            withdraw(100.0, -50.0);
        } catch (ValidationException e) {
            System.out.println("Validation: " + e.getMessage());
        } catch (InsufficientFundsException e) {
            System.out.println("Funds: " + e.getMessage());
        }

        // ── try-with-resources (auto close) ───────
        // Any class implementing AutoCloseable is auto-closed
        try (var reader = new java.io.StringReader("hello")) {
            int c = reader.read();
            System.out.println((char) c);   // h
        } catch (java.io.IOException e) {
            System.out.println(e.getMessage());
        }
        // reader.close() called automatically even on exception

        // ── Checked vs Unchecked ──────────────────
        // Checked (extends Exception):
        //   Must be caught or declared with throws
        //   Examples: IOException, SQLException, ClassNotFoundException
        //
        // Unchecked (extends RuntimeException):
        //   Compiler doesn't force handling — programmer's mistake
        //   Examples: NullPointerException, ArrayIndexOutOfBoundsException,
        //             IllegalArgumentException, ArithmeticException

        // ── Common exceptions reference ────────────
        // ArithmeticException       — e.g. division by zero
        // ArrayIndexOutOfBoundsException — bad array index
        // NullPointerException      — null reference used
        // ClassCastException        — bad cast
        // NumberFormatException     — bad string parse
        // IllegalArgumentException  — bad argument
        // IllegalStateException     — bad object state
        // StackOverflowError        — infinite recursion
        // OutOfMemoryError          — heap full
        // IOException               — I/O failure
        // FileNotFoundException     — file missing
        // SQLException              — database error

        // ── Stack trace ───────────────────────────
        try {
            methodA();
        } catch (RuntimeException e) {
            e.printStackTrace();   // prints full call stack
            System.out.println("Exception type: " + e.getClass().getName());
            System.out.println("Message: " + e.getMessage());
        }
    }

    static void methodA() { methodB(); }
    static void methodB() { throw new IllegalStateException("Something went wrong in B"); }
}
