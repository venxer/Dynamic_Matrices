HOMEWORK 3: MATRIX CLASS


NAME:  < Edwin Zhao >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

<https://www.geeksforgeeks.org/
https://www.w3schools.com/
https://cplusplus.com/
Florence Wang>

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 13hr >



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

O(1)
get

O(1)
set

O(1)
num_rows

O(N)
get_column

O(N^2)
operator<<

O(N^2)
quarter

O(N^2)
operator==

O(N^2)
operator!=

O(1)
swap_rows

O(m^2 n)
rref (provided in matrix_main.cpp)



TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?
I used Dr.Memory, Valgrind, as well as lldb to check for memory leaks. 
I also used print statements in each step of my function(s) to debug where the
function is reaching and cannot reach. (any irregularities) Corner cases
were tested in student test with corner case arguements. 

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

