#ifndef LOG_H
#define LOG_H

#define ENABLE_LOGS

#define ENABLE_TRACE
#define ENABLE_DEBUG
#define ENABLE_INFO
#define ENABLE_WARN

#if defined(ENABLE_LOGS) && defined(ENABLE_TRACE)
#define trace(...) _log("\x1b[94mTRACE", __FILE__, __VA_ARGS__)
#else
#define trace(ignore) ((void)0)
#endif

#if defined(ENABLE_LOGS) && defined(ENABLE_DEBUG)
#define debug(...) _log("\x1b[36mDEBUG", __FILE__, __VA_ARGS__)
#else
#define debug(ignore) ((void)0)
#endif

#if defined(ENABLE_LOGS) && defined(ENABLE_INFO)
#define info(...) _log("\x1b[32mINFO", __FILE__, __VA_ARGS__)
#else
#define info(ignore) ((void)0)
#endif

#if defined(ENABLE_LOGS) && defined(ENABLE_WARN)
#define warn(...) _log("\x1b[33mWARN", __FILE__, __VA_ARGS__)
#else
#define warn(ignore) ((void)0)
#endif

#endif
