#include "TradeDayProcessor.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

TradeDayProcessor::TradeDayProcessor(int numConsumers, std::string tradeFile, Predicate test)
    : numConsumers_(numConsumers), tradeFile_(std::move(tradeFile)), test_(std::move(test)) {}

TradeDayProcessor::~TradeDayProcessor() {
    // Join threads if still running
    if (producer_.joinable()) producer_.join();
    for (auto &t : consumers_) if (t.joinable()) t.join();
}

void TradeDayProcessor::start() {
    producer_ = std::thread(&TradeDayProcessor::generateTradeDays, this);
    for (int i = 0; i < numConsumers_; ++i) {
        consumers_.emplace_back(&TradeDayProcessor::consumeTradeDays, this);
    }
}

int TradeDayProcessor::getMatchingCount() {
    if (producer_.joinable()) producer_.join();
    for (auto &t : consumers_) if (t.joinable()) t.join();
    return matching_.load();
}

void TradeDayProcessor::generateTradeDays() {
    std::ifstream in(tradeFile_);
    if (!in.is_open()) {
        // Silently finish if file cannot be opened
        finished_ = true;
        cv_.notify_all();
        return;
    }
    std::string line;
    // skip header if present
    if (std::getline(in, line)) {
        if (line.find("Date") == std::string::npos) {
            // first line is actual data, process it
            TradeDay td = parseTradeEntry(line);
            {
                std::lock_guard<std::mutex> lock(mutex_);
                queue_.push(std::move(td));
            }
            cv_.notify_one();
        }
    }
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        TradeDay td = parseTradeEntry(line);
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(std::move(td));
        }
        cv_.notify_one();
    }
    finished_ = true;
    cv_.notify_all();
}

void TradeDayProcessor::consumeTradeDays() {
    while (true) {
        TradeDay td;
        {
            std::unique_lock<std::mutex> lock(mutex_);
            cv_.wait(lock, [&]{ return finished_ || !queue_.empty(); });
            if (queue_.empty()) {
                if (finished_) break;
                else continue;
            }
            td = std::move(queue_.front());
            queue_.pop();
        }
        if (test_) {
            try {
                if (test_(td)) {
                    matching_.fetch_add(1, std::memory_order_relaxed);
                }
            } catch (...) {
                // ignore predicate exceptions
            }
        }
    }
}

TradeDay TradeDayProcessor::parseTradeEntry(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    TradeDay td;
    // date
    if (!std::getline(ss, token, ',')) return td;
    td.date = parseDate(token);
    auto readDouble = [&](double &ref){ if (std::getline(ss, token, ',')) ref = std::stod(token); };
    auto readLong = [&](long long &ref){ if (std::getline(ss, token, ',')) ref = std::stoll(token); };
    readDouble(td.open);
    readDouble(td.high);
    readDouble(td.low);
    readDouble(td.close);
    readLong(td.volume);
    readDouble(td.adjClose);
    return td;
}
