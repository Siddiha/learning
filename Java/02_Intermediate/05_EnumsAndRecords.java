// ─────────────────────────────────────────
//  ENUMS & RECORDS
// ─────────────────────────────────────────

import java.util.*;

public class EnumsAndRecords {

    // ════════════════════════════════════
    //  ENUMS
    // ════════════════════════════════════

    // ── Basic enum ───────────────────────────
    enum Day {
        MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY;

        public boolean isWeekend() {
            return this == SATURDAY || this == SUNDAY;
        }
    }

    // ── Enum with fields and methods ──────────
    enum Planet {
        MERCURY(3.303e+23, 2.4397e6),
        VENUS  (4.869e+24, 6.0518e6),
        EARTH  (5.976e+24, 6.37814e6),
        MARS   (6.421e+23, 3.3972e6);

        private final double mass;     // kg
        private final double radius;   // meters

        Planet(double mass, double radius) {
            this.mass = mass;
            this.radius = radius;
        }

        static final double G = 6.67300E-11;

        double surfaceGravity() {
            return G * mass / (radius * radius);
        }

        double surfaceWeight(double otherMass) {
            return otherMass * surfaceGravity();
        }
    }

    // ── Enum with abstract method ─────────────
    enum Operation {
        ADD("+") {
            @Override public double apply(double x, double y) { return x + y; }
        },
        SUB("-") {
            @Override public double apply(double x, double y) { return x - y; }
        },
        MUL("*") {
            @Override public double apply(double x, double y) { return x * y; }
        },
        DIV("/") {
            @Override public double apply(double x, double y) { return x / y; }
        };

        private final String symbol;
        Operation(String symbol) { this.symbol = symbol; }

        public abstract double apply(double x, double y);

        @Override
        public String toString() { return symbol; }
    }

    // ── Enum implementing an interface ────────
    interface Describable {
        String describe();
    }

    enum Season implements Describable {
        SPRING("Warm and rainy"),
        SUMMER("Hot and sunny"),
        AUTUMN("Cool and windy"),
        WINTER("Cold and snowy");

        private final String description;
        Season(String desc) { this.description = desc; }

        @Override
        public String describe() { return name() + ": " + description; }
    }

    // ════════════════════════════════════
    //  RECORDS  (Java 16+)
    // ════════════════════════════════════
    // Immutable data carriers — auto-generates constructor, getters,
    // equals(), hashCode(), toString().

    // ── Basic record ──────────────────────────
    record Point(double x, double y) {
        // Compact constructor — runs before auto-generated constructor
        Point {
            if (Double.isNaN(x) || Double.isNaN(y))
                throw new IllegalArgumentException("Coordinates cannot be NaN");
        }

        // Custom method
        double distanceTo(Point other) {
            return Math.sqrt(Math.pow(x - other.x, 2) + Math.pow(y - other.y, 2));
        }

        // Static factory
        static Point origin() { return new Point(0, 0); }
    }

    record Person(String name, int age, String email) {
        // Custom compact constructor with validation
        Person {
            Objects.requireNonNull(name, "name cannot be null");
            if (age < 0 || age > 150)
                throw new IllegalArgumentException("Invalid age: " + age);
            email = email == null ? "" : email.strip(); // normalize
        }

        // Derived property
        boolean isAdult() { return age >= 18; }

        // wither — immutable update pattern
        Person withName(String newName) { return new Person(newName, age, email); }
        Person withAge(int newAge)      { return new Person(name, newAge, email); }
    }

    // ── Generic record ────────────────────────
    record Pair<A, B>(A first, B second) {
        static <A, B> Pair<A, B> of(A a, B b) { return new Pair<>(a, b); }
    }

    // ── Record implementing an interface ──────
    interface Shape {
        double area();
    }

    record Circle(double radius) implements Shape {
        Circle { if (radius < 0) throw new IllegalArgumentException("radius < 0"); }
        @Override public double area() { return Math.PI * radius * radius; }
    }

    record Rectangle(double width, double height) implements Shape {
        @Override public double area() { return width * height; }
    }

    public static void main(String[] args) {

        // ── Enum basics ───────────────────────────
        Day today = Day.WEDNESDAY;
        System.out.println(today);             // WEDNESDAY
        System.out.println(today.isWeekend()); // false
        System.out.println(Day.SATURDAY.isWeekend()); // true

        System.out.println(today.name());      // WEDNESDAY
        System.out.println(today.ordinal());   // 2 (0-indexed)

        // Enum from string
        Day friday = Day.valueOf("FRIDAY");
        System.out.println(friday);

        // All values
        for (Day d : Day.values())
            System.out.print(d + " ");
        System.out.println();

        // Enum in switch
        String type = switch (today) {
            case MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY -> "Weekday";
            case SATURDAY, SUNDAY -> "Weekend";
        };
        System.out.println(type);

        // Planet enum with fields
        double earthWeight = 75.0;
        double mass = earthWeight / Planet.EARTH.surfaceGravity();
        for (Planet p : Planet.values())
            System.out.printf("Weight on %-7s: %.2f%n", p, p.surfaceWeight(mass));

        // Operation enum
        double x = 10, y = 3;
        for (Operation op : Operation.values())
            System.out.printf("%.1f %s %.1f = %.2f%n", x, op, y, op.apply(x, y));

        // Season with interface
        for (Season s : Season.values())
            System.out.println(s.describe());

        // EnumSet and EnumMap
        EnumSet<Day> weekends = EnumSet.of(Day.SATURDAY, Day.SUNDAY);
        EnumSet<Day> weekdays = EnumSet.complementOf(weekends);
        System.out.println(weekends);
        System.out.println(weekdays);

        EnumMap<Day, String> schedule = new EnumMap<>(Day.class);
        schedule.put(Day.MONDAY, "Team meeting");
        schedule.put(Day.FRIDAY, "Demo day");
        schedule.forEach((d, task) -> System.out.println(d + ": " + task));

        // ── Records ───────────────────────────────
        Point p1 = new Point(0, 0);
        Point p2 = new Point(3, 4);

        System.out.println(p1);                    // Point[x=0.0, y=0.0]
        System.out.println(p2.x());                // 3.0  — getter
        System.out.println(p1.distanceTo(p2));     // 5.0
        System.out.println(Point.origin());        // Point[x=0.0, y=0.0]

        // Records are immutable — no setters
        // p1.x = 5;  → compile error

        // Auto-generated equals and hashCode
        Point p3 = new Point(0, 0);
        System.out.println(p1.equals(p3));   // true
        System.out.println(p1 == p3);        // false

        Person alice = new Person("Alice", 25, " alice@example.com ");
        System.out.println(alice);              // Person[name=Alice, age=25, email=alice@example.com]
        System.out.println(alice.name());       // Alice
        System.out.println(alice.isAdult());    // true

        // wither — returns new record with one field changed
        Person older = alice.withAge(30);
        System.out.println(older);
        System.out.println(alice);   // unchanged

        // Generic record
        var pair = Pair.of("Alice", 25);
        System.out.println(pair);           // Pair[first=Alice, second=25]
        System.out.println(pair.first());   // Alice

        // Record with interface
        List<Shape> shapes = List.of(new Circle(5), new Rectangle(4, 6));
        for (Shape s : shapes)
            System.out.printf("%s area = %.2f%n", s, s.area());
    }
}
