## Instructions to create an app using Agentive AI (.NET C#) (Single Project, Separate Utility Files, SOLID Compliant)

Goal: Build a console application that reads up to 10 numbers (terminated early by entering -1) and outputs each number along with its square and cube. The design must follow SOLID principles and allow easy extension with new mathematical operations via additional provider classes.

(Instructions)

1. Scaffold the project structure and files as described below. NUnit tests should be included in the scaffolding. Do not write any code until the structure is in place.

2. Initialize (or overwrite) a console project for the application using the standard .NET console template.

3. Confirm that the project contains a Program file. Keep it minimal (an empty Main entry point is fine) until after the interface and provider classes are created to avoid unresolved reference errors.

4. Use a single root namespace named Lambda for all source files. Create a folder named Functions at the project root; place utility/provider abstractions and implementations there under the sub-namespace Lambda.Functions.

5. Inside the Functions folder, define an interface named IFunctionProvider that exposes:
   - A read-only string property representing a human-friendly name of the function (Name).
   - A method that returns a delegate taking a double and returning a double (think: transformation function).
   This interface is the abstraction the main program will depend on.

6. Still inside the Functions folder, create two separate classes implementing the interface:
   - SquareFunctionProvider: returns a delegate computing the square of its input.
   - CubeFunctionProvider: returns a delegate computing the cube of its input.
   Each class should do only one thing (single responsibility) and should not perform I/O.

7. After the interface and the two provider classes exist and are saved, update the Program file to:
   - Add the necessary using directives for core collections and for the Functions namespace.
   - Allocate a collection to store up to 10 user-entered real numbers, stopping early if the user enters the sentinel value -1 (do not store the sentinel).
   - Re-prompt on invalid numeric input without incrementing the stored count.
   - Create a list of the provider interface type, adding both provider instances.
   - Build a list of transformation delegates by invoking the retrieval method on each provider.
   - For each entered number, compute and display: original value, its square, and its cube. Align the numeric columns for readability (for example, by using consistent width formatting or padding).
   - If the user enters no values before the sentinel, display a short exit message.

8. Ensure the output is readable and columns are vertically aligned (e.g., right-aligned numbers of uniform width for original, square, and cube). No additional decoration is required.

9. Add or update a .gitignore file in the project root so that build artifacts, IDE folders, user-specific files, logs, and temporary files are excluded. Minimum entries: build output directories, IDE metadata, user preference files, log files, and temporary files.

10. Build then run the application (save all files first) using either the command line or the IDE build/run actions.

(End of Instructions)