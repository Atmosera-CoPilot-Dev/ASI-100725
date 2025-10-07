
Use the Agent mode to perform all steps.

## Instructions to create an app using Agentive AI (GNU C++)

1. Create a new C++ file named `main.cpp` in the current directory.

2. At the top, include the necessary headers for input/output and collections:
   - `#include <iostream>`
   - `#include <vector>`
   - `#include <functional>`

3. Define a namespace `Lambda` and place all code inside it.

4. Inside the namespace, create a struct or class `LambdaGen` and place the following methods inside it:
   - `SqrGen`: Returns a `std::function<double(double)>` that squares a double argument.
   - `CubeGen`: Returns a `std::function<double(double)>` that cubes a double argument.

5. In the `main` function:
   - Declare a `std::vector<std::function<double(double)>>` to store functions matching the signatures of `SqrGen` and `CubeGen`.
   - Prompt the user to enter up to 10 real numbers, stopping if the user enters -1.
   - Store the input numbers in a `std::vector<double>`.
   - Add the `SqrGen` and `CubeGen` functions to the function list.
   - For each input number, print its value, its square, and its cube in a formatted row (e.g., `n: 2.5   Squared: 6.25    Cubed: 15.625`).

6. Create a Makefile for the program, add a `.gitignore` file to exclude unnecessary files, then build and run the program in a Bash terminal.
