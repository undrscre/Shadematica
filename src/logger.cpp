#include <ctime>
#include <iostream>
using namespace std;

enum Level { INFO, ERROR, WARNING };
class Logger {
public:
    void log(Level level, const string& message) {
        time_t now = time(0);
        tm* timeinfo = localtime(&now);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
        cout << "[" << timestamp << "] " << levelToString(level) << ": " << message << endl;
    }
private:
    string levelToString(Level level) {
        switch (level) {
        case INFO:
            return "INFO";
        case WARNING:
            return "WARNING";
        case ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
        }
    }
};