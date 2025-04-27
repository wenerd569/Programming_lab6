#include <chrono>

/**
 * @brief Класс выдающий даьты создания элеметам колекции
 * и хранящий дату создания колекции
 */
class DateManager {
    std::chrono::year_month_day ititialDay;

public:
    DateManager();
    DateManager(std::chrono::year_month_day ititialDay);
    static std::chrono::year_month_day getCurrentDate ();
    std::chrono::year_month_day getInitialDate ();
};