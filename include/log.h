#ifndef LOG_H
#define LOG_H

enum Level
{
    LEVEL_TRACE,
    LEVEL_INFO,
    LEVEL_WARN,

    LEVEL_NONE,
};

void log_init(void);

#define trace(...) log_event(LEVEL_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define info(...) log_event(LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define warn(...) log_event(LEVEL_WARN, __FILE__, __LINE__, __VA_ARGS__)

void log_event(enum Level level, char *file, unsigned int line, char *format, ...);

#define panic(...) log_panic(__FILE__, __LINE__, __VA_ARGS__)

void log_panic(char *file, unsigned int line, char *format, ...);

#endif
