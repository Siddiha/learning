# ─────────────────────────────────────────
#  COMPREHENSIONS
# ─────────────────────────────────────────

# ── List Comprehension ────────────────────
# [expression for item in iterable if condition]

squares = [x**2 for x in range(1, 6)]
print(squares)   # [1, 4, 9, 16, 25]

evens = [x for x in range(20) if x % 2 == 0]
print(evens)

upper_words = [w.upper() for w in ["hello", "world"]]
print(upper_words)

# Nested comprehension — flatten 2D list
matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
flat = [n for row in matrix for n in row]
print(flat)   # [1, 2, 3, 4, 5, 6, 7, 8, 9]

# Transpose a matrix
transposed = [[row[i] for row in matrix] for i in range(3)]
print(transposed)

# ── Dict Comprehension ────────────────────
# {key: value for item in iterable if condition}

word_lengths = {word: len(word) for word in ["apple", "banana", "fig"]}
print(word_lengths)   # {'apple': 5, 'banana': 6, 'fig': 3}

# Invert a dictionary
original = {"a": 1, "b": 2, "c": 3}
inverted = {v: k for k, v in original.items()}
print(inverted)   # {1: 'a', 2: 'b', 3: 'c'}

# Filter dict by value
scores = {"alice": 90, "bob": 55, "carol": 80, "dave": 45}
passing = {name: score for name, score in scores.items() if score >= 60}
print(passing)

# ── Set Comprehension ─────────────────────
# {expression for item in iterable if condition}

unique_lengths = {len(word) for word in ["hi", "hello", "hey", "world"]}
print(unique_lengths)   # {2, 5}  (no duplicates)

# ── Generator Expression ──────────────────
# Like list comprehension but lazy — doesn't build the whole list in memory
# (expression for item in iterable if condition)

gen = (x**2 for x in range(1, 6))
print(type(gen))        # <class 'generator'>
print(next(gen))        # 1
print(next(gen))        # 4
print(list(gen))        # [9, 16, 25]  (generator exhausted after this)

# Use in sum/max/min without building a list
total = sum(x**2 for x in range(1, 100))
print(total)

largest = max(len(w) for w in ["python", "is", "awesome"])
print(largest)   # 7

# ── When to use each ──────────────────────
# List comp   — when you need the full list in memory
# Generator   — when iterating once (saves memory, especially large data)
# Dict comp   — building dicts from iterable
# Set comp    — unique values from iterable
