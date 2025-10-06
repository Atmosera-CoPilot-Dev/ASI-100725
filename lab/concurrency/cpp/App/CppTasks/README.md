# CppTasks

Port of the original C# Tasks sample to C++17 using threads and a simple producer/consumer queue. Tests use a minimal embedded doctest header (replace with official doctest for full feature set).

## Build (CMake, non-MSVC)
Toolchain expectation: MinGW g++ or clang++ on Windows. Visual Studio (MSVC) is intentionally not supported.

```
mkdir build
cmake -S . -B build -G "Ninja" -DCMAKE_BUILD_TYPE=Release \
	-DCMAKE_CXX_COMPILER=g++
cmake --build build
ctest --test-dir build --output-on-failure
```
If Ninja is unavailable, you can omit `-G "Ninja"` and rely on the default Makefiles generator for MinGW.



## Quick compile (development only)
```
g++ -std=c++17 -Iinclude -Ithird_party/doctest \
  src/TradeDay.cpp src/TradeDayProcessor.cpp src/main.cpp \
  -o app
```

## Run
```
./cpp_tasks_app ../../dowjones.csv
```

## Notes
- Reflection-based tests from C# are approximated: C++ version verifies no crashes and expected behavior with absent file / null predicate.
- Replace `third_party/doctest/doctest.h` with the upstream single-header for richer assertions.

