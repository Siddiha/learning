# ─────────────────────────────────────────
#  DICTIONARIES  (key-value pairs, ordered in 3.7+, mutable)
# ─────────────────────────────────────────

person = {
    "name": "Alice",
    "age": 25,
    "city": "NYC"
}

# ── Access ────────────────────────────────
print(person["name"])           # Alice
print(person.get("age"))        # 25
print(person.get("email"))      # None  (no KeyError!)
print(person.get("email", "N/A"))  # N/A  (default value)

# ── Add / Update ──────────────────────────
person["email"] = "alice@example.com"   # add new key
person["age"] = 26                      # update existing key
person.update({"city": "LA", "job": "Dev"})  # update multiple
print(person)

# ── Remove ────────────────────────────────
removed = person.pop("email")         # remove & return value
del person["job"]                     # delete key
person.popitem()                      # remove last inserted pair
print(person)

# ── Check Key Exists ──────────────────────
print("name" in person)    # True
print("email" in person)   # False

# ── Iterate ───────────────────────────────
scores = {"math": 90, "science": 85, "english": 92}

for key in scores:                   # iterate keys
    print(key)

for value in scores.values():        # iterate values
    print(value)

for key, value in scores.items():    # iterate key-value pairs
    print(f"{key}: {value}")

# ── Keys, Values, Items ───────────────────
print(scores.keys())    # dict_keys(['math', 'science', 'english'])
print(scores.values())  # dict_values([90, 85, 92])
print(scores.items())   # dict_items([...])

# ── Dict Comprehension ────────────────────
squared = {x: x**2 for x in range(1, 6)}
print(squared)   # {1: 1, 2: 4, 3: 9, 4: 16, 5: 25}

filtered = {k: v for k, v in scores.items() if v >= 90}
print(filtered)  # {'math': 90, 'english': 92}

# ── Nested Dictionary ─────────────────────
students = {
    "alice": {"grade": "A", "score": 95},
    "bob": {"grade": "B", "score": 82},
}
print(students["alice"]["score"])   # 95

# ── Merge Dicts (Python 3.9+) ─────────────
d1 = {"a": 1, "b": 2}
d2 = {"b": 99, "c": 3}
merged = d1 | d2        # d2 values win on conflict
print(merged)           # {'a': 1, 'b': 99, 'c': 3}

# Older way (works in all Python 3 versions)
merged_old = {**d1, **d2}
print(merged_old)
