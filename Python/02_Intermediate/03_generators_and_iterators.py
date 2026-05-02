# ─────────────────────────────────────────
#  GENERATORS & ITERATORS
# ─────────────────────────────────────────

# ── Iterator Protocol ─────────────────────
# An object is iterable if it has __iter__()
# An object is an iterator if it has __iter__() and __next__()

my_list = [1, 2, 3]
iterator = iter(my_list)

print(next(iterator))   # 1
print(next(iterator))   # 2
print(next(iterator))   # 3
# next(iterator)        # StopIteration

# ── Custom Iterator (class-based) ─────────
class Countdown:
    def __init__(self, start):
        self.current = start

    def __iter__(self):
        return self

    def __next__(self):
        if self.current <= 0:
            raise StopIteration
        value = self.current
        self.current -= 1
        return value

for n in Countdown(5):
    print(n, end=" ")   # 5 4 3 2 1
print()

# ── Generator Function ────────────────────
# Uses 'yield' instead of 'return'
# Each call to next() resumes where it left off

def countdown(start):
    while start > 0:
        yield start
        start -= 1

gen = countdown(5)
print(next(gen))   # 5
print(next(gen))   # 4

for n in countdown(3):
    print(n, end=" ")   # 3 2 1
print()

# ── yield pauses execution ────────────────
def step_by_step():
    print("Step 1")
    yield 1
    print("Step 2")
    yield 2
    print("Step 3")
    yield 3

for step in step_by_step():
    print(f"Got: {step}")

# ── Infinite Generator ────────────────────
def natural_numbers():
    n = 1
    while True:
        yield n
        n += 1

gen = natural_numbers()
first_10 = [next(gen) for _ in range(10)]
print(first_10)   # [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

# ── Generator with send() ─────────────────
def accumulator():
    total = 0
    while True:
        value = yield total
        if value is None:
            break
        total += value

acc = accumulator()
next(acc)          # prime the generator
print(acc.send(10))   # 10
print(acc.send(20))   # 30
print(acc.send(5))    # 35

# ── yield from — delegate to sub-generator ─
def chain(*iterables):
    for it in iterables:
        yield from it

for item in chain([1, 2], [3, 4], [5]):
    print(item, end=" ")   # 1 2 3 4 5
print()

# ── Generator vs List memory comparison ───
import sys

list_version = [x**2 for x in range(10000)]
gen_version = (x**2 for x in range(10000))

print(f"List size: {sys.getsizeof(list_version)} bytes")
print(f"Generator size: {sys.getsizeof(gen_version)} bytes")
# Generator uses ~120 bytes regardless of size!

# ── itertools — powerful generator tools ──
import itertools

# chain — join multiple iterables
for x in itertools.chain([1, 2], [3, 4], [5]):
    print(x, end=" ")
print()

# islice — take a slice from any iterable
for x in itertools.islice(natural_numbers(), 5):
    print(x, end=" ")   # 1 2 3 4 5
print()

# cycle — repeat iterable indefinitely
colors = itertools.cycle(["red", "green", "blue"])
for _ in range(6):
    print(next(colors), end=" ")
print()

# count — infinite counter
counter = itertools.count(10, 2)
print([next(counter) for _ in range(5)])   # [10, 12, 14, 16, 18]
