# ─────────────────────────────────────────
#  POLYMORPHISM
# ─────────────────────────────────────────
# "Many forms" — same interface, different behavior based on the object type.
# You can call the same method on different objects and get different results.

# ── Method Overriding (Runtime Polymorphism) ─
class Shape:
    def area(self):
        raise NotImplementedError("Subclasses must implement area()")

    def perimeter(self):
        raise NotImplementedError("Subclasses must implement perimeter()")

    def describe(self):
        return f"I am a {type(self).__name__} with area={self.area():.2f}"

import math

class Circle(Shape):
    def __init__(self, radius):
        self.radius = radius

    def area(self):
        return math.pi * self.radius ** 2

    def perimeter(self):
        return 2 * math.pi * self.radius

class Rectangle(Shape):
    def __init__(self, width, height):
        self.width = width
        self.height = height

    def area(self):
        return self.width * self.height

    def perimeter(self):
        return 2 * (self.width + self.height)

class Triangle(Shape):
    def __init__(self, a, b, c):
        self.a, self.b, self.c = a, b, c

    def area(self):
        s = (self.a + self.b + self.c) / 2   # semi-perimeter
        return math.sqrt(s * (s-self.a) * (s-self.b) * (s-self.c))

    def perimeter(self):
        return self.a + self.b + self.c


shapes = [Circle(5), Rectangle(4, 6), Triangle(3, 4, 5)]

for shape in shapes:
    print(shape.describe())   # same call, different result — polymorphism!
    print(f"  Area: {shape.area():.2f}, Perimeter: {shape.perimeter():.2f}")

# ── Duck Typing ───────────────────────────
# "If it walks like a duck and quacks like a duck, it's a duck"
# Python doesn't require formal inheritance — just have the right methods

class Dog:
    def speak(self):
        return "Woof!"

class Cat:
    def speak(self):
        return "Meow!"

class Person:
    def speak(self):
        return "Hello!"

def make_it_speak(thing):
    print(thing.speak())   # doesn't care about type, just needs speak()

for creature in [Dog(), Cat(), Person()]:
    make_it_speak(creature)   # works for all — duck typing

# ── Operator Overloading ──────────────────
# Polymorphism with operators via magic methods

class Vector:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __add__(self, other):          # v1 + v2
        return Vector(self.x + other.x, self.y + other.y)

    def __sub__(self, other):          # v1 - v2
        return Vector(self.x - other.x, self.y - other.y)

    def __mul__(self, scalar):         # v * 3
        return Vector(self.x * scalar, self.y * scalar)

    def __rmul__(self, scalar):        # 3 * v
        return self.__mul__(scalar)

    def __eq__(self, other):           # v1 == v2
        return self.x == other.x and self.y == other.y

    def __abs__(self):                 # abs(v)
        return math.sqrt(self.x**2 + self.y**2)

    def __neg__(self):                 # -v
        return Vector(-self.x, -self.y)

    def __str__(self):
        return f"Vector({self.x}, {self.y})"

    def __repr__(self):
        return self.__str__()


v1 = Vector(2, 3)
v2 = Vector(1, 4)

print(v1 + v2)     # Vector(3, 7)
print(v1 - v2)     # Vector(1, -1)
print(v1 * 3)      # Vector(6, 9)
print(3 * v1)      # Vector(6, 9)
print(abs(v1))     # 3.605...
print(-v1)         # Vector(-2, -3)
print(v1 == Vector(2, 3))   # True

# ── len(), str(), etc. ─────────────────────
class Playlist:
    def __init__(self, songs):
        self.songs = songs

    def __len__(self):             # len(playlist)
        return len(self.songs)

    def __getitem__(self, index):  # playlist[0]
        return self.songs[index]

    def __contains__(self, song):  # "song" in playlist
        return song in self.songs

    def __iter__(self):            # for song in playlist
        return iter(self.songs)

pl = Playlist(["Song A", "Song B", "Song C"])
print(len(pl))              # 3
print(pl[1])                # Song B
print("Song A" in pl)       # True
for song in pl:
    print(song)
