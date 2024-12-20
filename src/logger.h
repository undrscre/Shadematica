#pragma once

#include <ctime>
#include <iostream>
#include <string>

enum Level { INFO, ERROR, WARN };
enum Thread { MAIN, RENDER, UI, EDITOR, SHADER };

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void log(Level level, Thread thread, const std::string& message) {
        time_t now = time(0);
        tm* timeinfo = localtime(&now);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

        std::cout << "[" << timestamp << "] "
                  << levelToString(level) << " @ " << threadToString(thread) << " THREAD: "
                  << message << std::endl;
    }

private:
    Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::string levelToString(Level level) {
        switch (level) {
        case INFO: return "\e[0;34;1mINFO\e[0m";
        case WARN: return "\e[0;33;1mWARNING\e[0m";
        case ERROR: return "\e[0;31;1mERROR\e[0m";
        default: return "UNKNOWN";
        }
    }

    std::string threadToString(Thread thread) {
        switch (thread) {
        case MAIN: return "MAIN";
        case RENDER: return "RENDER";
        case SHADER: return "SHADER";
        case UI: return "UI";
        case EDITOR: return "EDITOR";
        default: return "UNKNOWN";
        }
    }
};

#define logm(level, thread, message) Logger::getInstance().log(level, thread, message)