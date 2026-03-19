#ifndef __AROGSX_UTILS_TIMER_H__
#define __AROGSX_UTILS_TIMER_H__

#include <chrono>

namespace utils
{
    using TimePointSC = std::chrono::time_point <std::chrono::steady_clock>;

    class Timer
    {
        private:
            Timer();
            static bool inited;
            static TimePointSC starting_point;
            static TimePointSC previous_point;

        public:
            static void init(bool print = false);
            static void null(bool print = false);
            static int point(const char* commentary);
    };
}

#endif