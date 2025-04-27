#include "backend/date_manager.hpp"
#include <chrono>

using namespace std::chrono;

DateManager::DateManager() : ititialDay { DateManager::getCurrentDate() } { }

DateManager::DateManager(year_month_day ititialDay) : ititialDay { ititialDay } {};

year_month_day DateManager::getCurrentDate()
{
    auto now = system_clock::now();
    auto local_time = zoned_time { std::chrono::current_zone(), now };

    auto currDay = floor<days>(local_time.get_local_time());
    year_month_day res { currDay };
    return res;
}

year_month_day DateManager::getInitialDate()
{
    return ititialDay;
}