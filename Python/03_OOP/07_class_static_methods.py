# ─────────────────────────────────────────
#  CLASS METHODS & STATIC METHODS
# ─────────────────────────────────────────

class Date:
    def __init__(self, year, month, day):
        self.year = year
        self.month = month
        self.day = day

    # ── Instance method — receives self ───
    def to_string(self):
        return f"{self.year}-{self.month:02d}-{self.day:02d}"

    # ── Class method — receives cls (the class itself) ─
    # Use for: alternative constructors, factory methods
    @classmethod
    def from_string(cls, date_string):
        year, month, day = map(int, date_string.split("-"))
        return cls(year, month, day)   # cls() instead of Date() — works with subclasses

    @classmethod
    def today(cls):
        from datetime import date
        d = date.today()
        return cls(d.year, d.month, d.day)

    # ── Static method — no self or cls ────
    # Use for: utility functions related to the class but not needing instance/class
    @staticmethod
    def is_valid(year, month, day):
        if month < 1 or month > 12:
            return False
        if day < 1 or day > 31:
            return False
        return True

    @staticmethod
    def days_in_month(month, year):
        import calendar
        return calendar.monthrange(year, month)[1]

    def __str__(self):
        return self.to_string()


# Instance method
d1 = Date(2024, 1, 15)
print(d1.to_string())    # 2024-01-15

# Class method — alternative constructor
d2 = Date.from_string("2024-06-20")
print(d2)                # 2024-06-20

d3 = Date.today()
print(d3)                # today's date

# Static method — doesn't need an instance
print(Date.is_valid(2024, 2, 29))   # True
print(Date.is_valid(2024, 13, 1))   # False
print(Date.days_in_month(2, 2024))  # 29 (leap year)

# Static methods can also be called on instances (works, but call on class is clearer)
print(d1.is_valid(2024, 1, 15))     # True


# ── Practical example: Counter class ──────
class Counter:
    _instance_count = 0   # class variable

    def __init__(self, name):
        self.name = name
        Counter._instance_count += 1

    @classmethod
    def get_count(cls):
        return cls._instance_count

    @classmethod
    def reset_count(cls):
        cls._instance_count = 0

    @staticmethod
    def validate_name(name):
        return isinstance(name, str) and len(name) > 0


c1 = Counter("first")
c2 = Counter("second")
c3 = Counter("third")

print(Counter.get_count())            # 3
print(Counter.validate_name("test"))  # True
print(Counter.validate_name(123))     # False

Counter.reset_count()
print(Counter.get_count())            # 0


# ── Summary ───────────────────────────────
# Method type   | Decorator       | First param | Access
# ------------- | --------------- | ----------- | ------
# Instance      | (none)          | self        | instance + class data
# Class         | @classmethod    | cls         | class data only
# Static        | @staticmethod   | (none)      | no instance/class data
