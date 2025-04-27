#pragma once

#include "common/response.hpp"
#include "common/structures/collection_info.hpp"
#include "common/structures/person.hpp"
#include "common/type_defs.hpp"
#include "frontend/io_manager.hpp"
#include <functional>
#include <memory>
#include <string>
#include <system_error>
#include <vector>

class CommandManager;

/**
 * @brief Базовый класс команды
 *
 */
class Command {
public:
    const std::string description;
    /**
     * @brief Основной метод который должен быть переопределён в каждой команде
     * В каждой команде обязательно вызывается проверка аргументов
     * В каждой команде взамодействующей с backend printStatus или printPersonVector
     *
     * @param args список аргументов в строковом представлении
     */
    const std::function<void(std::vector<std::string> &args)> execute;
    /**
     * @brief Получить строку с описанием команды
     *
     * @return std::string
     */

    ~Command() = default;
    /**
     * @brief Проверить на наличие в args ровно одного аргумента заданного числового типа
     *
     * @tparam N
     * @param args
     * @param res
     * @return true - если аргумент 1 и число заданного типа
     */
    template<NumericType N>
    static bool getOneNumArg (IOManager &io, std::vector<std::string> &args, N &res);
    /**
     * @brief Проверить на наличие в args ровно одного аргумента строкового типа
     *
     * @tparam N
     * @param args
     * @param res
     * @return true - если аргумент 1 и строка
     */
    static bool getOneStringArg (IOManager &io, std::vector<std::string> &args, std::string &res);
    /**
     * @brief Проверить на отсутствие аргуметов
     *
     * @tparam N
     * @param args
     * @param res
     * @return true - если аргументов нет
     */
    static bool getZeroArg (IOManager &io, std::vector<std::string> &args);

    /**
     * @brief Вывести код результата обращения к серверу
     *
     * @tparam T
     * @param response
     */
    template<typename T>
    static void printStatus (IOManager &io, Response<T> response);
    /**
     * @brief Вывести вектор персон, а в случае ошибки вызвать printStatus
     *
     * @param response
     */
    static void printPersonVector (IOManager &io, Response<std::vector<Person>> response);
    /**
     * @brief Преобразовать Person в вид подходящий для вывода на консоль
     *
     * @param person
     * @return std::string
     */
    static std::string toString (Person person);
    /**
     * @brief Преобразовать CollectionInfo в вид подходящий для вывода на консоль
     *
     * @param person
     * @return std::string
     */
    static std::string toString (CollectionInfo info);
};

template<NumericType N>
bool Command::getOneNumArg(IOManager &io, std::vector<std::string> &args, N &res)
{
    if ( args.size() != 1 ) {
        io.writeError("Данная функция принимает один числовой аргумент\n");
        return false;
    }

    std::string arg = args[0];

    auto [ptr, ec] = std::from_chars(arg.data(), arg.data() + arg.size(), res);

    if ( ec == std::errc() && ptr == arg.data() + arg.size() ) {
        return true;
    } else {
        io.writeError("Данная функция принимает один числовой аргумент\n");
        return false;
    }
}

template<typename T>
void Command::printStatus(IOManager &io, Response<T> responce)
{
    switch ( responce.getStatusCode() ) {
    case Response<T>::OK:
        io.write("Выполнено!\n");
        break;
    case Response<T>::ELEMENT_NOT_FOUND:
        io.writeError("Возникла ошибка: элемент не существует\n");
        break;
    case Response<T>::CANT_SAVE_DATA:
        io.writeError("Возникла ошибка: данные не сохранены\n");
        break;
    case Response<T>::INDEX_OUT_OF_RANGE:
        io.writeError("Индекс вышел за границы коллекции\n");
        break;
    case Response<T>::NULL_RESULT:
        io.writeError("Результат пуст\n");
        break;
    case Response<T>::FAIL:
        io.writeError("Не удалось выполнить операциюn\n");
        break;
    }
}