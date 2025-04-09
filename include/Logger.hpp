#pragma once
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iomanip>
#include <iostream>
#include <string>
#include <mutex>
#include <map>
#include <fstream>
#include <ctime>
#include <sstream>
#include <set>

enum class LogLevel {
    INFO,
    WARNING,
    ERROR,
    DEBUG
};

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void setLogLevel(LogLevel level, bool enabled) {
        std::lock_guard<std::mutex> lock(mutex);
        logLevels[level] = enabled;
    }

    void setLogFile(const std::string& filePath) {
        std::lock_guard<std::mutex> lock(mutex);
        logFile.open(filePath, std::ios::out | std::ios::app);  // Otwórz do dopisywania
        if (!logFile.is_open()) {
            std::cerr << "[Logger] Failed to open log file: " << filePath << std::endl;
        }
    }

    void setKeywordFilter(const std::set<std::string>& keywords) {
        std::lock_guard<std::mutex> lock(mutex);
        keywordsFilter = keywords;
    }

    void log(LogLevel level, const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex);
        if (logLevels[level]) {
            std::string formattedMessage = getTimestamp() + " " + getLogLevelString(level) + " " + message;

            if (keywordsFilter.empty() || containsKeyword(message)) {
                std::cout << formattedMessage << std::endl;  // Loguj do konsoli
                if (logFile.is_open()) {
                    logFile << formattedMessage << std::endl;  // Loguj do pliku
                }
            }
        }
    }
    
    void muteAll() {
        std::lock_guard<std::mutex> lock(mutex);
        for (auto& pair : logLevels) {
            pair.second = false;
        }
    }

    void unmuteAll() {
        std::lock_guard<std::mutex> lock(mutex);
        for (auto& pair : logLevels) {
            pair.second = true;
        }
    }
    
    Logger() {
        logLevels[LogLevel::INFO] = true;
        logLevels[LogLevel::WARNING] = true;
        logLevels[LogLevel::ERROR] = true;
        logLevels[LogLevel::DEBUG] = false; // DEBUG w³¹czamy, jak potrzeba
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

private:
    std::map<LogLevel, bool> logLevels;
    std::mutex mutex;
    std::ofstream logFile;  // Plik do zapisywania logów
    std::set<std::string> keywordsFilter;  // Filtr s³ów kluczowych

    std::string getTimestamp() {
        std::time_t now = std::time(nullptr);
        std::tm tm = *std::localtime(&now);
        std::ostringstream oss;
        oss << std::put_time(&tm, "[%Y-%m-%d %H:%M:%S]");
        return oss.str();
    }

    std::string getLogLevelString(LogLevel level) {
        switch (level) {
        case LogLevel::INFO: return "[INFO]";
        case LogLevel::WARNING: return "[WARNING]";
        case LogLevel::ERROR: return "[ERROR]";
        case LogLevel::DEBUG: return "[DEBUG]";
        default: return "[UNKNOWN]";
        }
    }

    bool containsKeyword(const std::string& message) {
        for (const auto& keyword : keywordsFilter) {
            if (message.find(keyword) != std::string::npos) {
                return true;
            }
        }
        return false;
    }
};
#endif // !LOGGER_HPP
