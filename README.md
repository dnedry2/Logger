Simple cpp logger


Example:
```
Logger log = Logger(true, LogLevel::Debug, "out.log");
Log<Info>(&log, __func__, "Hello world");
```
Prints:
```
[main] Info: Hello world
```

Set Verbosity:
```
log.Verbosity() = LogLevel::Error;
```
Enable file logging:
```
log.SetFileLogging(true);
```
