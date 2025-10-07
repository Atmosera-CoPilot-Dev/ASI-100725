Use Copilot Chat 'Ask','Edit', or 'Agent' mode for the following prompts:

1) Add a function 'comb' that calcluates the combination of n and r using the formula:
C(n, r) = n! / (r! * (n - r)!)

2) To improve performance, make use of memoization to store previously computed factorials.

3) Implement the 'comb' function using the memoized 'fact' function.

4) Refactor into a class named 'Combinatorics' with static methods for 'fact', 'perm', and 'comb'.

5) Add xml documentation to the class and all methods.

6) Write a main function to demonstrate the usage of the 'Combinatorics' class and its methods.

7) Build and run the code to ensure it works as expected.

``` CPP
// combinatorics.cpp

#include <iostream>         // for std::cout
#include <cassert>          // for assert
#include <unordered_map>    // for std::unordered_map

/*
This example contains several global functions used in probability calculations.:
- a recursive implementation of a factorial function.
- a permutation function that calculates the permutation of n and r.
- a combination function that calculates the combination of n and r.
*/

/*
Define a factorial function 'fact' that takes an
unsigned integer 'n' and returns an unsigned long long.
The function will be recursive.

if n < 0 => return  -1
if n = 0 or n = 1 =>  return 1
n * fact(n - 1)
*/
unsigned long long fact(unsigned int n) {
    // Base case
    if (n < 0) {
        return -1;
    }
    if (n == 0 || n == 1) {
        return 1;
    }
    // Recursive case
    return n * fact(n - 1);
}

/*
Create a function 'perm' that calcluates the permutation of n and r using the formula:
P(n, r) = n! / (n - r)!
*/

unsigned int perm(unsigned int n, unsigned int r) {
    // Calculate permutation
    return fact(n) / fact(n - r);
}


```
