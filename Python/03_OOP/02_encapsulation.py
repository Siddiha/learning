# ─────────────────────────────────────────
#  ENCAPSULATION
# ─────────────────────────────────────────
# Bundling data + methods, and controlling access to the internals.
# Prevents external code from directly modifying internal state.

# ── Access modifiers (by convention) ──────
# public     — name        → accessible anywhere
# protected  — _name       → "please don't use outside class/subclass"
# private    — __name      → name-mangled, harder to access directly

class BankAccount:
    def __init__(self, owner, initial_balance=0):
        self.owner = owner            # public
        self._bank = "PyBank"         # protected — internal use
        self.__balance = initial_balance  # private — name-mangled

    def deposit(self, amount):
        if amount <= 0:
            raise ValueError("Deposit amount must be positive")
        self.__balance += amount
        return f"Deposited ${amount}. New balance: ${self.__balance}"

    def withdraw(self, amount):
        if amount <= 0:
            raise ValueError("Withdrawal amount must be positive")
        if amount > self.__balance:
            raise ValueError("Insufficient funds")
        self.__balance -= amount
        return f"Withdrew ${amount}. New balance: ${self.__balance}"

    def get_balance(self):
        return self.__balance

    def __str__(self):
        return f"Account({self.owner}, balance=${self.__balance})"


acc = BankAccount("Alice", 1000)
print(acc.deposit(500))     # Deposited $500. New balance: $1500
print(acc.withdraw(200))    # Withdrew $200. New balance: $1300
print(acc.get_balance())    # 1300
print(acc.owner)            # Alice  (public — fine)
# print(acc.__balance)      # AttributeError — private!

# Name mangling — still accessible but discouraged
print(acc._BankAccount__balance)   # 1300 — possible but don't do this

# ── @property — Pythonic way to control access ─
class Temperature:
    def __init__(self, celsius=0):
        self._celsius = celsius

    @property
    def celsius(self):
        return self._celsius

    @celsius.setter
    def celsius(self, value):
        if value < -273.15:
            raise ValueError("Temperature below absolute zero!")
        self._celsius = value

    @celsius.deleter
    def celsius(self):
        print("Deleting temperature")
        del self._celsius

    @property
    def fahrenheit(self):
        return self._celsius * 9/5 + 32

    @fahrenheit.setter
    def fahrenheit(self, value):
        self.celsius = (value - 32) * 5/9   # validates via celsius setter

    @property
    def kelvin(self):
        return self._celsius + 273.15


temp = Temperature(25)
print(temp.celsius)       # 25     — looks like attribute access
print(temp.fahrenheit)    # 77.0
print(temp.kelvin)        # 298.15

temp.celsius = 100        # calls the setter
print(temp.fahrenheit)    # 212.0

temp.fahrenheit = 32      # calls fahrenheit setter → celsius setter
print(temp.celsius)       # 0.0

try:
    temp.celsius = -300   # ValueError!
except ValueError as e:
    print(e)

# ── Read-only property ────────────────────
class Circle:
    def __init__(self, radius):
        self._radius = radius

    @property
    def radius(self):
        return self._radius

    @radius.setter
    def radius(self, value):
        if value < 0:
            raise ValueError("Radius cannot be negative")
        self._radius = value

    @property
    def area(self):
        import math
        return math.pi * self._radius ** 2

    @property
    def circumference(self):
        import math
        return 2 * math.pi * self._radius


c = Circle(5)
print(f"Area: {c.area:.2f}")              # Area: 78.54
print(f"Circumference: {c.circumference:.2f}")
c.radius = 10
print(f"New area: {c.area:.2f}")          # New area: 314.16
