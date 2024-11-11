#ifndef LOG_H
#define LOG_H

#define ENABLE_LOGS

#define ENABLE_TRACE
#define ENABLE_DEBUG
#define ENABLE_INFO
#define ENABLE_WARN

#ifdef ENABLE_LOGS
#define log(level, ...) log_internal(level, __FILE__, __VA_ARGS__)
#else
#define log(level, ...) ((void)0)
#endif

#ifdef ENABLE_TRACE
#define trace(...) log("\x1b[94mTRACE", __VA_ARGS__)
#else
#define trace(...) ((void)0)
#endif

#ifdef ENABLE_DEBUG
#define debug(...) log("\x1b[36mDEBUG", __VA_ARGS__)
#else
#define debug(...) ((void)0)
#endif

#ifdef ENABLE_INFO
#define info(...) log("\x1b[32mINFO", __VA_ARGS__)
#else
#define info(...) ((void)0)
#endif

#ifdef ENABLE_WARN
#define warn(...) log("\x1b[33mWARN", __VA_ARGS__)
#else
#define warn(...) ((void)0)
#endif

void log_internal(char *level, char *file, char *format, ...);

#endif
