## TDD with DocTest in GNU C++

```
Create a DocTest unit test for a C++ class 'Employees'.
The class has a method 'HighEarners' that returns a list of employees who earn more than 100,000.
The Employee class has a name and a salary. The method should return a list of employees who earn more than 100,000.
Edge cases:
The test should include a test case where the list is empty, and another where the list has one employee. In both cases, the method should return an empty list.
The response must include the unit test and a sample Employees class with the HighEarners method.
```

```
Modify the Employees class to include a HighEarners method that accepts a function object or lambda strategy in the form: std::function<bool(double)>.
Update the unit test class EmployeesTests to test the modified HighEarners method.
```

```
Show me a folder structure for this project that includes the following:
- A main application project that uses the Employees class.
- A test project that uses DocTest to test the Employees class.
- A CMakeLists.txt file for each project.

```