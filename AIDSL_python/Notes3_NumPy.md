# NumPy — Quick Reference Notes

## 1. Creating and Inspecting Arrays

```
import numpy as np

# Create a Python list
python_list = [10, 20, 30, 40, 50]

# Create a NumPy array
numpy_array = np.array(python_list)

print("Python list:", python_list)
print("NumPy array:", numpy_array)

print("\nArray properties:")
print("Dimensions:", numpy_array.ndim)
print("Shape:", numpy_array.shape)
print("Size:", numpy_array.size)
print("Data type:", numpy_array.dtype)
print("Item size:", numpy_array.itemsize)
print("Total bytes:", numpy_array.nbytes)
```

|Property|Purpose|
|---|---|
|`ndim`|Number of dimensions (axes)|
|`shape`|Number of elements along each dimension|
|`size`|Total number of elements|
|`dtype`|Data type of array elements|
|`itemsize`|Bytes occupied by one element|
|`nbytes`|Total bytes occupied by the element data buffer|

**Note:** `nbytes` does not include the complete memory overhead of the ndarray object.

## 2. Creating Specific Arrays

|Function|Purpose|Example|
|---|---|---|
|`np.zeros()`|Creates an array filled with zeros|`np.zeros((2, 3))`|
|`np.ones()`|Creates an array filled with ones|`np.ones((3, 2))`|
|`np.full()`|Fills an array with a specified value|`np.full((2, 2), 7)`|
|`np.arange()`|Creates values over a range with a step|`np.arange(0, 10, 2)`|
|`np.linspace()`|Creates a specified number of evenly spaced values|`np.linspace(0, 10, 5)`|
|`np.eye()`|Creates an identity matrix|`np.eye(3)`|

**Difference between** `**arange()**` **and** `**linspace()**`**:**

- `arange(start, stop, step)` specifies the interval between elements. The stop value is excluded.
    
- `linspace(start, stop, num)` specifies the number of evenly spaced elements. The endpoint is included by default.
    

## 3. Data Types (dtype)

A NumPy numerical array generally stores homogeneous, fixed-type elements in a contiguous data buffer.

Specify the data type during initialization:

```
a = np.array([1, 2, 3], dtype=np.float32)
```

Alternatively, convert an existing array:

```
b = a.astype(np.float64)
```

`astype()` returns a new converted array by default, leaving the original array unchanged.

**Memory consideration:**

- `float32` → 4 bytes per element.
    
- `float64` → 8 bytes per element.
    

Use an appropriate data type based on memory requirements and numerical precision.

## 4. NumPy Operations

### 4.1 Arithmetic Operators (Element-wise)

NumPy performs arithmetic operations element-wise by default.

```
A = np.array([10, 20, 30])
B = np.array([5, 5, 5])

print(A + B)   # Addition
print(A - B)   # Subtraction
print(A * B)   # Multiplication
print(A / B)   # Division
print(A ** 2)  # Exponentiation
```

Corresponding elements are operated on individually. Arrays must have compatible shapes, either identical or broadcastable.

### 4.2 Broadcasting

Broadcasting allows NumPy to perform operations between arrays of compatible but potentially different shapes, without manually replicating data.

**Compatibility rule:**

Compare dimensions from right to left. Two dimensions are compatible if:

1. They are equal, or
    
2. One of them is `1`.
    

Missing leading dimensions are treated as `1`.

Example:

```
A = np.array([
    [10, 20, 30],
    [40, 50, 60]
])

B = np.array([1, 2, 3])

print(A + B)
```

Shapes:

```
A: (2, 3)
B:    (3)
   -------
   (2, 3)
```

Output:

```
[[11 22 33]
 [41 52 63]]
```

Broadcasting also works with shapes `(3, 1)` and `(1, 4)`, producing a result of shape `(3, 4)`.

**Use:** Applying scalar values, offsets, or transformations across entire arrays efficiently.

### 4.3 Matrix Multiplication

Element-wise multiplication and matrix multiplication are different operations.

```
A * B   # Element-wise multiplication
A @ B   # Matrix multiplication
```

For matrices:

```
A: (m, n)
B: (n, p)
Result: (m, p)
```

The inner dimensions must match.

Matrix multiplication follows the row-by-column dot product rule.

## 5. Mathematical Functions (Element-wise)

```
a = np.array([1, 4, 9, 16])

print(np.sqrt(a))
print(np.exp(a))
print(np.log(a))
print(np.sin(a))
```

Other useful functions:

|Function|Purpose|
|---|---|
|`np.abs()`|Absolute value|
|`np.round()`|Rounding|
|`np.floor()`|Round down|
|`np.ceil()`|Round up|
|`np.maximum()`|Element-wise maximum|
|`np.minimum()`|Element-wise minimum|

These functions operate on individual array elements.

## 6. Statistical Functions

```
print(np.sum(marks))
print(np.mean(marks))
print(np.median(marks))
print(np.min(marks))
print(np.max(marks))
print(np.std(marks))
print(np.var(marks))
```

|Function|Purpose|
|---|---|
|`np.sum()`|Sum of elements|
|`np.mean()`|Arithmetic mean|
|`np.median()`|Median|
|`np.min()`|Minimum value|
|`np.max()`|Maximum value|
|`np.std()`|Standard deviation|
|`np.var()`|Variance|

### Axis-based Operations

For a 2D array where rows represent students and columns represent subjects:

- `axis=0` → Operates down the rows; produces one result per column.
    
- `axis=1` → Operates across the columns; produces one result per row.
    
- No axis specified → Operates on the entire array and returns a single aggregate value.
    

Example:

```
marks = np.array([
    [80, 70, 90],
    [60, 85, 75],
    [90, 95, 80]
])

print(np.mean(marks, axis=0))  # Average per subject
print(np.mean(marks, axis=1))  # Average per student
print(np.mean(marks))          # Overall average
```

## 7. NumPy Transformations and Memory Sharing

### 7.1 Indexing and Slicing

Access individual elements using their indices:

```
arr = np.array([10, 20, 30, 40, 50])

print(arr[0])    # First element
print(arr[-1])   # Last element
```

Slicing syntax:

```
array[start:stop:step]
```

The stop index is excluded.

```
print(arr[1:4])   # [20 30 40]
print(arr[:3])    # First three elements
print(arr[::2])   # Every second element
print(arr[::-1])  # Reverse array
```

For multidimensional arrays:

```
matrix[row_index, column_index]
```

Use `:` to select an entire row or column.

```
matrix[1, :]   # Entire second row
matrix[:, 1]   # Entire second column
```

### 7.2 Reshaping

`reshape()` changes the dimensions of an array without changing its total number of elements.

```
arr = np.arange(1, 13)

matrix = arr.reshape(3, 4)
print(matrix)
```

The original and new shapes must have the same total number of elements.

`-1` allows NumPy to automatically infer one dimension:

```
arr.reshape(3, -1)
```

### 7.3 Views vs Copies

**View:**

- A new ndarray object that references the same underlying data buffer.
    
- Changes made through a view can affect the original array.
    
- Basic slicing generally returns views.
    

**Copy:**

- Creates an independent array with its own data buffer.
    
- Changes to the copy do not affect the original.
    
- Use `.copy()` to explicitly create a copy.
    

Example:

```
arr = np.array([10, 20, 30, 40, 50])

view = arr[1:4]
copy_arr = arr[1:4].copy()

view[0] = 999

print(arr)       # Original is modified
print(copy_arr)  # Independent data
```

Check whether two arrays share memory:

```
np.shares_memory(arr, view)
```

Returns `True` if they share at least one memory location.

**Important:** Basic slicing generally produces views, while advanced indexing generally produces copies. Reshaping can return a view when the memory layout permits it, otherwise a copy may be necessary.

### 7.4 Flattening and Raveling

Both convert a multidimensional array into a 1D array.

```
matrix = np.array([[1, 2], [3, 4]])

a = matrix.flatten()
b = matrix.ravel()
```

- `flatten()` always returns a copy.
    
- `ravel()` returns a view when possible, otherwise a copy.
    

### 7.5 Random Number Generation

Use NumPy's modern random number generator:

```
rng = np.random.default_rng(42)

print(rng.random((2, 3)))      # Random floats in [0, 1)
print(rng.integers(1, 10, 5)) # Five integers from 1 to 9
```

A seed such as `42` makes the random sequence reproducible.

**Applications:** Simulations, randomized experiments, sampling, and machine learning.