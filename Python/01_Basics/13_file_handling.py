# ─────────────────────────────────────────
#  FILE HANDLING
# ─────────────────────────────────────────

# ── Write to a file ───────────────────────
with open("example.txt", "w") as f:
    f.write("Hello, World!\n")
    f.write("Python file handling is easy.\n")
    f.writelines(["Line 3\n", "Line 4\n"])

# 'with' automatically closes the file — always use it

# ── Read entire file ──────────────────────
with open("example.txt", "r") as f:
    content = f.read()
    print(content)

# ── Read line by line ─────────────────────
with open("example.txt", "r") as f:
    for line in f:
        print(line.strip())   # strip() removes trailing newline

# ── Read all lines into a list ────────────
with open("example.txt", "r") as f:
    lines = f.readlines()
    print(lines)   # ['Hello, World!\n', ...]

# ── Read one line at a time ───────────────
with open("example.txt", "r") as f:
    first_line = f.readline()
    second_line = f.readline()
    print(first_line.strip())
    print(second_line.strip())

# ── Append to file ────────────────────────
with open("example.txt", "a") as f:
    f.write("Appended line\n")

# ── File modes ────────────────────────────
# "r"  — read (default), file must exist
# "w"  — write, creates or overwrites
# "a"  — append, creates or adds to end
# "x"  — exclusive create, fails if file exists
# "rb" — read binary
# "wb" — write binary
# "r+" — read and write

# ── Check if file exists ──────────────────
import os

if os.path.exists("example.txt"):
    print("File exists")
    print(f"Size: {os.path.getsize('example.txt')} bytes")

# ── File/Directory operations ─────────────
print(os.getcwd())             # current working directory
# os.makedirs("new_dir", exist_ok=True)  # create directory
# os.rename("old.txt", "new.txt")        # rename file
# os.remove("example.txt")              # delete file
# os.rmdir("empty_dir")                 # delete empty directory

# ── Working with paths (use pathlib in modern Python) ─
from pathlib import Path

p = Path("example.txt")
print(p.exists())       # True
print(p.stem)           # example  (name without extension)
print(p.suffix)         # .txt
print(p.name)           # example.txt
print(p.parent)         # . (current directory)
print(p.absolute())     # full absolute path

# Create a path
data_path = Path("data") / "output" / "results.csv"
print(data_path)   # data/output/results.csv

# ── JSON files ────────────────────────────
import json

data = {"name": "Alice", "age": 25, "scores": [90, 85, 92]}

# Write JSON
with open("data.json", "w") as f:
    json.dump(data, f, indent=2)

# Read JSON
with open("data.json", "r") as f:
    loaded = json.load(f)
    print(loaded["name"])   # Alice

# ── CSV files ─────────────────────────────
import csv

rows = [["Name", "Age", "City"],
        ["Alice", "25", "NYC"],
        ["Bob", "30", "LA"]]

with open("people.csv", "w", newline="") as f:
    writer = csv.writer(f)
    writer.writerows(rows)

with open("people.csv", "r") as f:
    reader = csv.DictReader(f)
    for row in reader:
        print(row["Name"], row["Age"])

# ── Cleanup example files ─────────────────
import os
for fname in ["example.txt", "data.json", "people.csv"]:
    if os.path.exists(fname):
        os.remove(fname)
