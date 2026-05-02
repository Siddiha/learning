# ─────────────────────────────────────────
#  EXCEPTION HANDLING
# ─────────────────────────────────────────

# ── Basic try/except ──────────────────────
try:
    result = 10 / 0
except ZeroDivisionError:
    print("Cannot divide by zero!")

# ── Catch multiple exceptions ─────────────
try:
    nums = [1, 2, 3]
    print(nums[10])
except IndexError:
    print("Index out of range!")
except TypeError:
    print("Wrong type!")

# Catch multiple in one line
try:
    int("abc")
except (ValueError, TypeError) as e:
    print(f"Conversion error: {e}")

# ── else — runs if NO exception occurred ──
try:
    result = 10 / 2
except ZeroDivisionError:
    print("Error!")
else:
    print(f"Result is {result}")   # prints this

# ── finally — ALWAYS runs ─────────────────
try:
    f = open("nonexistent.txt")
except FileNotFoundError:
    print("File not found!")
finally:
    print("This always runs — good for cleanup")

# ── Catching the exception object ─────────
try:
    int("hello")
except ValueError as e:
    print(f"Error type: {type(e).__name__}")
    print(f"Error message: {e}")

# ── Raise exceptions ──────────────────────
def divide(a, b):
    if b == 0:
        raise ValueError("Denominator cannot be zero")
    return a / b

try:
    print(divide(10, 0))
except ValueError as e:
    print(e)

# ── Re-raise exceptions ───────────────────
def risky():
    try:
        return 1 / 0
    except ZeroDivisionError:
        print("Logging the error...")
        raise   # re-raises the same exception

try:
    risky()
except ZeroDivisionError:
    print("Caught in outer block")

# ── Custom Exceptions ─────────────────────
class InsufficientFundsError(Exception):
    def __init__(self, amount, balance):
        super().__init__(f"Cannot withdraw {amount}. Balance is only {balance}.")
        self.amount = amount
        self.balance = balance

def withdraw(balance, amount):
    if amount > balance:
        raise InsufficientFundsError(amount, balance)
    return balance - amount

try:
    new_balance = withdraw(100, 150)
except InsufficientFundsError as e:
    print(e)
    print(f"Tried to withdraw: {e.amount}")

# ── Common Built-in Exceptions ────────────
# ValueError      — wrong value type or out of range
# TypeError       — wrong type passed
# IndexError      — list index out of range
# KeyError        — dict key not found
# AttributeError  — attribute doesn't exist
# NameError       — variable not defined
# FileNotFoundError — file doesn't exist
# ZeroDivisionError — division by zero
# OverflowError   — number too large
# RecursionError  — max recursion depth exceeded
# StopIteration   — iterator exhausted
