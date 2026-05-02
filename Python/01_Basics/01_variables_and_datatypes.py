# ─────────────────────────────────────────
#  VARIABLES & DATA TYPES
# ─────────────────────────────────────────

# Python is dynamically typed — no need to declare the type
name = "Alice"          # str
age = 25                # int
height = 5.6            # float
is_student = True       # bool
nothing = None          # NoneType

# Check the type
print(type(name))       # <class 'str'>
print(type(age))        # <class 'int'>
print(type(height))     # <class 'float'>
print(type(is_student)) # <class 'bool'>
print(type(nothing))    # <class 'NoneType'>

# ── Type Casting ──────────────────────────
x = "10"
x_int = int(x)          # str → int
x_float = float(x)      # str → float
x_back = str(x_int)     # int → str

print(x_int + 5)        # 15
print(x_float)          # 10.0

# ── Multiple Assignment ───────────────────
a, b, c = 1, 2, 3
print(a, b, c)          # 1 2 3

# Swap without a temp variable
a, b = b, a
print(a, b)             # 2 1

# ── Constants (by convention, ALL_CAPS) ───
MAX_SPEED = 120
PI = 3.14159

# ── f-strings (Python 3.6+) ───────────────
print(f"Name: {name}, Age: {age}")

# ── Checking identity vs equality ─────────
x = [1, 2, 3]
y = [1, 2, 3]
print(x == y)   # True  — same value
print(x is y)   # False — different objects in memory
