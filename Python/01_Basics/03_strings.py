# ─────────────────────────────────────────
#  STRINGS
# ─────────────────────────────────────────

s = "Hello, World!"

# ── Indexing & Slicing ────────────────────
print(s[0])       # H
print(s[-1])      # !
print(s[0:5])     # Hello
print(s[7:])      # World!
print(s[:5])      # Hello
print(s[::2])     # Hlo ol!  (every 2nd char)
print(s[::-1])    # !dlroW ,olleH  (reversed)

# ── Common Methods ────────────────────────
print(s.upper())            # HELLO, WORLD!
print(s.lower())            # hello, world!
print(s.strip())            # removes whitespace from both ends
print(s.replace("World", "Python"))  # Hello, Python!
print(s.split(", "))        # ['Hello', 'World!']
print(s.startswith("Hello"))  # True
print(s.endswith("!"))      # True
print(s.find("World"))      # 7  (index of first match)
print(s.count("l"))         # 3
print(len(s))               # 13

# ── String Formatting ─────────────────────
name, age = "Alice", 25

# f-string (recommended, Python 3.6+)
print(f"Name: {name}, Age: {age}")

# .format()
print("Name: {}, Age: {}".format(name, age))

# % formatting (old style)
print("Name: %s, Age: %d" % (name, age))

# ── Multiline Strings ─────────────────────
poem = """Roses are red,
Violets are blue,
Python is awesome,
And so are you!"""
print(poem)

# ── Escape Characters ─────────────────────
print("Tab:\there")
print("Newline:\nhere")
print("Quote: \"quoted\"")
print("Backslash: \\")

# ── Raw Strings (useful for regex/paths) ──
path = r"C:\Users\name\folder"
print(path)  # backslashes treated literally

# ── String Joining ────────────────────────
words = ["Python", "is", "fun"]
print(" ".join(words))   # Python is fun
print("-".join(words))   # Python-is-fun

# ── Check content ─────────────────────────
print("hello123".isalnum())   # True
print("hello".isalpha())      # True
print("123".isdigit())        # True
print("  ".isspace())         # True
