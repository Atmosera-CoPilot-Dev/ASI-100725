# Concurrent Data Processing Lab (C++ + Threads + Copilot)

## Lab Goal
Enhance the C++ concurrency sample in `App/CppTasks` by evolving it into a robust, cancellable producer / multi-consumer pipeline that processes historical trade data from `DowJones.csv`. Use GitHub Copilot to iteratively implement and refine each step.

---

## Current Project Layout (Key Parts)
```
App/CppTasks/
	CMakeLists.txt
	include/
		TradeDay.hpp
		TradeDayProcessor.hpp
	src/
		main.cpp
		TradeDay.cpp
		TradeDayProcessor.cpp
	tests/
		test_tradedayprocessor.cpp
DowJones.csv
```

`TradeDayProcessor` already contains a basic producer thread and multiple consumer threads using a `std::queue` guarded by `std::mutex` + `std::condition_variable`.

You will extend it to:
1. Make the design more explicit and configurable.
2. Add cancellation.
3. Add better aggregation & error handling.
4. (Optional) Experiment with alternative queue strategies or C++20 utilities.

---

## Prerequisites
1. A C++20-capable compiler (MSVC, Clang, or GCC).
2. CMake (project already configured for out-of-source builds).
3. (Optional) Ninja for faster builds.

### Build & Run (VS Code on Windows, bash shell)

MinGW (GCC / "MinGW Makefiles") toolchain (recommended to avoid MSVC/CRT mixing):
```bash
# From repository root or project root; ensure you are in App/CppTasks directory
cd App/CppTasks

# Configure using MinGW Makefiles generator (Release build)
cmake -S . -B build_mingw -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release

# Build (uses make under the hood)
cmake --build build_mingw -- -j

# Run unit tests (doctest + sanity) – all should pass
ctest --test-dir build_mingw -V

# (Optional) Quick smoke run with tiny fixture (should report 1 match)
./build_mingw/cpp_tasks_app.exe tests/fixtures/testdata.csv

# Run the application (uses corrected relative path ../DowJones.csv by default)
./build_mingw/cpp_tasks_app.exe

# (Optional) Provide an explicit CSV path (overrides default)
./build_mingw/cpp_tasks_app.exe ../DowJones.csv

# (Optional) Debug build
cmake -S . -B build_mingw_dbg -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake --build build_mingw_dbg -- -j

# Re-run tests in Debug
ctest --test-dir build_mingw_dbg -V

# (Optional) Run the app in Debug (useful for stepping through threads)
./build_mingw_dbg/cpp_tasks_app.exe ../DowJones.csv

# Clean rebuild (if switching generators or encountering unexplained crashes)
rm -rf build_mingw && cmake -S . -B build_mingw -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release && cmake --build build_mingw -- -j
```


## Enhancement Roadmap
Tackle these one at a time, prompting Copilot for each change.

### 1. Refine the Producer
Goal: Make the producer clearly separated and optionally bounded.
Suggested changes:
- Add an optional maximum queue size (e.g., `size_t maxQueueSize_`) to throttle production.
- In `generateTradeDays()`, block (wait) when queue is full (prevent unbounded memory growth).
- Log (or count) how many rows were parsed.

Sample Copilot prompts:
- "In TradeDayProcessor, add a maxQueueSize_ member and modify generateTradeDays to wait while the queue is full using a second condition_variable if needed."
- "Add a counter for produced items and expose a getter."

### 2. Strengthen Consumers
Goal: Each consumer returns its own match count (rather than using only a shared atomic) so we can aggregate and debug distribution.
Suggested changes:
- Replace / augment the shared `matching_` counter with a `std::vector<int> consumerCounts_` sized to `numConsumers_`.
- Pass an index to each consumer thread (lambda capture or bind) so it updates only its slot.
- Retain `atomic<int>` for quick global increment if you like, but final result should also sum the vector.

Sample prompts:
- "Modify start() so that consumers are launched with their index and store per-consumer counts in a vector."
- "Add a method aggregateMatches() that sums consumerCounts_."

### 3. Add Cancellation
Goal: Allow early termination (user input or timeout).
Approaches (choose one):
- C++20 `std::stop_source` / `std::stop_token` (if compiler/lib supports it).
- Or a simple `std::atomic<bool> cancel_{false}` checked in loops.

Implementation steps:
- Add a `requestCancel()` method that sets the flag or calls `stop_source.request_stop()`. Notify waiting threads.
- Modify producer & consumer loops to exit promptly when cancellation is signaled.
- In `main.cpp`, start a small watcher thread that waits for ENTER and calls `requestCancel()`.

Sample prompts:
- "Add an atomic<bool> cancel_ to TradeDayProcessor and a public requestCancel() method."
- "Update generateTradeDays and consumeTradeDays to stop early if cancel_ is set."
- "In main.cpp, launch a thread that waits for user input and then calls processor.requestCancel()."

### 4. Robust Aggregation & Error Handling
Goal: Safely gather results and handle exceptions.
Suggested changes:
- Wrap predicate evaluation in try/catch (already present) but log counts of predicate errors.
- Add a method `waitForCompletion()` that joins threads and returns a struct with statistics:
	- produced rows
	- matched rows
	- predicate errors
	- cancelled flag
- Replace `getMatchingCount()` with the richer result type.

Sample prompts:
- "Create a Result struct in TradeDayProcessor with produced, matched, predicateErrors, cancelled fields."
- "Implement waitForCompletion() returning Result after joining threads."

### 5. (Optional) Performance / Alternative Queues
Ideas:
- Replace `std::queue` with a `std::deque` to allow move-friendly pops.
- Implement a lock-free single-producer / multi-consumer queue (note: trickier; could use a third-party library).
- Add timing instrumentation (steady_clock durations) per stage.

Sample prompts:
- "Instrument generateTradeDays and consumeTradeDays with timing and expose a stats struct."
- "Refactor queue_ to a bounded circular buffer implementation."

### 6. (Optional) Testing Enhancements
Extend `tests/test_tradedayprocessor.cpp`:
- Add a test with a controlled small CSV verifying match counts.
- Add a test that triggers cancellation early and asserts fewer items processed than total.
- Add a test for bounded queue backpressure (producer blocks until consumer frees space).

Sample prompts:
- "Add a unit test that feeds 10 rows where 3 satisfy the predicate and asserts the Result.matched == 3."
- "Add a cancellation test that cancels after first item and ensures matched <= 1."

---

## Example High-Level Copilot Prompt Sequence
1. "Introduce cancellation support (atomic flag) to TradeDayProcessor and modify loops to break early."
2. "Expose a Result struct with produced, matched, predicateErrors, cancelled."
3. "Refactor consumer threads to store per-thread counts and aggregate them."
4. "Add a bounded queue size of 1024 and block producer when full."
5. "Add a watcher thread in main.cpp that cancels on ENTER keypress."
6. "Extend tests to cover cancellation and bounded queue behavior."

---

## Suggested Acceptance Criteria
- Program still builds with CMake (Release & Debug).
- Cancelling early returns quickly (within < 100ms after ENTER on moderate CSV).
- Result struct reports coherent totals (matched <= produced, produced > 0 for non-empty CSV).
- Unit tests pass (`ctest -V`).

---

## Troubleshooting
- Hanging on exit: ensure all threads are joined and condition variable is notified on cancel.
- Zero matches unexpectedly: verify predicate and that CSV header handling is correct.
- Crash on `stod`/`stoll`: guard empty tokens or malformed lines.

---

## Quick Reference: Key Files
- `TradeDay.hpp / TradeDay.cpp`: Domain model + date parsing.
- `TradeDayProcessor.hpp / .cpp`: Pipeline orchestration (producer, consumers, queue, aggregation).
- `main.cpp`: Entry point, sets predicate, runs processor.
- `tests/`: doctest-based unit tests; add more here.

---

## Next Steps After Core Enhancements
- Add command-line options for number of consumers, predicate threshold, and queue size.
- Emit JSON summary (e.g., to stdout) for integration with other tools.
- Profile with `chrono` timestamps or platform profilers to tune consumers.

Happy hacking with C++ concurrency and Copilot!


