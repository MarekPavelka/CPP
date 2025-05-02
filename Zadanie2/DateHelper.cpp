#include "TaskService.h"
#include "DateHelper.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <sstream>

using namespace chrono;

string getTodayDate()
{
    auto now = system_clock::now();
    time_t nowSeconds = system_clock::to_time_t(now);
    tm localNowTime;

#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&localNowTime, &nowSeconds); 
#else
    localtime_r(&nowSeconds, &localNowTime);
#endif

    ostringstream stream;
    stream << put_time(&localNowTime, "%Y-%m-%d");

    return stream.str();
}

string getTomorrowDate()
{
    auto tomorrow = system_clock::now() + hours(24);
    time_t tomorrowSeconds = system_clock::to_time_t(tomorrow);
    tm localTomorrowTime;

#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&localTomorrowTime, &tomorrowSeconds);
#else
    localtime_r(&tomorrowSeconds, &localTomorrowTime);
#endif

    ostringstream stream;
    stream << put_time(&localTomorrowTime, "%Y-%m-%d");

    return stream.str();
}
