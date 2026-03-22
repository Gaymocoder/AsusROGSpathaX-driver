#ifndef __AROGSX_UTILS_LOGGER_H__
#define __AROGSX_UTILS_LOGGER_H__

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include <spdlog/spdlog.h>

#include "utils/macro.h"

#define CRITICAL SPDLOG_CRITICAL
#define ERROR    SPDLOG_ERROR
#define WARN     SPDLOG_WARN
#define INFO     SPDLOG_INFO
#define DEBUG    SPDLOG_DEBUG
#define TRACE    SPDLOG_TRACE

namespace utils::logger
{
    void init(int argc, char** argv);
}

#endif