# ─────────────────────────────────────────
#  CLASSES & OBJECTS  — The Basics
# ─────────────────────────────────────────

# A class is a blueprint; an object is an instance of that blueprint.

# ── Define a class ────────────────────────
class Dog:
    # Class variable — shared by ALL instances
    species = "Canis lupus familiaris"
    count = 0

    # __init__ is the constructor — called when creating an object
    def __init__(self, name, breed, age):
        # Instance variables — unique to each instance
        self.name = name
        self.breed = breed
        self.age = age
        Dog.count += 1   # track how many dogs created

    # Instance method — has access to self (the instance)
    def bark(self):
        return f"{self.name} says: Woof!"

    def describe(self):
        return f"{self.name} is a {self.age}-year-old {self.breed}"

    def birthday(self):
        self.age += 1
        return f"Happy birthday {self.name}! Now {self.age} years old."

    # __str__ — called by print() and str()
    def __str__(self):
        return f"Dog({self.name}, {self.breed}, {self.age})"

    # __repr__ — developer representation, called by repr()
    def __repr__(self):
        return f"Dog(name={self.name!r}, breed={self.breed!r}, age={self.age})"


# ── Create objects (instances) ────────────
dog1 = Dog("Buddy", "Golden Retriever", 3)
dog2 = Dog("Max", "German Shepherd", 5)

print(dog1.name)          # Buddy
print(dog2.age)           # 5
print(dog1.bark())        # Buddy says: Woof!
print(dog2.describe())    # Max is a 5-year-old German Shepherd
print(dog1.birthday())    # Happy birthday Buddy! Now 4 years old.

# ── Access class variable ─────────────────
print(dog1.species)       # Canis lupus familiaris
print(Dog.species)        # same thing
print(Dog.count)          # 2

# ── __str__ vs __repr__ ───────────────────
print(dog1)           # Dog(Buddy, Golden Retriever, 4)  ← __str__
print(repr(dog1))     # Dog(name='Buddy', breed='Golden Retriever', age=4) ← __repr__

# ── Dynamic attribute assignment ──────────
dog1.color = "golden"    # add attribute after creation
print(dog1.color)

# ── Check type & membership ───────────────
print(type(dog1))                    # <class '__main__.Dog'>
print(isinstance(dog1, Dog))         # True
print(hasattr(dog1, "name"))         # True
print(hasattr(dog1, "email"))        # False
print(getattr(dog1, "breed"))        # Golden Retriever
setattr(dog1, "age", 10)            # set attribute
print(dog1.age)                      # 10

# ── Simple data class ─────────────────────
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def distance_to(self, other):
        return ((self.x - other.x)**2 + (self.y - other.y)**2) ** 0.5

    def __str__(self):
        return f"({self.x}, {self.y})"

p1 = Point(0, 0)
p2 = Point(3, 4)
print(p1.distance_to(p2))   # 5.0
print(p1, p2)
