/**
 * @brief Класс выдающий уникальные id элементам колекции
 *
 */
class IdManager {
    long lastId;

public:
    IdManager();
    IdManager(long last_id);

    long getNext ();
    long getLast ();
};