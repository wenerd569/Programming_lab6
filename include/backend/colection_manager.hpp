#pragma once

#include <cmath>
#include <map>
#include <vector>

#include "backend/collection_serializer.hpp"
#include "backend/date_manager.hpp"
#include "backend/id_manager.hpp"
#include "common/interface/person_collection_service.hpp"

/**
 * @brief Управляет коллекцией Person
 * Реализет все стандартные сценарии взаимодействия с колекцией
 * @note Этот класс сейчас напрямую используется в Command, позднее он будет подключен к API,
 * которое будет получать Response, сереализовываь его и отправлять на клиент
 */
class CollectionManager : public CollectionService {
    // Колекция
    std::vector<Person> persons;
    // Класс управляющий выдачей Id элементам колекции
    IdManager idManager;
    // Класс управляющий выдачей даты создания элементам колекции
    DateManager dateManager;
    // Класс управляющий сериализацией элементов колекции
    CollectionSerializer collectionSerializer;

    // Название типа элементов Колекции (нужен для создания CollectionInfo)
    std::string type;

public:
    /**
     * @brief Construct a new Collection Manager object
     * Сам подгружает значения из файла колекции
     * @param collectionSerializer
     * @warning Если файл колекции не скществует сделает exit(1)
     * Если существует, но содержит неправильные данные колекция создастся заново
     */
    CollectionManager(CollectionSerializer collectionSerializer);

    /**
     * @brief Сохраняет колекцию в файл
     *
     * @return колекция сохранена -> Responce<void>::OK
     * не сохранена -> Responce Responce<void>::CANT_SAVE_DATA
     */
    Response<void> save () override;
    /**
     * @brief Получить информацию о колекции
     *
     * @return Response<CollectionInfo>::OK
     */
    Response<CollectionInfo> getInfo () override;

    /**
     * @brief Добавить элемент в колекцию
     *
     * @param prePerson (Преобразуется в Person)
     * @return Response<void>::OK
     */
    Response<void> add (PersonPrecursor &prePerson) override;
    /**
     * @brief Удалить элемент колекции по его id
     *
     * @param id
     * @return елемент найден и удалён -> Response<void>::OK
     * нет элемента с заданным id -> Response<void>::ELEMENT_NOT_FOUND
     */
    Response<void> remove (long id) override;
    /**
     * @brief Обновить значения элемента с заданным id
     *
     * @param id
     * @param prePerson (Преобразуется в Person)
     * @return елемент найден и обновлён ->Response<void>::OK
     * нет элемента с заданным id -> Response<void>::ELEMENT_NOT_FOUND
     */
    Response<void> update (long id, PersonPrecursor &prePerson) override;
    /**
     * @brief Очистить колекцию
     *
     * @return Response<void>::OK
     */
    Response<void> clear () override;
    /**
     * @brief Вставить элемент по индексу
     *
     * @param index
     * @param prePerson (Преобразуется в Person)
     * @return index не выходит за границы колекции -> Response<void>::OK
     * выходит -> Response<void>::INDEX_OUT_OF_RANGE
     */
    Response<void> inseartAt (size_t index, PersonPrecursor &prePerson) override;
    /**
     * @brief Добавить элемент если его высота макимальна
     *
     * @param prePerson (Преобразуется в Person)
     * @return успешно добавлен -> Response<void>::OK
     * не добавлен -> Response<void>::FAIL
     */
    Response<void> addIfMax (PersonPrecursor &prePerson) override;
    /**
     * @brief Добавить элемент если его высота минимальна
     *
     * @param prePerson (Преобразуется в Person)
     * @return успешно добавлен -> Response<void>::OK
     * не добавлен -> Response<void>::FAIL
     */
    Response<void> addIfMin (PersonPrecursor &prePerson) override;

    /**
     * @brief Проверить элемент с конкретным id на существование
     *
     * @param id
     * @return элемент есть -> Response<void>::OK
     * элемента нет -> Response<void>::ELEMENT_NOT_FOUND
     */
    Response<void> checkElement (long id) override;
    /**
     * @brief Получить всю колекцию
     *
     * @return результат не пуст -> Response<std::vector<Person>>::OK
     * результат пуст -> Response<std::vector<Person>>::NULL_RESULT
     */
    Response<std::vector<Person>> getAllElement () override;
    /**
     * @brief Получить все элементы с высотой меньше заданной
     *
     * @param height
     * @return результат не пуст -> Response<std::vector<Person>>::OK
     * результат пуст -> Response<std::vector<Person>>::NULL_RESULT
     */
    Response<std::vector<Person>> getHeightLessElement (double height) override;
    /**
     * @brief Сгрупировть элементы по имени и вывести количество элементов с конкретным именем
     *
     * @return результат не пуст -> Response<std::map<std::string, int>>::OK
     * результат пуст -> Response<std::map<std::string, int>>::NULL_RESULT
     */
    Response<std::map<std::string, int>> groupCountingByName () override;

    Response<std::map<long, Country>> getFieldAscendingNationality () override;

private:
    /**
     * @brief Расширяет PersonPrecursor до Person добавив id и creationDate
     *
     * @param prePerson
     * @return Person
     */
    Person createPerson (PersonPrecursor &prePerson);
    /**
     * @brief Берёт из данные из this, DateManager и IdManager
     * и компаниет их в CollectionInfo
     * @return CollectionInfo
     */
    CollectionInfo configureInfo ();
};