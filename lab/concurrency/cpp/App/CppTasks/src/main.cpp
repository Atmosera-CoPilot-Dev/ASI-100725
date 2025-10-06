#include "TradeDayProcessor.hpp"
#include <iostream>
#include <chrono>

int main(int argc, char** argv) {
    int numConsumers = 1;
    // Default dataset path relative to executable working directory (App/CppTasks)
    // The CSV lives at App/DowJones.csv, so from here it's one level up.
    std::string file = "../DowJones.csv"; 
    if (argc > 1) file = argv[1];

    TradeDayProcessor processor(numConsumers, file, [](const TradeDay& d){
        if (d.open == 0.0) return false;
        return (d.close - d.open) / d.open > 0.05; // >5%
    });

    auto start = std::chrono::steady_clock::now();
    processor.start();
    int matches = processor.getMatchingCount();
    auto end = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Total processing time " << ms << " ms\n";
    std::cout << "Total matches " << matches << "\n";
    return 0;
}
