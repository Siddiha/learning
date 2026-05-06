// ─────────────────────────────────────────
//  OOP  (Classes, Inheritance, Polymorphism,
//        Interfaces, Abstract Classes)
// ─────────────────────────────────────────

import java.util.*;

// ════════════════════════════════════
//  CLASSES & ENCAPSULATION
// ════════════════════════════════════

class Animal {
    // ── Fields ────────────────────────────────
    private String name;     // private — only accessible within class
    private int    age;
    protected String species; // protected — accessible in subclasses

    // ── Static field — shared across all instances ─
    private static int totalAnimals = 0;

    // ── Constructor ───────────────────────────
    public Animal(String name, int age, String species) {
        this.name    = name;   // 'this' disambiguates from parameter
        this.age     = age;
        this.species = species;
        totalAnimals++;
    }

    // ── Copy constructor ──────────────────────
    public Animal(Animal other) {
        this(other.name, other.age, other.species);   // calls primary constructor
    }

    // ── Getters / Setters ─────────────────────
    public String getName()  { return name; }
    public int    getAge()   { return age; }
    public void   setAge(int age) {
        if (age < 0) throw new IllegalArgumentException("Age cannot be negative");
        this.age = age;
    }

    // ── Instance method ───────────────────────
    public String describe() {
        return name + " is a " + species + " aged " + age;
    }

    // ── Static method ─────────────────────────
    public static int getTotalAnimals() { return totalAnimals; }

    // ── toString — called by println ──────────
    @Override
    public String toString() {
        return "Animal{name='" + name + "', age=" + age + "}";
    }

    // ── equals & hashCode — for value equality ─
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Animal)) return false;
        Animal a = (Animal) o;
        return age == a.age && Objects.equals(name, a.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, age);
    }
}

// ════════════════════════════════════
//  INHERITANCE
// ════════════════════════════════════

class Dog extends Animal {
    private String breed;

    public Dog(String name, int age, String breed) {
        super(name, age, "Dog");   // call parent constructor first
        this.breed = breed;
    }

    public String getBreed() { return breed; }

    // ── Override parent method ────────────────
    @Override
    public String describe() {
        return super.describe() + ", breed: " + breed;   // extend parent behavior
    }

    // ── Subclass-specific method ──────────────
    public void fetch() {
        System.out.println(getName() + " fetches the ball!");
    }
}

class Cat extends Animal {
    private boolean isIndoor;

    public Cat(String name, int age, boolean isIndoor) {
        super(name, age, "Cat");
        this.isIndoor = isIndoor;
    }

    @Override
    public String describe() {
        return super.describe() + (isIndoor ? " (indoor)" : " (outdoor)");
    }

    public void purr() {
        System.out.println(getName() + " purrs...");
    }
}

// ════════════════════════════════════
//  INTERFACES
// ════════════════════════════════════

interface Swimmable {
    void swim();   // abstract by default — must be implemented

    // Default method — has a body, can be overridden
    default String getSwimStyle() {
        return "freestyle";
    }

    // Static method — belongs to interface, not instance
    static String getWaterType() {
        return "freshwater";
    }
}

interface Flyable {
    void fly();
    default int getAltitude() { return 100; }
}

// Class implementing multiple interfaces
class Duck extends Animal implements Swimmable, Flyable {
    public Duck(String name, int age) {
        super(name, age, "Duck");
    }

    @Override public void swim() { System.out.println(getName() + " paddles!"); }
    @Override public void fly()  { System.out.println(getName() + " flaps and takes off!"); }

    @Override
    public String getSwimStyle() { return "waddling paddle"; }   // override default
}

// ════════════════════════════════════
//  ABSTRACT CLASSES
// ════════════════════════════════════
// Can't be instantiated. Mix of concrete + abstract methods.

abstract class Shape {
    protected String color;

    public Shape(String color) { this.color = color; }

    // Abstract — subclasses MUST implement
    public abstract double area();
    public abstract double perimeter();

    // Concrete — shared logic, available to all subclasses
    public void printInfo() {
        System.out.printf("%s %s — area=%.2f perimeter=%.2f%n",
            color, getClass().getSimpleName(), area(), perimeter());
    }
}

class Circle extends Shape {
    private double radius;
    public Circle(String color, double radius) {
        super(color);
        this.radius = radius;
    }
    @Override public double area()      { return Math.PI * radius * radius; }
    @Override public double perimeter() { return 2 * Math.PI * radius; }
}

class Rectangle extends Shape {
    private double w, h;
    public Rectangle(String color, double w, double h) {
        super(color);
        this.w = w; this.h = h;
    }
    @Override public double area()      { return w * h; }
    @Override public double perimeter() { return 2 * (w + h); }
}

// ════════════════════════════════════
//  INTERFACE vs ABSTRACT CLASS
// ════════════════════════════════════
// Interface:        multiple inheritance allowed, all methods public, no state (only constants)
// Abstract class:   single inheritance, any visibility, can hold state/constructors

// ════════════════════════════════════
//  POLYMORPHISM
// ════════════════════════════════════

public class OOP {
    public static void main(String[] args) {

        // ── Basic instantiation ───────────────────
        Animal a    = new Animal("Generic", 3, "Unknown");
        Dog dog     = new Dog("Rex", 5, "Labrador");
        Cat cat     = new Cat("Whiskers", 2, true);

        System.out.println(a.describe());
        System.out.println(dog.describe());
        System.out.println(cat.describe());

        // ── toString / equals ─────────────────────
        System.out.println(dog);              // calls toString
        Animal dog2 = new Animal("Rex", 5, "Dog");
        System.out.println(dog.equals(dog2)); // false — different types

        // ── Static member ─────────────────────────
        System.out.println("Total animals: " + Animal.getTotalAnimals());   // 3+

        // ── Polymorphism — treat subclasses as parent type ─
        List<Animal> animals = new ArrayList<>();
        animals.add(dog);
        animals.add(cat);
        animals.add(new Duck("Donald", 4));

        for (Animal animal : animals) {
            System.out.println(animal.describe());   // each calls its OWN describe()
        }

        // ── instanceof — type check before cast ───
        for (Animal animal : animals) {
            if (animal instanceof Dog d) {          // pattern matching (Java 16+)
                d.fetch();
            } else if (animal instanceof Cat c) {
                c.purr();
            } else if (animal instanceof Duck duck) {
                duck.swim();
                duck.fly();
            }
        }

        // ── Interface reference ───────────────────
        Swimmable swimmer = new Duck("Daffy", 3);
        swimmer.swim();
        System.out.println(swimmer.getSwimStyle());
        System.out.println(Swimmable.getWaterType());   // static interface method

        // ── Abstract class ────────────────────────
        List<Shape> shapes = List.of(
            new Circle("red", 5),
            new Rectangle("blue", 4, 6)
        );
        for (Shape s : shapes) s.printInfo();

        // ── Upcasting & downcasting ───────────────
        Animal ref = new Dog("Buddy", 3, "Poodle");   // upcast (implicit — safe)
        System.out.println(ref.describe());            // calls Dog's describe

        if (ref instanceof Dog downDog) {              // downcast (must check first)
            downDog.fetch();
        }

        // ── final — prevent override or inheritance ─
        // final class  — can't be extended (e.g. String)
        // final method — can't be overridden
        // final field  — can't be reassigned (like const)

        // ── Inner / nested classes (brief) ────────
        // Static nested class — doesn't need outer instance
        // Inner class         — tied to outer instance, accesses its fields
        // Anonymous class     — one-off implementation
        Swimmable anon = new Swimmable() {
            @Override public void swim() { System.out.println("Anonymous swimmer!"); }
        };
        anon.swim();

        // Lambda replaces anonymous class for @FunctionalInterface
        // (see 03_FunctionalInterfaces.java)
    }
}
