# ─────────────────────────────────────────
#  TUPLES  (ordered, IMMUTABLE, allows duplicates)
# ─────────────────────────────────────────

# Use tuples for data that shouldn't change (coordinates, RGB, DB records)

coords = (10, 20)
rgb = (255, 128, 0)
single = (42,)       # trailing comma required for single-element tuple
empty = ()

print(type(coords))  # <class 'tuple'>
print(type(single))  # <class 'tuple'>
print(type((42)))    # <class 'int'> — no trailing comma = just parentheses

# ── Access (same as lists) ────────────────
print(coords[0])     # 10
print(coords[-1])    # 20
print(rgb[1:])       # (128, 0)

# ── Cannot Modify ─────────────────────────
# coords[0] = 99  → TypeError: 'tuple' object does not support item assignment

# ── Unpacking ─────────────────────────────
x, y = coords
print(x, y)          # 10 20

r, g, b = rgb
print(r, g, b)       # 255 128 0

# Extended unpacking
first, *rest = (1, 2, 3, 4, 5)
print(first)   # 1
print(rest)    # [2, 3, 4, 5]

*start, last = (1, 2, 3, 4, 5)
print(start)   # [1, 2, 3, 4]
print(last)    # 5

# ── Swap using tuple unpacking ────────────
a, b = 1, 2
a, b = b, a   # Python unpacks right side first
print(a, b)   # 2 1

# ── Methods ───────────────────────────────
t = (1, 2, 3, 2, 2, 4)
print(t.count(2))   # 3
print(t.index(3))   # 2

# ── Tuple vs List ─────────────────────────
# Tuples are faster and use less memory
# Use tuples for fixed collections (config, constants, function returns)
# Use lists when you need to add/remove items

# ── Named Tuples (structured records) ─────
from collections import namedtuple

Point = namedtuple("Point", ["x", "y"])
p = Point(3, 7)
print(p.x, p.y)   # 3 7
print(p)          # Point(x=3, y=7)

Person = namedtuple("Person", ["name", "age", "city"])
alice = Person("Alice", 25, "NYC")
print(alice.name)  # Alice
