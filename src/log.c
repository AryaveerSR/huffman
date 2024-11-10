#include <stdio.h>
#include <stdarg.h>

#include "log.h"

void _log(char *level, char *file, char *format, ...)
{
    va_list args;
    va_start(args, format);

    printf("%s \x1b[90m[%s]:\x1b[0m ", level, file);
    vprintf(format, args);
    printf("\n");

    va_end(args);
}
