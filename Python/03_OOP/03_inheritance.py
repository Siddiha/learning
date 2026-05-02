# ─────────────────────────────────────────
#  INHERITANCE
# ─────────────────────────────────────────
# Child class inherits attributes and methods from parent class.
# Promotes code reuse and establishes "is-a" relationships.

# ── Single Inheritance ────────────────────
class Animal:
    def __init__(self, name, age):
        self.name = name
        self.age = age

    def eat(self):
        return f"{self.name} is eating"

    def sleep(self):
        return f"{self.name} is sleeping"

    def speak(self):
        return f"{self.name} makes a sound"

    def __str__(self):
        return f"{type(self).__name__}(name={self.name}, age={self.age})"


class Dog(Animal):   # Dog inherits from Animal
    def __init__(self, name, age, breed):
        super().__init__(name, age)   # call parent __init__
        self.breed = breed

    def speak(self):   # override parent method
        return f"{self.name} says: Woof!"

    def fetch(self):   # new method
        return f"{self.name} fetches the ball!"


class Cat(Animal):
    def __init__(self, name, age, indoor=True):
        super().__init__(name, age)
        self.indoor = indoor

    def speak(self):
        return f"{self.name} says: Meow!"

    def purr(self):
        return f"{self.name} purrs..."


dog = Dog("Buddy", 3, "Labrador")
cat = Cat("Whiskers", 5)

print(dog.eat())       # inherited from Animal
print(dog.speak())     # Buddy says: Woof! — overridden
print(dog.fetch())     # new method
print(cat.speak())     # Whiskers says: Meow!
print(cat.purr())      # new method

print(isinstance(dog, Dog))     # True
print(isinstance(dog, Animal))  # True — dog IS an Animal
print(isinstance(cat, Dog))     # False

# ── Multi-level Inheritance ───────────────
class GuideDog(Dog):
    def __init__(self, name, age, breed, owner):
        super().__init__(name, age, breed)
        self.owner = owner

    def guide(self):
        return f"{self.name} guides {self.owner} safely"

    def speak(self):
        parent_sound = super().speak()   # call Dog's speak
        return f"{parent_sound} (trained)"

guide = GuideDog("Rex", 4, "German Shepherd", "John")
print(guide.guide())
print(guide.speak())   # calls Dog.speak() internally
print(guide.eat())     # from Animal — 3 levels up

# ── Multiple Inheritance ──────────────────
class Swimmer:
    def swim(self):
        return f"{self.name} is swimming"

class Runner:
    def run(self):
        return f"{self.name} is running"

class Duck(Animal, Swimmer, Runner):
    def speak(self):
        return f"{self.name} says: Quack!"

duck = Duck("Donald", 2)
print(duck.speak())   # Quack!
print(duck.swim())    # Donald is swimming
print(duck.run())     # Donald is running

# ── MRO — Method Resolution Order ─────────
print(Duck.__mro__)
# (Duck, Animal, Swimmer, Runner, object)
# Python searches left to right, then up

# ── super() in multiple inheritance ───────
class A:
    def greet(self):
        return "A"

class B(A):
    def greet(self):
        return "B → " + super().greet()

class C(A):
    def greet(self):
        return "C → " + super().greet()

class D(B, C):
    def greet(self):
        return "D → " + super().greet()

d = D()
print(d.greet())   # D → B → C → A
print(D.__mro__)   # D, B, C, A, object

# ── Check inheritance ─────────────────────
print(issubclass(Dog, Animal))    # True
print(issubclass(Dog, Cat))       # False
print(issubclass(Dog, object))    # True — everything inherits from object
