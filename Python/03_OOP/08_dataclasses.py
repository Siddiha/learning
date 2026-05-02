# ─────────────────────────────────────────
#  DATACLASSES  (Python 3.7+)
# ─────────────────────────────────────────
# Auto-generates __init__, __repr__, __eq__ and more.
# Perfect for classes that are primarily data containers.

from dataclasses import dataclass, field, asdict, astuple
from typing import List

# ── Basic dataclass ───────────────────────
@dataclass
class Point:
    x: float
    y: float

p1 = Point(1.0, 2.0)
p2 = Point(1.0, 2.0)

print(p1)           # Point(x=1.0, y=2.0)  — auto __repr__ & __str__
print(p1 == p2)     # True — auto __eq__ compares fields

# ── Default values ────────────────────────
@dataclass
class Student:
    name: str
    age: int
    gpa: float = 0.0
    enrolled: bool = True

s = Student("Alice", 20, 3.8)
print(s)   # Student(name='Alice', age=20, gpa=3.8, enrolled=True)

# ── Mutable defaults — use field() ────────
@dataclass
class Course:
    name: str
    students: List[str] = field(default_factory=list)  # NOT default=[]
    credits: int = field(default=3)

c = Course("Python 101")
c.students.append("Alice")
print(c)

# ── frozen=True — immutable dataclass ─────
@dataclass(frozen=True)
class ImmutablePoint:
    x: float
    y: float

ip = ImmutablePoint(3.0, 4.0)
# ip.x = 10   → FrozenInstanceError
print(hash(ip))   # hashable because immutable

# ── order=True — enables <, >, <=, >= ────
@dataclass(order=True)
class Product:
    sort_index: float = field(init=False, repr=False)
    name: str
    price: float

    def __post_init__(self):
        self.sort_index = self.price   # sort by price

products = [
    Product("Apple", 0.99),
    Product("Laptop", 999.99),
    Product("Book", 12.99),
]
print(sorted(products))   # sorted by price

# ── __post_init__ — run code after init ───
@dataclass
class Circle:
    radius: float

    def __post_init__(self):
        if self.radius < 0:
            raise ValueError("Radius cannot be negative")
        import math
        self.area: float = math.pi * self.radius ** 2  # computed field

c = Circle(5.0)
print(c.area)   # 78.539...

# ── asdict / astuple ──────────────────────
@dataclass
class Person:
    name: str
    age: int
    city: str

p = Person("Alice", 25, "NYC")
print(asdict(p))    # {'name': 'Alice', 'age': 25, 'city': 'NYC'}
print(astuple(p))   # ('Alice', 25, 'NYC')

# ── Inheritance with dataclasses ──────────
@dataclass
class Animal:
    name: str
    age: int

@dataclass
class Dog(Animal):
    breed: str

    def bark(self):
        return f"{self.name} says Woof!"

d = Dog("Buddy", 3, "Labrador")
print(d)           # Dog(name='Buddy', age=3, breed='Labrador')
print(d.bark())

# ── Comparison: regular class vs dataclass ─
# Regular class — must write all this manually:
class PointManual:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    def __repr__(self):
        return f"PointManual(x={self.x}, y={self.y})"
    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

# Dataclass — auto-generated:
@dataclass
class PointAuto:
    x: float
    y: float
# Both are equivalent — dataclass saves you the boilerplate!
