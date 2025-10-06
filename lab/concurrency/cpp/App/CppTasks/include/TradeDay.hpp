#pragma once
#include <string>
#include <chrono>

struct TradeDay {
    std::chrono::system_clock::time_point date; // parsed from YYYY-MM-DD
    double open{};
    double high{};
    double low{};
    double close{};
    long long volume{};
    double adjClose{};

    std::string toString() const;
};

std::chrono::system_clock::time_point parseDate(const std::string& s);
std::string formatDate(const std::chrono::system_clock::time_point& tp);
