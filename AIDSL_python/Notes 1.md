### Immutable objects
An immutable object cannot have its value changed after creation.
Examples:
- `int` 
- `float`
- `bool`
- `str`
- `tuple` (with an important qualification about mutable objects inside it)
- `frozenset`

### Mutable objects
A mutable object can be modified after creation.
Examples:
- `list`
- `dict`
- `set`
- Most user-defined class instances

### Call by object sharing (AKA call by assignment):
It is neither traditional call by value nor traditional call by reference.

### Operations that mutates or binds:

|Operation|What it does|
|---|---|
|`b.append(4)`|Modifies the object referenced by `b`|
|`b = [4, 5, 6]`|Creates a list and binds `b` to it|
|`b = a`|Binds `b` to the object currently referenced by `a`|
*here b.append(4) modifies the object pointed by b itself, but b = [4, 5, 6] or b = a binds b to different object depending on the right value* 
Assignment operator here rebinds the variable to other object, only here a new object can be created, but .append() works on the reference of the object pointed by b. 

### The object-tracing method
1. Identify object creation
    Which statements construct new objects?
    Examples: `[1, 2]`, `{}`, `list()`, `MyClass()`.
    
2. Track name bindings
    Which names refer to which objects?
    Examples: `b = a`, `x = y`.
    
3. Identify mutation versus rebinding
    Does the operation change an existing object, or change what a name refers to?
    Examples: `append()` versus `=`.
    
4. Check object lifetime    
    Are there still references to the object? If not, it may become eligible for garbage collection.

### Create a copy to avoid accidental modifications to the parameters

This is probably the most practical technique when you need to protect the caller's list from accidental modification.
```python
def process(numbers):
    numbers = numbers.copy()

    numbers.append(100)

data = [1, 2, 3]

process(data)

print(data)
```

```Output
[1, 2, 3]
```

**But beware: `.copy()` makes a shallow copy.**

Consider: 
```python
data = [[1, 2], [3, 4]]

def process(numbers):
    numbers = numbers.copy()
    numbers[0].append(100)

process(data)

print(data)
```

```Output
[[1, 2, 100], [3, 4]]
```

Why? The outer list was copied, but the inner lists are still shared.
For nested structures, `copy.deepcopy()` can create an independent deep copy:

```python
import copy

numbers = copy.deepcopy(numbers)
```

**Deep copying has additional time and memory costs, and isn't suitable for every object.**


