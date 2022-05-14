#include "log.h"

using namespace LogLevel;

int main() {
    Logger log = Logger(true, LogLevel::Debug, "out.log");

    Log<Warning>(&log, __func__, "Hello world");

    return 0;
}