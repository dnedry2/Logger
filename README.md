Simple cpp logger

Example:

Logger log = Logger(true, LogLevel::Debug, "out.log");
Log<Warning>(&log, __func__, "Hello world");
