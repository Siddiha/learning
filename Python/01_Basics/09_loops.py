# ─────────────────────────────────────────
#  LOOPS
# ─────────────────────────────────────────

# ── for loop ──────────────────────────────
for i in range(5):
    print(i, end=" ")   # 0 1 2 3 4
print()

# range(start, stop, step)
for i in range(1, 10, 2):
    print(i, end=" ")   # 1 3 5 7 9
print()

for i in range(5, 0, -1):
    print(i, end=" ")   # 5 4 3 2 1
print()

# ── Iterate over collections ──────────────
fruits = ["apple", "banana", "cherry"]
for fruit in fruits:
    print(fruit)

# enumerate — get index + value
for i, fruit in enumerate(fruits):
    print(f"{i}: {fruit}")

for i, fruit in enumerate(fruits, start=1):  # start index at 1
    print(f"{i}. {fruit}")

# ── Iterate over dict ─────────────────────
scores = {"math": 90, "science": 85}
for subject, score in scores.items():
    print(f"{subject}: {score}")

# ── zip — iterate two lists together ──────
names = ["Alice", "Bob", "Carol"]
ages = [25, 30, 28]
for name, age in zip(names, ages):
    print(f"{name} is {age}")

# ── while loop ────────────────────────────
count = 0
while count < 5:
    print(count, end=" ")
    count += 1
print()

# ── break — exit loop early ───────────────
for i in range(10):
    if i == 5:
        break
    print(i, end=" ")   # 0 1 2 3 4
print()

# ── continue — skip current iteration ─────
for i in range(10):
    if i % 2 == 0:
        continue
    print(i, end=" ")   # 1 3 5 7 9
print()

# ── for-else / while-else ─────────────────
# else block runs if loop completed without break
for i in range(5):
    if i == 10:
        break
else:
    print("Loop completed without break")

# Useful for search patterns
target = 7
for num in [1, 3, 5, 9]:
    if num == target:
        print("Found!")
        break
else:
    print("Not found")   # prints this

# ── Nested Loops ──────────────────────────
for i in range(1, 4):
    for j in range(1, 4):
        print(f"{i}x{j}={i*j}", end="  ")
    print()

# ── List/Dict/Set comprehensions as loop alternatives ─
squares = [x**2 for x in range(1, 6)]
print(squares)

even_squares = [x**2 for x in range(10) if x % 2 == 0]
print(even_squares)
