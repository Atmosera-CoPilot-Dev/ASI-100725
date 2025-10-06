#include "TradeDay.hpp"
#include <sstream>
#include <iomanip>

std::string TradeDay::toString() const {
    std::ostringstream oss;
    oss << formatDate(date) << ": " << open << " - " << close;
    return oss.str();
}

std::chrono::system_clock::time_point parseDate(const std::string& s) {
    std::tm tm{};
    std::istringstream iss(s);
    iss >> std::get_time(&tm, "%Y-%m-%d");
    auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    return tp;
}

std::string formatDate(const std::chrono::system_clock::time_point& tp) {
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    char buf[16];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", &tm);
    return buf;
}
