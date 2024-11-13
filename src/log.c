#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdnoreturn.h>

#include "log.h"

static const char *level_text[] = {
    [LEVEL_TRACE] = "\x1b[94mTRACE",
    [LEVEL_INFO] = "\x1b[32mINFO",
    [LEVEL_WARN] = "\x1b[33mWARN",
};

static enum Level filter = LEVEL_NONE;

/**
 * Initializes the logging system.
 *
 * This reads the `NEUR_LOG` environment variable and sets the minimum log level
 * to that value if valid. Default minimum log level is `LEVEL_NONE` (no logs printed).
 */
void log_init(void)
{
    const char *env_log_filter = getenv("NEUR_LOG");

    if ((env_log_filter == NULL) || (strlen(env_log_filter) != 1))
    {
        return;
    }

    switch (env_log_filter[0])
    {
    case '0':
        filter = LEVEL_TRACE;
        break;

    case '1':
        filter = LEVEL_INFO;
        break;

    case '2':
        filter = LEVEL_WARN;
        break;
    }
}

/**
 * Logs an event to the terminal if the level satisfies the filter.
 *
 * @param level The level of the event.
 * @param file The file where the event originated. This is usually passed by __FILE__ in macros.
 */
void log_event(enum Level level, char *file, unsigned int line, char *format, ...)
{
    if (level < filter)
    {
        return;
    }

    va_list args;
    va_start(args, format);

    printf("%s \x1b[90m[%s:%d]:\x1b[0m ", level_text[level], file, line);
    vprintf(format, args);
    printf("\n");

    va_end(args);
}

noreturn void log_panic(char *file, unsigned int line, char *format, ...)
{
    va_list args;
    va_start(args, format);

    printf("\x1b[31mPANIC \x1b[90m[%s:%d]:\x1b[0m ", file, line);
    vprintf(format, args);
    printf("\n");

    va_end(args);

    exit(1);
}
