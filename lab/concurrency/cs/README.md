# Concurrent Data Structures Lab (with Copilot)

## Lab Goal
Enhance the C# app following the suggested steps below. Use GitHub Copilot to help you make each change.

---

## Getting Started
1. Open the solution in the `App` folder.
2. Review the code in `Program.cs`, `TradeDayProcessor.cs`, and `TradeDay.cs`.
3. Familiarize yourself with the data in `DowJones.csv`.

---

## Suggested Copilot Prompts
Use the prompts similar to the following (one at a time) to guide Copilot in making the required changes. You can copy/paste these into Copilot Chat or use your own wording.

### 1. Add a Producer Task
- "Add a BlockingCollection<TradeDay> to TradeDayProcessor and implement a method to generate TradeDay objects from the CSV file, adding them to the collection."
- "Create a Task to run the generator method and start it in the Start method."

### 2. Add Consumer Tasks
- "Add a List<Task<int>> to hold consumer tasks in TradeDayProcessor."
- "Implement a method that consumes TradeDay objects from the BlockingCollection, counts those matching a predicate, and returns the count."
- "Start multiple consumer tasks in the Start method, as specified by the constructor argument."

### 3. Aggregate Results
- "Implement a method to wait for all tasks to finish and sum the results from the consumer tasks. Handle exceptions appropriately."

### 4. Add Cancellation Support
- "Add support for CancellationToken in TradeDayProcessor and its tasks."
- "Implement a Canceller method in Program.cs that cancels processing when the user presses Enter."
- "Update the Start method in TradeDayProcessor and processing loops to respect cancellation."

---

## Tips
- Use Copilot to generate code, but review and test each change.
- If you get stuck, ask Copilot for help with specific errors or refactoring.

---

