#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>

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

#define panic(...) log_panic(__FILE__, __LINE__, __VA_ARGS__)

#define out_of_memory()                          \
    do                                           \
    {                                            \
        printf("\x1b[31mOUT OF MEMORY.\x1b[0m"); \
        exit(1);                                 \
    } while (0)

void log_event(enum Level level, char *file, unsigned int line, char *format, ...);
void log_panic(char *file, unsigned int line, char *format, ...);

#endif
