# ─────────────────────────────────────────
#  ABSTRACTION
# ─────────────────────────────────────────
# Hiding complex implementation details, exposing only what's necessary.
# Abstract classes define a contract — subclasses MUST implement abstract methods.

from abc import ABC, abstractmethod
import math

# ── Abstract Base Class ───────────────────
class Shape(ABC):   # inherit from ABC to make it abstract

    @abstractmethod
    def area(self) -> float:
        pass   # no implementation — subclass must provide it

    @abstractmethod
    def perimeter(self) -> float:
        pass

    # Concrete method — available to all subclasses as-is
    def describe(self):
        return (f"{type(self).__name__}: "
                f"area={self.area():.2f}, perimeter={self.perimeter():.2f}")

    def is_larger_than(self, other: "Shape") -> bool:
        return self.area() > other.area()


# Cannot instantiate abstract class directly:
# s = Shape()  → TypeError: Can't instantiate abstract class Shape


class Circle(Shape):
    def __init__(self, radius):
        self.radius = radius

    def area(self):
        return math.pi * self.radius ** 2

    def perimeter(self):
        return 2 * math.pi * self.radius


class Rectangle(Shape):
    def __init__(self, w, h):
        self.w = w
        self.h = h

    def area(self):
        return self.w * self.h

    def perimeter(self):
        return 2 * (self.w + self.h)


class Square(Rectangle):   # Square IS-A Rectangle
    def __init__(self, side):
        super().__init__(side, side)


c = Circle(5)
r = Rectangle(4, 6)
sq = Square(5)

print(c.describe())
print(r.describe())
print(sq.describe())
print(c.is_larger_than(r))   # True

# ── Abstract with abstract property ───────
class Vehicle(ABC):

    @property
    @abstractmethod
    def max_speed(self) -> int:
        pass

    @abstractmethod
    def fuel_type(self) -> str:
        pass

    def info(self):
        return f"{type(self).__name__}: max={self.max_speed}km/h, fuel={self.fuel_type()}"


class Car(Vehicle):
    @property
    def max_speed(self):
        return 200

    def fuel_type(self):
        return "petrol"


class ElectricCar(Vehicle):
    @property
    def max_speed(self):
        return 250

    def fuel_type(self):
        return "electric"


class Bicycle(Vehicle):
    @property
    def max_speed(self):
        return 30

    def fuel_type(self):
        return "human power"


for v in [Car(), ElectricCar(), Bicycle()]:
    print(v.info())

# ── Abstract class with partial implementation ─
class DataProcessor(ABC):

    @abstractmethod
    def read_data(self):
        pass

    @abstractmethod
    def process(self, data):
        pass

    def run(self):
        data = self.read_data()
        result = self.process(data)
        return result


class CSVProcessor(DataProcessor):
    def read_data(self):
        return [1, 2, 3, 4, 5]   # simulate reading CSV

    def process(self, data):
        return [x * 2 for x in data]


class JSONProcessor(DataProcessor):
    def read_data(self):
        return {"values": [10, 20, 30]}

    def process(self, data):
        return sum(data["values"])


csv_proc = CSVProcessor()
json_proc = JSONProcessor()

print(csv_proc.run())    # [2, 4, 6, 8, 10]
print(json_proc.run())   # 60

# ── Abstraction summary ────────────────────
# Abstract class = defines WHAT to do (interface/contract)
# Concrete class = defines HOW to do it (implementation)
# User of the class only needs to know the WHAT, not the HOW
