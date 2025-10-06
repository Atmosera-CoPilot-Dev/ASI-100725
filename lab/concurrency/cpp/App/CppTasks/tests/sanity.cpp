#include "../include/TradeDayProcessor.hpp"
#include <iostream>

int main(){
    // Sanity: construct processor with null predicate and no start to ensure basic object works.
    TradeDayProcessor proc(1, "nonexistent.csv", nullptr);
    std::cout << "Sanity OK\n";
    return 0;
}
