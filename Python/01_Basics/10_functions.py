# ─────────────────────────────────────────
#  FUNCTIONS
# ─────────────────────────────────────────

# ── Basic Function ────────────────────────
def greet(name):
    return f"Hello, {name}!"

print(greet("Alice"))   # Hello, Alice!

# ── Default Arguments ─────────────────────
def greet2(name, greeting="Hello"):
    return f"{greeting}, {name}!"

print(greet2("Bob"))              # Hello, Bob!
print(greet2("Bob", "Hi"))        # Hi, Bob!
print(greet2("Bob", greeting="Hey"))  # Hey, Bob!

# ── *args — variable positional arguments ─
def add(*numbers):
    return sum(numbers)

print(add(1, 2))         # 3
print(add(1, 2, 3, 4))   # 10

# ── **kwargs — variable keyword arguments ─
def print_info(**details):
    for key, value in details.items():
        print(f"{key}: {value}")

print_info(name="Alice", age=25, city="NYC")

# ── Combining all argument types ──────────
# Order must be: positional → *args → keyword-only → **kwargs
def mixed(a, b, *args, key="default", **kwargs):
    print(a, b, args, key, kwargs)

mixed(1, 2, 3, 4, key="custom", x=10, y=20)

# ── Return Multiple Values ────────────────
def min_max(numbers):
    return min(numbers), max(numbers)   # returns a tuple

low, high = min_max([3, 1, 7, 2, 9])
print(low, high)   # 1 9

# ── Docstrings ────────────────────────────
def area(radius):
    """Calculate the area of a circle given its radius."""
    return 3.14159 * radius ** 2

print(area(5))
print(area.__doc__)   # access the docstring

# ── Scope: LEGB Rule ──────────────────────
# Local → Enclosing → Global → Built-in

x = "global"

def outer():
    x = "enclosing"
    def inner():
        x = "local"
        print(x)   # local
    inner()
    print(x)       # enclosing

outer()
print(x)           # global

# ── global keyword ────────────────────────
counter = 0
def increment():
    global counter
    counter += 1

increment()
increment()
print(counter)   # 2

# ── nonlocal keyword ──────────────────────
def make_counter():
    count = 0
    def increment():
        nonlocal count
        count += 1
        return count
    return increment

c = make_counter()
print(c())   # 1
print(c())   # 2
print(c())   # 3

# ── Type Hints (Python 3.5+) ──────────────
def multiply(a: int, b: int) -> int:
    return a * b

print(multiply(3, 4))   # 12
