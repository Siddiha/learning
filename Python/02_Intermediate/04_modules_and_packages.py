# ─────────────────────────────────────────
#  MODULES & PACKAGES
# ─────────────────────────────────────────

# ── Importing modules ─────────────────────
import math
import os
import sys

print(math.pi)          # 3.141592653589793
print(math.sqrt(16))    # 4.0
print(math.ceil(4.2))   # 5
print(math.floor(4.8))  # 4
print(math.log(100, 10))  # 2.0
print(math.factorial(5))  # 120

# ── Import specific names ─────────────────
from math import sqrt, pi, e

print(sqrt(25))   # 5.0 — no "math." prefix needed
print(pi)         # 3.14159...

# ── Import with alias ─────────────────────
import math as m
from datetime import datetime as dt

print(m.cos(0))   # 1.0
now = dt.now()
print(now)

# ── Useful Standard Library Modules ───────

# random
import random
print(random.random())             # float between 0 and 1
print(random.randint(1, 10))       # int between 1 and 10 (inclusive)
print(random.choice(["a","b","c"])) # random element
items = [1, 2, 3, 4, 5]
random.shuffle(items)              # shuffle in-place
print(items)
print(random.sample(items, 3))    # 3 unique random elements

# datetime
from datetime import datetime, date, timedelta

today = date.today()
print(today)              # 2024-01-15
print(today.year)
print(today.strftime("%B %d, %Y"))   # January 15, 2024

now = datetime.now()
print(now.strftime("%Y-%m-%d %H:%M:%S"))

one_week_later = today + timedelta(days=7)
print(one_week_later)

# os — operating system interaction
print(os.getcwd())                  # current working directory
print(os.path.join("folder", "file.txt"))  # path joining
print(os.path.exists("nonexistent.txt"))   # False
print(os.environ.get("PATH", "not set")[:50])  # env variable

# sys — Python interpreter info
print(sys.version)         # Python version
print(sys.platform)        # 'win32', 'linux', 'darwin'
# sys.exit(0)              # exit the program

# collections — specialized data structures
from collections import Counter, defaultdict, deque, OrderedDict

# Counter — count occurrences
words = ["apple", "banana", "apple", "cherry", "banana", "apple"]
count = Counter(words)
print(count)                    # Counter({'apple': 3, 'banana': 2, ...})
print(count.most_common(2))     # [('apple', 3), ('banana', 2)]

text = "hello world"
char_count = Counter(text)
print(char_count)

# defaultdict — dict with default values
dd = defaultdict(list)
dd["fruits"].append("apple")
dd["fruits"].append("banana")
dd["veggies"].append("carrot")
print(dd)

dd_int = defaultdict(int)
for char in "mississippi":
    dd_int[char] += 1
print(dd_int)

# deque — double-ended queue (efficient append/pop from both ends)
d = deque([1, 2, 3])
d.appendleft(0)   # O(1) — much faster than list.insert(0, ...)
d.append(4)
print(d)          # deque([0, 1, 2, 3, 4])
d.popleft()
d.pop()
print(d)          # deque([1, 2, 3])

# ── __name__ == "__main__" ─────────────────
# This block only runs when the file is executed directly,
# NOT when it's imported as a module.
if __name__ == "__main__":
    print("Running directly!")
    # Put test/demo code here
