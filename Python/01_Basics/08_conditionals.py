# ─────────────────────────────────────────
#  CONDITIONALS
# ─────────────────────────────────────────

age = 20

# ── if / elif / else ──────────────────────
if age < 13:
    print("Child")
elif age < 18:
    print("Teenager")
elif age < 60:
    print("Adult")
else:
    print("Senior")

# ── Ternary (one-liner if-else) ───────────
status = "Minor" if age < 18 else "Adult"
print(status)   # Adult

# ── Truthy & Falsy Values ─────────────────
# Falsy: False, 0, 0.0, "", [], {}, set(), None, ()
# Truthy: everything else

values = [0, 1, "", "hello", [], [1], None, True, False]
for v in values:
    if v:
        print(f"{v!r} is truthy")
    else:
        print(f"{v!r} is falsy")

# ── Chained Comparisons ───────────────────
score = 75
if 60 <= score < 80:
    print("B grade")

# ── match / case (Python 3.10+ — like switch) ─
command = "quit"
match command:
    case "start":
        print("Starting...")
    case "stop":
        print("Stopping...")
    case "quit" | "exit":
        print("Quitting...")
    case _:
        print("Unknown command")

# ── Match with conditions (guards) ────────
point = (0, 5)
match point:
    case (0, 0):
        print("Origin")
    case (x, 0):
        print(f"On X-axis at {x}")
    case (0, y):
        print(f"On Y-axis at {y}")
    case (x, y):
        print(f"Point at ({x}, {y})")

# ── Short-circuit for defaults ─────────────
name = ""
display = name or "Anonymous"   # uses "Anonymous" when name is falsy
print(display)

config = None
value = config or {}            # safe default
print(value)
