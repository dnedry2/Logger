#include <string.h>
#include <ctime>

#include "log.h"

using namespace LogLevel;

char* getTime(char* buffer, int len, const char* fmt = "%d-%m-%Y %H:%M:%S") {
    time_t rt = time(NULL);
    strftime(buffer, len, fmt, localtime(&rt));
    return buffer;
}

Logger::Logger(bool log, Level level, const char* logPath) : logPath(logPath), verbosity(level)
{
    SetLogging(log);
}

Logger::~Logger() {
    if (logFile != NULL)
        fclose(logFile);
}

Level& Logger::Verbosity() { return verbosity; }
bool Logger::IsLogging() { return log; }

void Logger::SetLogging(bool log) {
    this->log = log;

    if (!log) {
        if (logFile != NULL)
            fclose(logFile);
            logFile = NULL;
    } else {
        // Open log file. logPath can't change, so any file already open is the right one
        if (logFile == NULL && logPath != nullptr) {
            if (!(logFile = fopen(logPath, "a"))) {
                Log(Level::Error, __func__, "Failed to open log file!");
                this->log = false;
            } else {
                // Write log start time to file
                char buffer[80];
                fprintf(logFile, "**** Log start: %s ****\n", getTime(buffer, 80));
            }
        }
    }
}

void Logger::Log(Level type, const char* sender, const char* format, va_list args) {
    constexpr int hLen = 256;
    int nType = static_cast<int>(type);

    if (type <= verbosity) {
        char hBuf[hLen], tBuf[80];

        snprintf(hBuf, hLen, "%s[%s] %s\033[0m%s\n", LevelAnsi[nType], sender, LevelText[nType], format);
        vprintf(hBuf, args);

        if (log && logFile != NULL) {
            snprintf(hBuf, hLen, "%s [%s] %s%s\n", getTime(tBuf, 80), sender, LevelText[nType], format);
            vfprintf(logFile, hBuf, args);
        }
    }
}

void Logger::Log(Level type, const char* sender, const char* format, ...) {
    va_list args;
    va_start(args, format);

    Log(type, sender, format, args);

    va_end(args);
}