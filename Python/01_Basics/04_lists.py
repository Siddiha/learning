# ─────────────────────────────────────────
#  LISTS  (ordered, mutable, allows duplicates)
# ─────────────────────────────────────────

fruits = ["apple", "banana", "cherry"]

# ── Access ────────────────────────────────
print(fruits[0])    # apple
print(fruits[-1])   # cherry
print(fruits[1:3])  # ['banana', 'cherry']

# ── Modify ────────────────────────────────
fruits[1] = "blueberry"
print(fruits)       # ['apple', 'blueberry', 'cherry']

# ── Add ───────────────────────────────────
fruits.append("mango")          # add to end
fruits.insert(1, "avocado")     # insert at index
fruits.extend(["kiwi", "plum"]) # add multiple items
print(fruits)

# ── Remove ────────────────────────────────
fruits.remove("mango")    # remove by value (first occurrence)
popped = fruits.pop()     # remove & return last item
popped2 = fruits.pop(0)   # remove & return item at index
del fruits[0]             # delete by index
print(fruits)

# ── Search & Sort ─────────────────────────
nums = [3, 1, 4, 1, 5, 9, 2, 6]
print(nums.index(4))      # 2  — index of first occurrence
print(nums.count(1))      # 2  — count of value

nums.sort()               # in-place sort (ascending)
print(nums)

nums.sort(reverse=True)   # descending
print(nums)

sorted_copy = sorted(nums)  # returns new list, original unchanged
print(sorted_copy)

nums.reverse()            # reverse in-place
print(nums)

# ── Copy ──────────────────────────────────
original = [1, 2, 3]
shallow = original.copy()   # or list(original) or original[:]
shallow.append(4)
print(original)    # [1, 2, 3] — unaffected
print(shallow)     # [1, 2, 3, 4]

# ── List Comprehension ────────────────────
squares = [x**2 for x in range(1, 6)]
print(squares)      # [1, 4, 9, 16, 25]

evens = [x for x in range(10) if x % 2 == 0]
print(evens)        # [0, 2, 4, 6, 8]

# ── Nested Lists (2D) ─────────────────────
matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
print(matrix[1][2])  # 6

# Flatten a 2D list
flat = [num for row in matrix for num in row]
print(flat)   # [1, 2, 3, 4, 5, 6, 7, 8, 9]

# ── Useful Functions ──────────────────────
nums2 = [4, 7, 2, 9, 1]
print(len(nums2))   # 5
print(min(nums2))   # 1
print(max(nums2))   # 9
print(sum(nums2))   # 23
