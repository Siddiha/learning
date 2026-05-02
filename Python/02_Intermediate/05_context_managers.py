# ─────────────────────────────────────────
#  CONTEXT MANAGERS  (with statement)
# ─────────────────────────────────────────
# Guarantees setup/teardown even if an exception occurs.
# Most common use: file handling, DB connections, locks.

# ── Standard usage ────────────────────────
with open("temp.txt", "w") as f:
    f.write("Hello\n")
# File is automatically closed here — even if an exception occurred

# ── Multiple context managers ─────────────
with open("temp.txt", "r") as src, open("temp_copy.txt", "w") as dst:
    dst.write(src.read())

# ── Class-based Context Manager ───────────
# Implement __enter__ and __exit__

class Timer:
    import time

    def __enter__(self):
        import time
        self._start = time.time()
        return self   # value bound to 'as' variable

    def __exit__(self, exc_type, exc_val, exc_tb):
        import time
        elapsed = time.time() - self._start
        print(f"Elapsed: {elapsed:.4f}s")
        return False   # False = don't suppress exceptions

with Timer() as t:
    total = sum(range(1_000_000))
print(f"Sum: {total}")

# ── contextlib.contextmanager decorator ───
from contextlib import contextmanager
import time

@contextmanager
def timer(label=""):
    start = time.time()
    try:
        yield   # everything before yield = __enter__
    finally:
        elapsed = time.time() - start
        print(f"{label} took {elapsed:.4f}s")

with timer("Loop"):
    _ = [x**2 for x in range(100_000)]

# ── Managed resource example ──────────────
@contextmanager
def managed_resource(name):
    print(f"Acquiring {name}")
    resource = {"name": name, "active": True}
    try:
        yield resource
    except Exception as e:
        print(f"Error during {name}: {e}")
        raise
    finally:
        resource["active"] = False
        print(f"Released {name}")

with managed_resource("database connection") as conn:
    print(f"Using {conn['name']}")

# ── suppress — silently ignore exceptions ─
from contextlib import suppress

with suppress(FileNotFoundError):
    open("nonexistent.txt")

print("Continued after suppressed exception")

# ── redirect_stdout ────────────────────────
from contextlib import redirect_stdout
import io

buffer = io.StringIO()
with redirect_stdout(buffer):
    print("This goes to buffer, not console")

output = buffer.getvalue()
print(f"Captured: {output.strip()}")

# Cleanup
import os
for f in ["temp.txt", "temp_copy.txt"]:
    if os.path.exists(f):
        os.remove(f)
