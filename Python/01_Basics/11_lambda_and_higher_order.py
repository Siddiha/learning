# ─────────────────────────────────────────
#  LAMBDA & HIGHER-ORDER FUNCTIONS
# ─────────────────────────────────────────

# ── Lambda (anonymous function) ───────────
# lambda arguments: expression
square = lambda x: x ** 2
print(square(5))   # 25

add = lambda a, b: a + b
print(add(3, 4))   # 7

# Lambdas are mostly used inline (not assigned to variables)

# ── map() — apply function to every item ──
nums = [1, 2, 3, 4, 5]

doubled = list(map(lambda x: x * 2, nums))
print(doubled)   # [2, 4, 6, 8, 10]

# same with a named function
def triple(x):
    return x * 3

tripled = list(map(triple, nums))
print(tripled)   # [3, 6, 9, 12, 15]

# ── filter() — keep items that pass a test ─
evens = list(filter(lambda x: x % 2 == 0, nums))
print(evens)   # [2, 4]

words = ["hello", "world", "python", "hi"]
long_words = list(filter(lambda w: len(w) > 4, words))
print(long_words)   # ['hello', 'world', 'python']

# ── reduce() — fold list into a single value ─
from functools import reduce

product = reduce(lambda acc, x: acc * x, nums)
print(product)   # 120  (1*2*3*4*5)

total = reduce(lambda acc, x: acc + x, nums)
print(total)     # 15

# ── sorted() with key ─────────────────────
people = [("Alice", 30), ("Bob", 25), ("Carol", 35)]

# sort by age (index 1)
sorted_people = sorted(people, key=lambda p: p[1])
print(sorted_people)   # [('Bob', 25), ('Alice', 30), ('Carol', 35)]

# sort by name length
words2 = ["banana", "apple", "fig", "cherry"]
print(sorted(words2, key=len))  # ['fig', 'apple', 'banana', 'cherry']

# sort by multiple criteria (primary: age, secondary: name)
data = [("Alice", 30), ("Bob", 25), ("Carol", 30)]
print(sorted(data, key=lambda p: (p[1], p[0])))

# ── Functions as arguments ─────────────────
def apply(func, value):
    return func(value)

print(apply(lambda x: x**2, 7))   # 49
print(apply(str.upper, "hello"))  # HELLO

# ── Functions returning functions ──────────
def make_multiplier(factor):
    return lambda x: x * factor

double = make_multiplier(2)
triple2 = make_multiplier(3)

print(double(10))   # 20
print(triple2(10))  # 30
