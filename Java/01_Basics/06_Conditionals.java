// ─────────────────────────────────────────
//  CONDITIONALS
// ─────────────────────────────────────────

public class Conditionals {
    public static void main(String[] args) {

        int age = 20;

        // ── if / else if / else ───────────────────
        if (age < 13) {
            System.out.println("Child");
        } else if (age < 18) {
            System.out.println("Teenager");
        } else if (age < 60) {
            System.out.println("Adult");
        } else {
            System.out.println("Senior");
        }

        // ── Ternary operator ──────────────────────
        String status = age >= 18 ? "Adult" : "Minor";
        System.out.println(status);

        // Nested ternary (keep it simple)
        int score = 75;
        String grade = score >= 90 ? "A"
                     : score >= 75 ? "B"
                     : score >= 60 ? "C"
                     : "F";
        System.out.println(grade);   // B

        // ── switch statement ──────────────────────
        int day = 3;
        switch (day) {
            case 1:
                System.out.println("Monday");
                break;
            case 2:
                System.out.println("Tuesday");
                break;
            case 3:
            case 4:                           // fall-through (multiple cases)
                System.out.println("Mid-week");
                break;
            case 5:
                System.out.println("Friday!");
                break;
            case 6:
            case 7:
                System.out.println("Weekend");
                break;
            default:
                System.out.println("Invalid");
        }

        // switch on String (Java 7+)
        String command = "start";
        switch (command) {
            case "start":
                System.out.println("Starting...");
                break;
            case "stop":
                System.out.println("Stopping...");
                break;
            default:
                System.out.println("Unknown command");
        }

        // ── switch expression (Java 14+) — no break needed ─
        String dayName = switch (day) {
            case 1 -> "Monday";
            case 2 -> "Tuesday";
            case 3 -> "Wednesday";
            case 4 -> "Thursday";
            case 5 -> "Friday";
            case 6, 7 -> "Weekend";      // multiple cases with comma
            default -> "Invalid";
        };
        System.out.println(dayName);

        // switch expression with blocks
        int result = switch (score / 10) {
            case 10, 9 -> 4;   // A
            case 8     -> 3;   // B
            case 7     -> 2;   // C
            case 6     -> 1;   // D
            default -> {
                System.out.println("Fail");
                yield 0;       // yield returns value from block
            }
        };
        System.out.println("Grade points: " + result);

        // ── Pattern matching switch (Java 21+) ───
        Object obj = 3.14;
        String desc = switch (obj) {
            case Integer i -> "Integer: " + i;
            case Double d  -> "Double: " + d;
            case String s  -> "String: " + s;
            case null      -> "Null value";
            default        -> "Unknown: " + obj;
        };
        System.out.println(desc);

        // ── Guarded patterns ─────────────────────
        Object val = 42;
        switch (val) {
            case Integer i when i > 100 -> System.out.println("Big number: " + i);
            case Integer i when i > 0   -> System.out.println("Positive: " + i);
            case Integer i              -> System.out.println("Non-positive: " + i);
            default                     -> System.out.println("Not an int");
        }

        // ── Null safety ───────────────────────────
        String name = null;
        if (name == null) {
            name = "Anonymous";
        }
        System.out.println(name);

        // Using Objects.requireNonNullElse (Java 9+)
        String display = java.util.Objects.requireNonNullElse(null, "Default");
        System.out.println(display);
    }
}
