// Official doctest (main supplied via target compile definitions in CMake)
#include <doctest/doctest.h>
#include "../include/TradeDayProcessor.hpp"
#include <filesystem>
#include <string>

// Tests adapted from MSTest reflection checks. In C++ we verify constructor sets internal state

static std::string fixturePath() {
    namespace fs = std::filesystem;
    fs::path p = fs::path(__FILE__).parent_path() / "fixtures" / "testdata.csv"; // tests/fixtures/testdata.csv
    return p.string();
}

TEST_CASE("Constructor_Assigns_ProvidedValues_AndProcessesFixture") {
    // Using fixture with one row; predicate always true so expect 1 match.
    TradeDayProcessor proc(3, fixturePath(), [](const TradeDay&){ return true; });
    proc.start();
    int count = proc.getMatchingCount();
    CHECK(count == 1);
}

TEST_CASE("Constructor_Allows_Null_Predicate_NoMatches") {
    // Null predicate means we don't evaluate and thus no matches counted.
    TradeDayProcessor proc(1, fixturePath(), nullptr);
    proc.start();
    int count = proc.getMatchingCount();
    CHECK(count == 0);
}

// main is provided by defining DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN in CMake compile definitions
