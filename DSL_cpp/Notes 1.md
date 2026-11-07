**When you use raw pointers, always define a deep copy constructor as when we do `class obj = other`, now the obj and other share same memory locations for shallow copy, and results in double-free bug after scope ends**
RVO = Return Value Optimization (RVO)
NVRO = Named Return Value Optimization (NRVO)
## 10. Rule of Three: the minimum you need

If a class manually manages a resource through a raw pointer, it generally needs three special member functions:

1. Destructor — releases the resource.
    
2. Copy constructor — creates an independent copy.
    
3. Copy assignment operator — safely replaces an object's existing resource.
    

The copy constructor must perform a deep copy.

For example:

```
Matrix(const Matrix& other) {
    rows = other.rows;
    cols = other.cols;

    arr = new int*[rows];

    for (int i = 0; i < rows; i++) {
        arr[i] = new int[cols];

        for (int j = 0; j < cols; j++) {
            arr[i][j] = other.arr[i][j];
        }
    }
}
```

Now:

```
Matrix A(2, 2);
Matrix B = A;
```
## 15. Implementing safe copy assignment

In here we have to modify this object with the parameter's data, without sharing memory allocations

Let's implement a robust approach called copy-and-swap.

First, we need a small helper:

```
void swap(Matrix& other) {
    int** tempArr = arr;
    arr = other.arr;
    other.arr = tempArr;

    int tempRows = rows;
    rows = other.rows;
    other.rows = tempRows;

    int tempCols = cols;
    cols = other.cols;
    other.cols = tempCols;
}
```

Now the assignment operator:

```
Matrix& operator=(const Matrix& other) {
    if (this == &other) {
        return *this;
    }

    Matrix temp(other);  // Deep copy using copy constructor

    swap(temp);          // Exchange resources

    return *this;
}
```

Let's understand why this works.

1. `Matrix temp(other)` creates an independent copy.
    
2. `swap(temp)` gives C the newly allocated memory.
    
3. `temp` now owns C's old memory.
    
4. When `temp` goes out of scope, its destructor releases that old memory.
    
5. `return *this` returns a reference to the existing C object.


## Changes Suggested: 
1.  One improvement: validate that `r` and `c` are positive before allocating. A negative dimension can convert into a very large allocation size.
```cpp
Matrix(int r, int c) : row(r), col(c)
{
    arr = new int *[row];
    for (int i = 0; i < row; i++)
    {
        arr[i] = new int[col];
    }
}
```
2.  One small improvement: make `swap()` a `noexcept` member function if you're using a C++11-or-newer compiler. It only exchanges pointers and integers, so it cannot throw.
   ```cpp
Matrix &operator=(const Matrix &other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    Matrix temp(other);
    swap(temp);

    return *this;
}
   ```
3. A few improvements: 
	1. Make `show()` const
	   change to: 
		```void show() const```
	2. Use initializer lists in the copy constructor
	   ```cpp
	   Matrix(const Matrix &other)
		{
		    row = other.row;
		    col = other.col;
		    ...
		}
	   ```
	   change to: 
	   ```cpp
	   Matrix(const Matrix &other)
    : row(other.row), col(other.col)
		{}
	   ```
	   3. Validate dimensions
	      Your constructor should reject invalid dimensions.
	      Conceptually:
	      ```cpp
	      if (r <= 0 || c <= 0){
			throw "Invalid matrix dimensions"; }
	      ```

## Program class improvements: 
1.  Prevent accidental copying of `Program`
	Your `Program` class owns dynamically allocated matrices:
	
	```
	Matrix *matrices[capacity];
	```
	
	If someone writes:
	
	```
	Program A;
	Program B = A;
	```
	
	the compiler-generated copy constructor copies the pointers, not the actual matrices. Both objects would attempt to delete the same matrices.

	Since your program doesn't need to copy a `Program`, the simplest solution is to prohibit copying:
	```
	Program(const Program&) = delete;
	Program& operator=(const Program&) = delete;
	```
	This is a good example of designing an ownership contract explicitly.
	
2. Give each `switch` case its own scope: 
   ```cpp
switch (ch)
{
case 1:
{
    int r, c;
    // Create matrix
    break;
}
case 2:
{
    int no;
    // Display matrix
    break;
}
case 3:
{
    int no;
    // Transpose
    break;
}
case 4:
{
    int no, no2;
    // Addition
    break;
}
case 5:
    // Exit
    break;
default:
    cout << "Invalid choice\n";
}
   ```
   3. 