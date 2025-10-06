#pragma once
#include "TradeDay.hpp"
#include <functional>
#include <string>
#include <vector>
#include <atomic>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>

class TradeDayProcessor {
public:
    using Predicate = std::function<bool(const TradeDay&)>;

    TradeDayProcessor(int numConsumers, std::string tradeFile, Predicate test);
    ~TradeDayProcessor();

    void start();
    int getMatchingCount();

private:
    int numConsumers_;
    std::string tradeFile_;
    Predicate test_;

    std::vector<std::thread> consumers_;
    std::thread producer_;

    std::queue<TradeDay> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;
    bool finished_{false};

    std::atomic<int> matching_{0};

    void generateTradeDays();
    void consumeTradeDays();
    static TradeDay parseTradeEntry(const std::string& line);
};
