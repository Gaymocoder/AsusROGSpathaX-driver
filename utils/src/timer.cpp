#include "utils/timer.h"

#include <cstdio>

namespace utils
{

bool Timer::inited = false;
TimePointSC Timer::starting_point = TimePointSC();
TimePointSC Timer::previous_point = TimePointSC();

void Timer::init(bool print)
{
    Timer::inited = true;
    Timer::null(print);
}

void Timer::null(bool print)
{
    auto now = std::chrono::steady_clock::now();
    Timer::starting_point = now;
    Timer::previous_point = now;

    if (print)
        fprintf(stderr, "[%12li][%12li] %s\n", (long) 0, (long) 0, "NULL");
}

int Timer::point(const char* commentary)
{
    auto now = std::chrono::steady_clock::now();
    if (!Timer::inited)
        return 1;

    auto from_starting_point = std::chrono::duration_cast <std::chrono::nanoseconds> (now - Timer::starting_point).count();
    auto from_previous_point = std::chrono::duration_cast <std::chrono::nanoseconds> (now - Timer::previous_point).count();

    Timer::previous_point = now;
    fprintf(stderr, "[%12li][%12li] %s\n", from_starting_point, from_previous_point, commentary);

    return 0;
}

}