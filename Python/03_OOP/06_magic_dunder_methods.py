# ─────────────────────────────────────────
#  MAGIC / DUNDER METHODS  (__method__)
# ─────────────────────────────────────────
# Special methods Python calls automatically in certain situations.
# "dunder" = double underscore

# ── Object lifecycle ──────────────────────
class MyClass:
    def __init__(self, value):         # constructor
        print(f"Creating {value}")
        self.value = value

    def __del__(self):                  # destructor (called on garbage collection)
        print(f"Destroying {self.value}")


# ── String representation ─────────────────
class Book:
    def __init__(self, title, author, pages):
        self.title = title
        self.author = author
        self.pages = pages

    def __str__(self):     # for humans — print(book)
        return f'"{self.title}" by {self.author}'

    def __repr__(self):    # for devs — repr(book), in lists/dicts
        return f"Book({self.title!r}, {self.author!r}, {self.pages})"

    def __len__(self):     # len(book)
        return self.pages

    def __bool__(self):    # if book:
        return self.pages > 0


b = Book("Python Crash Course", "Eric Matthes", 544)
print(b)          # "Python Crash Course" by Eric Matthes
print(repr(b))    # Book('Python Crash Course', 'Eric Matthes', 544)
print(len(b))     # 544
print(bool(b))    # True

# ── Comparison operators ──────────────────
class Student:
    def __init__(self, name, gpa):
        self.name = name
        self.gpa = gpa

    def __eq__(self, other):   # ==
        return self.gpa == other.gpa

    def __lt__(self, other):   # <
        return self.gpa < other.gpa

    def __le__(self, other):   # <=
        return self.gpa <= other.gpa

    def __gt__(self, other):   # >
        return self.gpa > other.gpa

    def __ge__(self, other):   # >=
        return self.gpa >= other.gpa

    def __ne__(self, other):   # !=
        return self.gpa != other.gpa

    def __str__(self):
        return f"Student({self.name}, GPA={self.gpa})"


s1 = Student("Alice", 3.8)
s2 = Student("Bob", 3.5)
s3 = Student("Carol", 3.8)

print(s1 > s2)    # True
print(s1 == s3)   # True
print(s2 < s1)    # True

students = [s1, s2, s3]
print(sorted(students))   # sorted by GPA — uses __lt__

# ── Arithmetic operators ──────────────────
class Money:
    def __init__(self, amount, currency="USD"):
        self.amount = amount
        self.currency = currency

    def __add__(self, other):
        if self.currency != other.currency:
            raise ValueError("Cannot add different currencies")
        return Money(self.amount + other.amount, self.currency)

    def __sub__(self, other):
        return Money(self.amount - other.amount, self.currency)

    def __mul__(self, factor):
        return Money(self.amount * factor, self.currency)

    def __str__(self):
        return f"{self.currency} {self.amount:.2f}"

    def __repr__(self):
        return f"Money({self.amount}, {self.currency!r})"


m1 = Money(10.50)
m2 = Money(5.25)
print(m1 + m2)    # USD 15.75
print(m1 - m2)    # USD 5.25
print(m1 * 3)     # USD 31.50

# ── Container methods ─────────────────────
class Stack:
    def __init__(self):
        self._items = []

    def push(self, item):
        self._items.append(item)

    def pop(self):
        return self._items.pop()

    def __len__(self):           # len(stack)
        return len(self._items)

    def __getitem__(self, index): # stack[0]
        return self._items[index]

    def __setitem__(self, index, value):  # stack[0] = val
        self._items[index] = value

    def __contains__(self, item): # item in stack
        return item in self._items

    def __iter__(self):           # for item in stack
        return iter(self._items)

    def __bool__(self):           # if stack:
        return len(self._items) > 0

    def __str__(self):
        return f"Stack{self._items}"


stack = Stack()
stack.push(1); stack.push(2); stack.push(3)
print(len(stack))       # 3
print(stack[0])         # 1
print(2 in stack)       # True
print(list(stack))      # [1, 2, 3]
if stack:
    print("Stack is not empty")

# ── Context manager ───────────────────────
class FileManager:
    def __init__(self, filename, mode):
        self.filename = filename
        self.mode = mode

    def __enter__(self):
        self.file = open(self.filename, self.mode)
        return self.file

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.file.close()
        return False

with FileManager("temp.txt", "w") as f:
    f.write("Hello from context manager!")

import os; os.remove("temp.txt")

# ── Callable object ───────────────────────
class Adder:
    def __init__(self, n):
        self.n = n

    def __call__(self, x):   # makes instance callable like a function
        return self.n + x


add5 = Adder(5)
print(add5(10))    # 15
print(add5(20))    # 25
print(callable(add5))  # True

# ── Hash (for use in sets/dict keys) ──────
class Coordinate:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __hash__(self):   # needed if __eq__ is defined
        return hash((self.x, self.y))


c1 = Coordinate(1, 2)
c2 = Coordinate(1, 2)
coords = {c1, c2}       # set — uses hash and eq
print(len(coords))       # 1 — same hash, same value
d = {c1: "origin"}
print(d[c2])             # "origin" — c2 == c1
