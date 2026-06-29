# Question 6: "Symmetric rank-1 update of a size-n symmetric eigenvalue problem"
Alfred Riis Lykke 


## Overview
The following code is made to find the eigenvalues of a matrix A on the form:
```
A = D + u*u^T
```

where D is a diagonal Matrix and u is a vector
This algorithm is meant to run in O(n^2) time.

When running "make", 2 things will happen:
1. The file Out.txt will be generated containing test of the algorithm on various cases 
2. A benchmark will begin to run the algorithm with increasing size starting from n=100 up to n=5000 with stepsize 100. This generates the file "benchmark.data" used to make a plot over the runtime.

## Method/theory

The eigenvalues are obtained by solving the secular equation as described in the book
$$
1 + \sum_{i=1}^{n} \frac{u_i^2}{d_i - \lambda} = 0
$$
The algorithm performs the following steps:

1. Sort the diagonal entries of D. 
2. Reorder the corresponding entries of u.
2. Use the interlacing property to determine an interval containing each eigenvalue.
3. Solve the secular equation in each interval using the bisection method.
4. Return the computed eigenvalues.

## Out.txt
The file Out.txt shows some testcases of this algorithm where the input d denotes the Diagonal matrix. For example d = 1 3 5 coresponds to the matrix: 
$$
D=
\begin{bmatrix}
1&0&0\\
0&3&0\\
0&0&5
\end{bmatrix}
$$
and u = 1 2 1 is:

$$
u=
\begin{bmatrix}
1&2&1\\
\end{bmatrix} ^T
$$
The found eigenvalues are written under "Eigenvalues"




## Benchmark.png
The plot, "benchmark.png" shows the scaling runtime of O(n^2). This is done by timing the runtime for a given n where the size of both matrixes is 
$$
D = (d_1 ... d_n) 
$$
and 
$$
u = (u_1 ... u_n)
$$
I then do a fit of this data using 
$$
f(n)=an^2
$$
where a is just a verry small number.

The plot shows that the runtime scales almost perfectly with O(n^2)
## Conclution
The rank-1 eigenvalue algoritm has been implimented as acording to the task and the book, and all points of the task has been concidered, along with a plot showing the intended runtime. 

score: 10/10

## AI Decleration: (Can also be found in "Extramateriale" on wiseflow)
AI dekleration: 
ChatGPT has been used to generate big parts of the code in the following files:
rank.h
rank.cpp
main.cpp
in the Makefile, ChatGPT has been used to make the ”plot:” rule




