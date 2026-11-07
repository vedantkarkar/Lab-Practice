### Python Function call operation:
```python
def calculate(a, b):
    result = a + b
    return result

x = 10
y = 20

answer = calculate(x, y)
print(answer)
```
When Python encounters `answer = calculate(x, y)`, Conceptually, it performs the following operations:
1. Finds the function object associated with `calculate`.
2. Evaluates the arguments `x` and `y`.
3. Creates a new execution context for this function call.
4. Binds the parameter names `a` and `b` to the argument objects.
5. Executes the function body.
6. Evaluates the return expression.
7. Returns the result to the caller.
8. Finishes the function's execution context.

### Scope
**Namespace:** 
A namespace is essentially a mapping between names and objects.
There are two distinct namespaces involved.
local and global namespace.
```python
def calculate(a, b):
    result = a + b

    print("Inside function:")
    print(locals())

    return result


x = 10
y = 20

answer = calculate(x, y)

print("Outside function:")
print(globals().get("x"))
print(globals().get("y"))
```
Two useful built-in functions:
- `locals()` — returns a mapping representing the current local namespace.
- `globals()` — returns the module's global namespace.

### Execution Frame
Every active function call has an associated execution frame.
Think of a frame as the execution record for a particular function invocation.

It contains information needed to continue executing that invocation, such as:
- Local variable bindings.
- References to the function's global and built-in namespaces.
- The current execution position.
- Evaluation state and other interpreter bookkeeping.

### LEGB rule:

| Order | Scope     | Meaning                     |
| ----- | --------- | --------------------------- |
| L     | Local     | Current function            |
| E     | Enclosing | Outer function, if nested   |
| G     | Global    | Current module              |
| B     | Built-in  | Python's built-in namespace |
Python searches these scopes in that order.

