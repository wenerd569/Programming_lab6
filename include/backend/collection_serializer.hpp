#pragma once

#include "common/structures/collection_info.hpp"
#include "common/structures/person.hpp"
#include <filesystem>
#include <optional>
#include <vector>

/**
 * @brief json сериализатор/десериализатор колекции
 */
class CollectionSerializer {
    // путь до файла колекции
    std::filesystem::path filePath;

public:
    /**
     * @brief Создаёт новый CollectionSerializer
     *
     * @param filePath
     */
    CollectionSerializer(std::filesystem::path filePath);

    /**
     * @brief Сериализует колекцию в файл по filePath
     *
     * @param collection
     * @param colectionManager
     * @warning Если файл не может быть открыт вызовет std::ios_base::failure
     */
    void serialize (std::vector<Person> &collection, CollectionInfo &colectionManager);
    /**
     * @brief Десериализует колекцию из файла по filePath
     *
     * @return std::pair<std::vector<Person>, std::optional<CollectionInfo>>
     * @warning Если файл не может быть открыт вызовет std::ios_base::failure
     * если информация в файле повреждена вернёт пустой std::vector<Person> и
     * std::optional<CollectionInfo> без данных
     */
    std::pair<std::vector<Person>, std::optional<CollectionInfo>> deserialize ();
};