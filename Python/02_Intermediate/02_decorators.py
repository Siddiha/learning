# ─────────────────────────────────────────
#  DECORATORS
# ─────────────────────────────────────────
# A decorator is a function that wraps another function to add behavior
# without modifying the original function's code.

import time
import functools

# ── Understanding the concept ─────────────
def my_decorator(func):
    def wrapper():
        print("Before the function runs")
        func()
        print("After the function runs")
    return wrapper

def say_hello():
    print("Hello!")

# Manual decoration
decorated = my_decorator(say_hello)
decorated()

# ── Using @ syntax (syntactic sugar) ──────
@my_decorator
def say_bye():
    print("Bye!")

say_bye()

# ── Decorator with arguments ──────────────
def logger(func):
    @functools.wraps(func)   # preserves original function's metadata
    def wrapper(*args, **kwargs):
        print(f"Calling {func.__name__} with args={args}, kwargs={kwargs}")
        result = func(*args, **kwargs)
        print(f"{func.__name__} returned {result}")
        return result
    return wrapper

@logger
def add(a, b):
    return a + b

add(3, 5)

# ── Timer decorator ───────────────────────
def timer(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        start = time.time()
        result = func(*args, **kwargs)
        end = time.time()
        print(f"{func.__name__} took {end - start:.4f}s")
        return result
    return wrapper

@timer
def slow_function():
    time.sleep(0.1)
    return "done"

slow_function()

# ── Decorator with parameters ─────────────
def repeat(times):
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            for _ in range(times):
                result = func(*args, **kwargs)
            return result
        return wrapper
    return decorator

@repeat(3)
def greet(name):
    print(f"Hello, {name}!")

greet("Alice")   # prints 3 times

# ── Stacking decorators ───────────────────
@timer
@logger
def multiply(a, b):
    return a * b

multiply(4, 5)   # logger runs first (innermost), then timer

# ── Class-based decorator ─────────────────
class CountCalls:
    def __init__(self, func):
        functools.update_wrapper(self, func)
        self.func = func
        self.count = 0

    def __call__(self, *args, **kwargs):
        self.count += 1
        print(f"Call #{self.count} to {self.func.__name__}")
        return self.func(*args, **kwargs)

@CountCalls
def say_hi():
    print("Hi!")

say_hi()
say_hi()
say_hi()
print(f"Total calls: {say_hi.count}")

# ── Common built-in decorators ─────────────
# @staticmethod  — method that doesn't need self or cls
# @classmethod   — method that receives cls instead of self
# @property      — getter for an attribute
# @abstractmethod — must be overridden in subclass
# (These are covered in OOP section)
