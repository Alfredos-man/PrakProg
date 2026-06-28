Alfred Riis Lykke

Question 6: Symmetric rank-1 update of a size-n symmetric eigenvalue problem 
"
The matrix A to diagonalize is given in the form
A = D +uuT,
where D is a diagonal matrix and u is a column-vector.
Given the diagonal elements of the matrix D and the elements of the vector u find the eigenvalues of the matrix A using only O(n2) operations (see section "Eigenvalues of updated matrix" in the book).
"

The problem here is that we are given a Diagonal matrix, D. In the code this is represented as a column vector. An example could be:
D = (1,3,1) = (1 0 0  
               0 3 0
               0 0 1) 

however this doest have to be written in code, since instead of constructing the full matrix, A, we can use the secular equation,