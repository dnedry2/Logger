#ifndef _LOGGER_
#define _LOGGER_

#include <stdio.h>
#include <stdarg.h>

namespace LogLevel { enum Level { Error, Warning, Info, Message, Debug }; };

/*
* Message logging class
* 
* Writes to terminal and optionally a file
*/
class Logger {
public:
    /*
    * Generic print / log function
    *
    * @param type    message type
    * @param sender  function sending message
    * @param format  output format (like printf)
    * @param ...     output
    */
    void Log(LogLevel::Level type, const char* sender, const char* format, ...);

    /*
    * Generic print / log function
    *
    * @param type    message type
    * @param sender  function sending message
    * @param format  output format (like printf)
    * @param args    output
    */
    void Log(LogLevel::Level type, const char* sender, const char* format, va_list args);

    // Current verbosity level
    LogLevel::Level& Verbosity();
    // Logging to file?
    bool IsFileLogging();
    // Enable / Disable logging to file
    void SetFileLogging(bool log);

    /*
    * Logger constructor
    *
    * @param log        log messages to file
    * @param verbosity  lowest level message to log
    * @param logPath    path to log file
    */
    Logger(bool fileLog, LogLevel::Level verbosity, const char* logPath = nullptr);
    ~Logger();
private:
    // Location to write log
    const char* logPath;
    // Logfile pointer
    FILE* logFile = NULL;
    // Logging enabled?
    bool log;
    // Verbosity level
    LogLevel::Level verbosity;

    const char* LevelText[5] = { "Error: ", "Warn: ", "Info: ", "Message: ", "Debug: " };
    const char* LevelAnsi[5] = { "\033[1;31m",  "\033[1;33m", "\033[1;32m", "\033[1;36m", "" };
};

template <LogLevel::Level lvl> void Log(Logger* log, const char* sender, const char* format, ...) {
    va_list args;
    va_start(args, format);
    
    log->Log(lvl, sender, format, args);

    va_end(args);
}

#endif