Use Copilot Chat 'Ask','Edit', or 'Agent' mode for the following prompts:

1) Add a method 'comb' to generate the count of combinations.

2) Refactor the revised class to make use of memoization.

3) Add xml documentation to the class and all methods.

4) Translate the class into C++. I want the implementation separate from the definition.

``` CSharp
/*
This file contains a class that provides operations in the mathematical field of combinatorics.
*/

namespace MathFun
{

    public class Combinatorics
    {
        /*
        define a public method named 'fact' that takes an unsigned integer 'n' and returns the factorial of 'n' using recursion:
        Implementation details:

        if n is less than or equal to 1, return 1
        return n * fact(n - 1)
        */
        public static ulong fact(uint n)
        {
            if (n <= 1)
            {
                return 1;
            }
            return n * fact(n - 1);
        }

        /*
        Define a public method named 'perm' that takes two unsigned integers 'n' and 'r' and returns the permutation of 'n' and 'r':
        Implementation details:

        The permutation of 'n' and 'r' is defined as n! / (n - r)!
        */
        public static ulong perm(uint n, uint r)
        {
            return fact(n) / fact(n - r);
        }


  
    }

}

```


