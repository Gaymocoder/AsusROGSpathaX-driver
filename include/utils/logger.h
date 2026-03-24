#ifndef __AROGSX_UTILS_LOGGER_H__
#define __AROGSX_UTILS_LOGGER_H__

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include <spdlog/spdlog.h>

#include <string>

#define CRITICAL SPDLOG_CRITICAL
#define ERROR    SPDLOG_ERROR
#define WARN     SPDLOG_WARN
#define INFO     SPDLOG_INFO
#define DEBUG    SPDLOG_DEBUG
#define TRACE    SPDLOG_TRACE

#define CRIT_ASSERT(cond, fmt, ...) \
    if (!(cond)) { \
         \
        CRITICAL(fmt ", aborting" __VA_OPT__(,) __VA_ARGS__); \
        abort(); \
    }

#define ASSERT(cond, fmt, ...) \
    if (!(cond)) { \
        ERROR(fmt __VA_OPT__(,) __VA_ARGS__); \
        return 1; \
    }

#define SUCCESS(cond, log_fnc, ret_flag, fmt, ...) \
    if (cond) { \
        log_fnc(fmt __VA_OPT__(,) __VA_ARGS__); \
        if (ret_flag) \
            return 0; \
    }

namespace utils::logger
{
    void init(int argc, char** argv);

    std::string filepath();
    std::string filename();
    std::string rel_filepath();
}

#endif