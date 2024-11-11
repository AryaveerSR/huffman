#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "log.h"

const char *level_text[] = {
    [LEVEL_TRACE] = "\x1b[94mTRACE",
    [LEVEL_INFO] = "\x1b[32mINFO",
    [LEVEL_WARN] = "\x1b[33mWARN",
};

static enum Level filter = 255;

void log_init(void)
{
    const char *env_log_filter = getenv("NEUR_LOG");

    if ((env_log_filter == NULL) || (env_log_filter[1] != '\0'))
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

void log_event(enum Level level, char *file, char *format, ...)
{
    if (level < filter)
    {
        return;
    }

    va_list args;
    va_start(args, format);

    printf("%s \x1b[90m[%s]:\x1b[0m ", level_text[level], file);
    vprintf(format, args);
    printf("\n");

    va_end(args);
}
