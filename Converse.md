# 6/11/2026
### Session 1 (DSL 1)
Question 1:
1. Are you beginning on November 6, 2026?

2. Your previous array preparation: You mentioned that you completed array fundamentals yesterday. What exactly did you cover?

- Insertion and deletion?
    
- Array traversal and merging?
    
- Matrix operations?
    
- Address calculation and memory representation?
    
- Dynamic allocation?
    

3. C++ implementation confidence: How comfortable are you with these?
4. One important question: Have you previously implemented the Student Record Management experiment using a `Student` structure/class, or did you implement the financial matrix operations?

Answer 1: 
1. yes it is November 6, 2026, 12:06 PM
2. I can insert between and delete between an array, traverse an array, merge two arrays into a new merged array, i can perform matrix operations, address calculation is a bit sore but i think i can do it, yep mostly comfortable with dynamic allocation. 
3. 4, I am pretty much comfortable writing in cpp, just new with int** matrix and then declaring a for loop for initialization of rows in the constructor. Not very comfortable with operator overload for such a class if it is needed. 
4. I have implemented student record management, but i took my sweet time doing so. 

Answer 2: 
1. 4 times new is called, once for a array of pointer to int of size 3, and 3 times for array of int of size 4 each
2. int*
3. array of 2nd row 
4. if int is of 4 bytes then yes because `arr[0]` is array of contiguous memory locations, and `arr[0][2]` is just 2 elements after `arr[0][0]` 
5. once to delete the int array of each row, and after that delete int** array of pointers of int
6. both the shape of matrix must be same that is `row1 == row2 && col1 == col2`, because each element is added with its corresponding element. 
(I want to confess i dont know how to deal with the functions that return a class like Matrix add(const Matrix& A, const Matrix& B), i dont know if to keep this function as static function or not, i dont know if you return a heap pointer created inside the function call, or do you return directly a local object inside the function or i am not sure about anything related to this. Also how do we do this Matrix C = A.add(Matrix B), we can do this? keeping the function non static but then how do we return a reference to the object, it can be rvalue reference or not?? Make my confusions go away)

Answer 3: 
1. we can create a local class instance inside add, and when returned, due to the NRVO protocol, the object's resources are directly transfered to the lvalue, and the object's lifetime and scope ends with the function scope but the resources are now owned by C. Hence we do not need to allocate heap memory to the local variable to persist its resources after returning it. Also i am thinking that copy constructor is must because the local variables row, and col's value must be copied to the matrix C, which we have never defined if copy constructor is not defined, since compiler generates its own copy constructor if user does not, it might handle that (but explicit copy resolves the doubt ). 
2. const before the parameter Matrix& B guarentees that there is no modifications done to Matrix B through the reference, and the const after add(...) guarentees that the instance calling add will not be modified, that is add does not modify both the this object and passed object. 
3. if incase a object is created Matrix C(2, 2), and later we use C = A.add(B), then the matrix C's resource should handled explicitly, otherwise the returned object's resources and the C's existing resources collide, that is there is ambiguity on which resource to hold and how the values are copied from right to left. 