# ─────────────────────────────────────────
#  SETS  (unordered, mutable, NO duplicates)
# ─────────────────────────────────────────

# Great for: removing duplicates, membership tests, math set operations

fruits = {"apple", "banana", "cherry", "apple"}  # duplicate removed
print(fruits)   # {'apple', 'banana', 'cherry'}  (order may vary)

empty_set = set()   # NOT {} — that creates an empty dict!

# ── Add / Remove ──────────────────────────
fruits.add("mango")
fruits.discard("banana")   # safe — no error if not found
fruits.remove("cherry")    # raises KeyError if not found
popped = fruits.pop()      # removes a random item
print(fruits)

# ── Membership Test ───────────────────────
print("apple" in fruits)   # True (much faster than list for large data)

# ── Set Operations ────────────────────────
a = {1, 2, 3, 4, 5}
b = {4, 5, 6, 7, 8}

print(a | b)    # Union — all items from both: {1,2,3,4,5,6,7,8}
print(a & b)    # Intersection — common items: {4, 5}
print(a - b)    # Difference — in a but not b: {1, 2, 3}
print(b - a)    # Difference — in b but not a: {6, 7, 8}
print(a ^ b)    # Symmetric difference — in one but not both: {1,2,3,6,7,8}

# Same operations using methods
print(a.union(b))
print(a.intersection(b))
print(a.difference(b))
print(a.symmetric_difference(b))

# ── Subset / Superset ─────────────────────
x = {1, 2}
y = {1, 2, 3, 4}

print(x.issubset(y))    # True  — x ⊆ y
print(y.issuperset(x))  # True  — y ⊇ x
print(x.isdisjoint({5, 6}))  # True — no common elements

# ── Remove Duplicates from a List ─────────
nums = [1, 2, 2, 3, 3, 3, 4]
unique = list(set(nums))   # order not guaranteed
print(unique)

# ── Frozenset (immutable set) ─────────────
fs = frozenset([1, 2, 3])
# fs.add(4)  → AttributeError — can't modify
print(fs)

# ── Set Comprehension ─────────────────────
squares = {x**2 for x in range(-3, 4)}
print(squares)   # {0, 1, 4, 9}
