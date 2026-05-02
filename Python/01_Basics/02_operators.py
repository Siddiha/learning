# ─────────────────────────────────────────
#  OPERATORS
# ─────────────────────────────────────────

# ── Arithmetic ────────────────────────────
print(10 + 3)   # 13  — addition
print(10 - 3)   # 7   — subtraction
print(10 * 3)   # 30  — multiplication
print(10 / 3)   # 3.333... — true division (always float)
print(10 // 3)  # 3   — floor division (integer result)
print(10 % 3)   # 1   — modulus (remainder)
print(10 ** 3)  # 1000 — exponentiation

# ── Comparison ────────────────────────────
print(5 == 5)   # True
print(5 != 3)   # True
print(5 > 3)    # True
print(5 < 3)    # False
print(5 >= 5)   # True
print(5 <= 4)   # False

# ── Logical ───────────────────────────────
print(True and False)   # False
print(True or False)    # True
print(not True)         # False

# Short-circuit evaluation
x = 0
print(x != 0 and 10 / x > 1)  # False — second part never evaluated

# ── Assignment Shortcuts ──────────────────
n = 10
n += 5   # n = 15
n -= 3   # n = 12
n *= 2   # n = 24
n //= 4  # n = 6
n **= 2  # n = 36
print(n)

# ── Bitwise ───────────────────────────────
print(0b1010 & 0b1100)   # 8  (AND)
print(0b1010 | 0b1100)   # 14 (OR)
print(0b1010 ^ 0b1100)   # 6  (XOR)
print(~0b1010)            # -11 (NOT)
print(0b0001 << 3)        # 8  (left shift)
print(0b1000 >> 2)        # 2  (right shift)

# ── Membership ────────────────────────────
fruits = ["apple", "banana", "cherry"]
print("apple" in fruits)     # True
print("mango" not in fruits) # True

# ── Identity ──────────────────────────────
a = None
print(a is None)   # True
print(a is not None)  # False
